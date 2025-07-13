/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_0_sort_small_stack_constrained.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjikuhar <kjikuhar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 01:15:42 by kei2003730        #+#    #+#             */
/*   Updated: 2025/06/02 21:25:06 by kjikuhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	sort_two_elements_constrained(t_Stacks *stacks, t_op *ops,
		t_op *op_count)
{
	if (deque_peek_at_Nth(&stacks->a_stack,
			0) > deque_peek_at_Nth(&stacks->a_stack, 1))
		do_op(stacks, SA, ops, op_count);
}

static void	sort_three_elements_constrained(t_Stacks *stacks, t_op *ops,
		t_op *op_count)
{
	int	a[3];

	for (int i = 0; i < 3; i++)
		a[i] = deque_peek_at_Nth(&stacks->a_stack, i);
	// [1,2,3] -> already sorted
	if (a[0] < a[1] && a[1] < a[2])
		return ;
	// [2,1,3] -> SA
	else if (a[0] > a[1] && a[1] < a[2] && a[0] < a[2])
		do_op(stacks, SA, ops, op_count);
	// [1,3,2] -> 1をBに移動、3と2をソート、1を戻す
	else if (a[0] < a[1] && a[1] > a[2] && a[0] < a[2])
	{
		do_op(stacks, PB, ops, op_count); // [3,2] [1]
		do_op(stacks, SA, ops, op_count); // [2,3] [1]
		do_op(stacks, PA, ops, op_count); // [1,2,3]
	}
	// [3,1,2] -> 最小値1を上に持ってきてからソート
	else if (a[0] > a[1] && a[1] < a[2] && a[0] > a[2])
	{
		do_op(stacks, SA, ops, op_count); // [1,3,2]
		do_op(stacks, PB, ops, op_count); // [3,2] [1]
		do_op(stacks, SA, ops, op_count); // [2,3] [1]
		do_op(stacks, PA, ops, op_count); // [1,2,3]
	}
	// [2,3,1] -> 最小値1をBに退避、2と3をソート、最後に1を配置
	else if (a[0] < a[1] && a[1] > a[2] && a[0] > a[2])
	{
		do_op(stacks, PB, ops, op_count);  // [3,1] [2]
		do_op(stacks, PB, ops, op_count);  // [1] [2,3]
		do_op(stacks, RA, ops, op_count);  // [3,1] [2]
		do_op(stacks, PA, ops, op_count);  // [1,3] [2]
		do_op(stacks, PA, ops, op_count);  // [2,1,3]
		do_op(stacks, RRA, ops, op_count); // [1,2,3]
	}
	// [3,2,1] -> 最小値1をBに退避、残りをソート
	else if (a[0] > a[1] && a[1] > a[2])
	{
		do_op(stacks, PB, ops, op_count);  // [2,1] [3]
		do_op(stacks, PB, ops, op_count);  // [1] [3,2]
		do_op(stacks, RA, ops, op_count);  // [2,1] [3]
		do_op(stacks, SB, ops, op_count);  // [2,1] [3]
		do_op(stacks, PA, ops, op_count);  // [3,1,2]
		do_op(stacks, PA, ops, op_count);  // [1,2,3]
		do_op(stacks, RRA, ops, op_count); // [1,2,3]
	}
}

/* 4 要素専用・使用可能命令は SA / PB / PA / RA / RRA */
/* 下の要素の位置関係を崩さずにソートする */
static void	sort_four_elements_constrained(t_Stacks *stacks, t_op *ops,
		t_op *op_count)
{
	int	min_val;
	int	min_idx;
	int	a[4];

	for (int i = 0; i < 4; i++)
		a[i] = deque_peek_at_Nth(&stacks->a_stack, i);
	if (a[0] < a[1] && a[1] < a[2] && a[2] < a[3])
		return ;
	if (a[0] > a[1] && a[1] < a[2] && a[2] < a[3] && a[0] < a[2])
	{
		do_op(stacks, SA, ops, op_count); // [a[1],a[0],a[2],a[3]]
		return ;
	}
	if (a[1] < a[0] && a[0] < a[2] && a[2] < a[3] && a[1] < a[2])
	{
		do_op(stacks, SA, ops, op_count);
		// [a[0],a[1],a[2],a[3]]
		do_op(stacks, RRA, ops, op_count);
		// [a[1],a[2],a[3],a[0]]
		sort_three_elements_constrained(stacks, ops, op_count);
		// [a[1],a[2],a[3]]
		do_op(stacks, RA, ops, op_count);
		// [a[2],a[3],a[0],a[1]]
		return ;
	}
	if (a[3] >= a[0] && a[3] >= a[1] && a[3] >= a[2])
	{
		sort_three_elements_constrained(stacks, ops, op_count);
		return ;
	}
	if (a[0] < a[1] && a[1] < a[2] && a[2] < a[3])
		return ;
	min_val = a[0];
	min_idx = 0;
	for (int i = 0; i < 4; i++)
		if (a[i] < min_val)
			min_val = a[i];
	for (int i = 0; i < min_idx; i++)
		do_op(stacks, RA, ops, op_count);
	do_op(stacks, PB, ops, op_count);
	for (int i = 0; i < min_idx; i++)
		do_op(stacks, RRA, ops, op_count);
}

static void	sort_five_elements_constrained(t_Stacks *stacks, t_op *ops,
		t_op *op_count)
{
	int	a[5];
	int	min_val;
	int	min_idx;

	for (int i = 0; i < 5; i++)
		a[i] = deque_peek_at_Nth(&stacks->a_stack, i);
	if (a[0] < a[1] && a[1] < a[2] && a[2] < a[3] && a[3] < a[4])
		return ;
	min_val = a[0];
	min_idx = 0;
	for (int i = 0; i < 5; i++)
		if (a[i] < min_val)
			min_val = a[i];
	for (int i = 0; i < min_idx; i++)
		do_op(stacks, RA, ops, op_count);
	do_op(stacks, PB, ops, op_count);
	for (int i = 0; i < min_idx; i++)
		do_op(stacks, RRA, ops, op_count);
	sort_four_elements_constrained(stacks, ops, op_count);
	do_op(stacks, PA, ops, op_count);
}
void	sort_small_stack_constrained(t_Stacks *stacks, t_op *ops,
		unsigned int *op_count, int len)
{
	if (len == 1)
		return ;
	else if (len == 2)
		sort_two_elements_constrained(stacks, ops, op_count);
	else if (len == 3)
		sort_three_elements_constrained(stacks, ops, op_count);
	else if (len == 4)
		sort_four_elements_constrained(stacks, ops, op_count);
	else if (len == 5)
		sort_five_elements_constrained(stacks, ops, op_count);
}
