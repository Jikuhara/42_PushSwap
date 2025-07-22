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

static int	chunk_contains(int val, int min_val, int max_val)
{
	return (val >= min_val && val <= max_val);
}

static void	move_chunk_a_to_b(t_Stacks *s, t_op *ops, unsigned int *cnt,
				int min_val, int max_val)
{
	int	pushed;
	int	total;
	int	val;

	pushed = 0;
	total = max_val - min_val + 1;
	while (pushed < total)
	{
		val = deque_peek_at_Nth(&s->a_stack, 0);
		if (chunk_contains(val, min_val, max_val))
		{
			do_op(s, PB, ops, cnt);
			pushed++;
		}
		else
			do_op(s, RA, ops, cnt);
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

static void	move_all_chunks_a_to_b(t_Stacks *s, t_op *ops, unsigned int *op_count, size_t chunk_count, size_t n)
{
	size_t		  i;
	int			  min_val;
	int			  max_val;

	i = 0;
	while ((size_t)i < chunk_count)
	{
		min_val = (int)(i * CHUNK_SIZE);
		max_val = (int)((i + 1) * CHUNK_SIZE - 1);
		if (max_val >= (int)n)
			max_val = (int)n - 1;
		move_chunk_a_to_b(s, ops, op_count, min_val, max_val);
		i++;
	}
}

static void	move_all_b_to_a(t_Stacks *s, t_op *ops, unsigned int *op_count)
{
	while (!deque_is_empty(&s->b_stack))
		do_op(s, PA, ops, op_count);
}

static void	sort_all_chunks(t_Stacks *s, t_op *ops, unsigned int *op_count, size_t chunk_count, size_t n)
{
	size_t		  i;
	size_t		  count;

	i = 0;
	while ((size_t)i < chunk_count)
	{
		count = CHUNK_SIZE;
		if ((i + 1) * CHUNK_SIZE > n)
			count = n - i * CHUNK_SIZE;
		for (size_t j = 0; j < (size_t)count; ++j)
			do_op(s, PB, ops, op_count);
		sort_chunk_from_b(s, ops, op_count, count);
		i++;
	}
}

void		sort_stacks(t_Stacks *s, t_op *ops)
{
	const size_t	n = s->a_stack.size;
	const size_t	chunk_count = (n + CHUNK_SIZE - 1) / CHUNK_SIZE;
	unsigned int	op_count;

	op_count = 0;
	if (n <= 1)
		return (ops[0] = LAST, (void)0);
	move_all_chunks_a_to_b(s, ops, &op_count, chunk_count, n);
	move_all_b_to_a(s, ops, &op_count);
	sort_all_chunks(s, ops, &op_count, chunk_count, n);
	ops[op_count] = LAST;
}
