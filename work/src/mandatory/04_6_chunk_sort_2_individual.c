/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_2_LISsort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kei2003730 <kei2003730@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 13:48:20 by kei2003730        #+#    #+#             */
/*   Updated: 2025/07/14 08:26:09 by kei2003730       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "chunk_sort.h"

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

static size_t	find_max_index(const t_Deque *d)
{
	size_t	i;
	size_t	pos;
	size_t	max_idx;
	int		max_val;
	int		val;

	max_val = INT_MIN;
	max_idx = 0;
	pos = d->top;
	i = 0;
	while (i < d->size)
	{
		val = d->array[pos];
		if (val > max_val)
		{
			max_val = val;
			max_idx = i;
		}
		pos = (pos + 1) % DEQUE_CAPACITY;
		i++;
	}
	return (max_idx);
}

static size_t	select_best_rotation(const t_Deque *b, size_t *out_idx, int *is_min)
{
	size_t	min_idx;
	size_t	max_idx;
	size_t	size;
	size_t	dist_top_min;
	size_t	dist_top_max;
	size_t	dist_bottom_min;
	size_t	dist_bottom_max;
	size_t	min_dist;

	min_idx = find_min_index(b);
	max_idx = find_max_index(b);
	size = b->size;
	dist_top_min = min_idx;
	dist_top_max = max_idx;
	dist_bottom_min = size - min_idx;
	dist_bottom_max = size - max_idx;
	min_dist = dist_top_min;
	*out_idx = min_idx;
	*is_min = 1;
	if (dist_top_max < min_dist)
	{
		min_dist = dist_top_max;
		*out_idx = max_idx;
		*is_min = 0;
	}
	if (dist_bottom_min < min_dist)
	{
		min_dist = dist_bottom_min;
		*out_idx = min_idx;
		*is_min = 1;
	}
	if (dist_bottom_max < min_dist)
	{
		min_dist = dist_bottom_max;
		*out_idx = max_idx;
		*is_min = 0;
	}
	return (min_dist);
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
	int	max_pa_count;
	int	b_top;
	size_t	min_idx;
	size_t	max_idx;
	int	min_val;
	int	max_val;
	size_t	best_idx;
	int	is_min;
	int	i;

	max_pa_count = 0;
	while (count > 0)
	{
		b_top = deque_peek_at_Nth(&s->b_stack, 0);
		min_idx = find_min_index(&s->b_stack);
		max_idx = find_max_index(&s->b_stack);
		min_val = s->b_stack.array[(s->b_stack.top + min_idx) % DEQUE_CAPACITY];
		max_val = s->b_stack.array[(s->b_stack.top + max_idx) % DEQUE_CAPACITY];
		if (b_top == min_val)
		{
			do_op(s, PA, ops, cnt);
			do_op(s, RA, ops, cnt);
			count--;
		}
		else if (b_top == max_val)
		{
			do_op(s, PA, ops, cnt);
			max_pa_count++;
			count--;
		}
		else
		{
			select_best_rotation(&s->b_stack, &best_idx, &is_min);
			rotate_b_to_top(s, ops, cnt, best_idx);
		}
	}
	i = 0;
	while (i < max_pa_count)
	{
		do_op(s, RA, ops, cnt);
		i++;
	}
}

void	sort_all_chunks(t_Stacks *s, t_op *ops, unsigned int *op_count, const t_chunks *chunks)
{
	for (int i = 0; i < chunks->count; ++i)
	{
		size_t count = chunks->chunks[i].size;
		for (size_t j = 0; j < count; ++j)
			do_op(s, PB, ops, op_count);
		sort_chunk_from_b(s, ops, op_count, count);
	}
}
