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

void	split_each_chunks(t_Stacks *s, t_op *ops, unsigned int *op_count, const t_chunks *chunks)
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
	while (!deque_is_empty(&s->b_stack))
		do_op(s, PA, ops, op_count);
}
