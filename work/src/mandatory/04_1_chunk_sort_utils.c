/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_1_chunk_sort_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjikuhar <kjikuhar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:24:51 by kjikuhar          #+#    #+#             */
/*   Updated: 2025/06/02 21:18:57 by kjikuhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "chunk_sort.h"

void	init_size(t_chunk *min, t_chunk *mid, t_chunk *max)
{
	min->size = 0;
	mid->size = 0;
	max->size = 0;
}

/* チャンクが既にソート済みかチェック */
bool	is_chunk_sorted(t_Stacks *stacks, t_chunk chunk)
{
	int	i;
	int	current;
	int	next;

	if (chunk.size <= 1)
		return (true);
	i = 0;
	while (i < chunk.size - 1)
	{
		if (chunk.position == TOP_A)
		{
			current = deque_peek_at_Nth(&stacks->a_stack, i);
			next = deque_peek_at_Nth(&stacks->a_stack, i + 1);
			if (current > next)
				return (false);
		}
		else if (chunk.position == BOTTOM_A)
		{
			current = deque_peek_at_Nth(&stacks->a_stack, stacks->a_stack.size
					- chunk.size + i);
			next = deque_peek_at_Nth(&stacks->a_stack, stacks->a_stack.size
					- chunk.size + i + 1);
			if (current > next)
				return (false);
		}
		else if (chunk.position == TOP_B)
		{
			current = deque_peek_at_Nth(&stacks->b_stack, i);
			next = deque_peek_at_Nth(&stacks->b_stack, i + 1);
			if (current < next)
				return (false);
		}
		else if (chunk.position == BOTTOM_B)
		{
			current = deque_peek_at_Nth(&stacks->b_stack, stacks->b_stack.size
					- chunk.size + i);
			next = deque_peek_at_Nth(&stacks->b_stack, stacks->b_stack.size
					- chunk.size + i + 1);
			if (current < next)
				return (false);
		}
		i++;
	}
	return (true);
}


// チャンクを指定されたポジションに移動
void	move_chunk_to_position(t_Stacks *stacks, t_op *ops,
		t_op *op_count, t_chunk *chunk, t_position target)
{
	int	i;

	if (chunk->position == target)
		return ;
	// 効率的な移動：最小限の操作で移動
	if (chunk->position == TOP_B && target == TOP_A)
	{
		// TOP_B -> TOP_A: すべてPA
		i = 0;
		while (i < chunk->size)
		{
			do_op(stacks, PA, ops, op_count);
			i++;
		}
	}
	else if (chunk->position == BOTTOM_B && target == TOP_A)
	{
		// BOTTOM_B -> TOP_A: RRB + PA
		i = 0;
		while (i < chunk->size)
		{
			do_op(stacks, RRB, ops, op_count);
			do_op(stacks, PA, ops, op_count);
			i++;
		}
	}
	else if (chunk->position == BOTTOM_A && target == TOP_A)
	{
		// BOTTOM_A -> TOP_A: すべてRRA
		i = 0;
		while (i < chunk->size)
		{
			do_op(stacks, RRA, ops, op_count);
			i++;
		}
	}
	else if (chunk->position == TOP_A && target == TOP_B)
	{
		// TOP_A -> TOP_B: すべてPB
		i = 0;
		while (i < chunk->size)
		{
			do_op(stacks, PB, ops, op_count);
			i++;
		}
	}
	else if (chunk->position == BOTTOM_A && target == TOP_B)
	{
		// BOTTOM_A -> TOP_B: RRA + PB
		i = 0;
		while (i < chunk->size)
		{
			do_op(stacks, RRA, ops, op_count);
			do_op(stacks, PB, ops, op_count);
			i++;
		}
	}
	else if (chunk->position == BOTTOM_A && target == TOP_B)
	{
		// BOTTOM_B -> TOP_B: RRB
		i = 0;
		while (i < chunk->size)
		{
			do_op(stacks, RRB, ops, op_count);
			i++;
		}
	}
	else if (chunk->position == TOP_A && target == BOTTOM_A)
	{
		// TOP_A -> BOTTOM_A: すべてRA
		i = 0;
		while (i < chunk->size)
		{
			do_op(stacks, RA, ops, op_count);
			i++;
		}
	}
	else if (chunk->position == TOP_A && target == BOTTOM_A)
	{
		// TOP_B -> BOTTOM_A: すべてRA
		i = 0;
		while (i < chunk->size)
		{
			do_op(stacks, PA, ops, op_count);
			do_op(stacks, RA, ops, op_count);
			i++;
		}
	}
	else if (chunk->position == TOP_A && target == BOTTOM_A)
	{
		// BOTTOM_B -> BOTTOM_A: すべてRA
		i = 0;
		while (i < chunk->size)
		{
			do_op(stacks, RRB, ops, op_count);
			do_op(stacks, PA, ops, op_count);
			do_op(stacks, RA, ops, op_count);
			i++;
		}
	}
	else if (chunk->position == TOP_B && target == BOTTOM_B)
	{
		// TOP_B -> BOTTOM_B: すべてRB
		i = 0;
		while (i < chunk->size)
		{
			do_op(stacks, RB, ops, op_count);
			i++;
		}
	}
	else if (chunk->position == TOP_B && target == BOTTOM_B)
	{
		// TOP_A -> BOTTOM_B: すべてRB
		i = 0;
		while (i < chunk->size)
		{
			do_op(stacks, PB, ops, op_count);
			do_op(stacks, RB, ops, op_count);
			i++;
		}
	}
	else if (chunk->position == TOP_B && target == BOTTOM_B)
	{
		// BOTTOM_A -> BOTTOM_B: すべてRB
		i = 0;
		while (i < chunk->size)
		{
			do_op(stacks, RRA, ops, op_count);
			do_op(stacks, PB, ops, op_count);
			do_op(stacks, RB, ops, op_count);
			i++;
		}
	}
	chunk->position = target;
}
