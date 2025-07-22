/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_6_chunk_sort.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codex <codex@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 00:00:00 by codex             #+#    #+#             */
/*   Updated: 2025/07/22 00:00:00 by codex            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

#define CHUNK_SIZE 25
#define MAXCHUNK 40

typedef struct s_chunk {
	int min_val;
	int max_val;
	int index;
} t_chunk;

typedef struct s_chunks {
	t_chunk chunks[MAXCHUNK];
	int count;
} t_chunks;

static void	init_chunks(t_chunks *chunks, size_t n)
{
	int chunk_count = (n + CHUNK_SIZE - 1) / CHUNK_SIZE;
	for (int i = 0; i < chunk_count; ++i)
	{
		chunks->chunks[i].min_val = i * CHUNK_SIZE;
		chunks->chunks[i].max_val = (i + 1) * CHUNK_SIZE - 1;
		if (chunks->chunks[i].max_val >= (int)n)
			chunks->chunks[i].max_val = (int)n - 1;
		chunks->chunks[i].index = i;
	}
	chunks->count = chunk_count;
}

static int	chunk_contains(const t_chunk *chunk, int val)
{
	return (val >= chunk->min_val && val <= chunk->max_val);
}

static void	move_two_chunks_to_b(t_Stacks *s, t_op *ops, unsigned int *cnt, const t_chunk *upper, const t_chunk *lower)
{
	int upper_remaining = upper->max_val - upper->min_val + 1;
	int lower_remaining = lower->max_val - lower->min_val + 1;
	int val;

	while (upper_remaining > 0 || lower_remaining > 0)
	{
		val = deque_peek_at_Nth(&s->a_stack, 0);
		if (upper_remaining > 0 && chunk_contains(upper, val))
		{
			do_op(s, PB, ops, cnt);
			upper_remaining--;
		}
		else if (lower_remaining > 0 && chunk_contains(lower, val))
		{
			do_op(s, PB, ops, cnt);
			do_op(s, RB, ops, cnt);
			lower_remaining--;
		}
		else
		{
			do_op(s, RA, ops, cnt);
		}
	}
}

static size_t	find_min_index(const t_Deque *d)
{
	size_t	i;
	size_t	pos;
	int		min_val;
	size_t	min_idx;
	int		val;

	min_val = INT_MAX;
	min_idx = 0;
	pos = d->top;
	i = 0;
	while (i < d->size)
	{
		val = d->array[pos];
		if (val < min_val)
		{
			min_val = val;
			min_idx = i;
		}
		pos = (pos + 1) % DEQUE_CAPACITY;
		i++;
	}
	return (min_idx);
}

static void	move_all_chunks_a_to_b(t_Stacks *s, t_op *ops, unsigned int *op_count, const t_chunks *chunks)
{
	int center = chunks->count / 2;
	int pair_count = chunks->count / 2;
	for (int i = 0; i < pair_count; ++i)
	{
		const t_chunk *upper = &chunks->chunks[center + i];
		const t_chunk *lower = &chunks->chunks[center - 1 - i];
		move_two_chunks_to_b(s, ops, op_count, upper, lower);
	}
	if (chunks->count % 2 == 1)
	{
		const t_chunk *center_chunk = &chunks->chunks[center];
		int remaining = center_chunk->max_val - center_chunk->min_val + 1;
		int val;
		while (remaining > 0)
		{
			val = deque_peek_at_Nth(&s->a_stack, 0);
			if (chunk_contains(center_chunk, val))
			{
				do_op(s, PB, ops, op_count);
				remaining--;
			}
			else
				do_op(s, RA, ops, op_count);
		}
	}
}

static void	move_all_b_to_a(t_Stacks *s, t_op *ops, unsigned int *op_count)
{
	while (!deque_is_empty(&s->b_stack))
		do_op(s, PA, ops, op_count);
}

static void	rotate_b_to_top(t_Stacks *s, t_op *ops, unsigned int *cnt,
	size_t idx)
{
	if (idx <= s->b_stack.size / 2)
	{
	while (idx--)
	do_op(s, RB, ops, cnt);
	}
	else
	{
	idx = s->b_stack.size - idx;
	while (idx--)
	do_op(s, RRB, ops, cnt);
	}
}
static void	sort_chunk_from_b(t_Stacks *s, t_op *ops, unsigned int *cnt,
	size_t count)
{
	size_t	idx;

	while (count--)
	{
	idx = find_min_index(&s->b_stack);
	rotate_b_to_top(s, ops, cnt, idx);
	do_op(s, PA, ops, cnt);
	do_op(s, RA, ops, cnt);
	}
}

static void	sort_all_chunks(t_Stacks *s, t_op *ops, unsigned int *op_count, const t_chunks *chunks, size_t n)
{
	for (int i = 0; i < chunks->count; ++i)
	{
		size_t count = CHUNK_SIZE;
		if ((i + 1) * CHUNK_SIZE > (int)n)
			count = n - i * CHUNK_SIZE;
		for (size_t j = 0; j < (size_t)count; ++j)
			do_op(s, PB, ops, op_count);
		sort_chunk_from_b(s, ops, op_count, count);
	}
}

void		sort_stacks(t_Stacks *s, t_op *ops)
{
	const size_t	n = s->a_stack.size;
	t_chunks		chunks;
	unsigned int	op_count = 0;

	if ((int)n <= 1)
		return (ops[0] = LAST, (void)0);
	init_chunks(&chunks, n);
	move_all_chunks_a_to_b(s, ops, &op_count, &chunks);
	move_all_b_to_a(s, ops, &op_count);
	sort_all_chunks(s, ops, &op_count, &chunks, n);
	ops[op_count] = LAST;
}
