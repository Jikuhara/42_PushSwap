/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_1_Quick_sort.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kei2003730 <kei2003730@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 19:14:34 by kei2003730        #+#    #+#             */
/*   Updated: 2025/07/14 08:25:48 by kei2003730       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define BASE_CASE 3
#include "push_swap.h"

static void	find_dual_pivots(t_Stacks *stacks, int len, int *pivot1,
		int *pivot2)
{
	int	*temp_array;
	int	i, j, temp;
	int	pos1, pos2;

	temp_array = malloc(sizeof(int) * len);
	if (!temp_array)
		exit_with_error();
	i = 0;
	while (i < len)
	{
		temp_array[i] = deque_peek_at_Nth(&stacks->a_stack, i);
		i++;
	}
	i = 0;
	while (i < len - 1)
	{
		j = 0;
		while (j < len - i - 1)
		{
			if (temp_array[j] > temp_array[j + 1])
			{
				temp = temp_array[j];
				temp_array[j] = temp_array[j + 1];
				temp_array[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
	pos1 = len / 3;
	pos2 = (len * 2) / 3;
	if (pos1 >= len)
		pos1 = len - 1;
	if (pos2 >= len)
		pos2 = len - 1;
	if (pos1 == pos2 && len > 1)
		pos2 = pos1 + 1;
	if (pos2 >= len)
		pos2 = len - 1;
	*pivot1 = temp_array[pos1];
	*pivot2 = temp_array[pos2];
	free(temp_array);
}

// 3-Way パーティション：2つのピボットで3分割
static void	three_way_partition(t_Stacks *stacks, t_op *ops,
		unsigned int *op_count, int len, int pivot1, int pivot2,
		int *small_count, int *mid_count, int *large_count)
{
	int	processed;
	int	current;
	int i;

	*small_count = 0;
	*mid_count = 0;
	*large_count = 0;
	processed = 0;
	while (processed < len)
	{
		current = deque_peek_at_Nth(&stacks->a_stack, 0);
		if (current < pivot1)
		{
			do_op(stacks, PB, ops, op_count);
			(*small_count)++;
		}
		else if (current < pivot2)
		{
			do_op(stacks, PB, ops, op_count);
			do_op(stacks, RB, ops, op_count);
			(*mid_count)++;
		}
		else
		{
			do_op(stacks, RA, ops, op_count);
			(*large_count)++;
		}
		processed++;
	}
	i = 0;
	while (i < *large_count)
	{
		do_op(stacks, RRA, ops, op_count);
		i++;
	}
	i = 0;
	while (i < *mid_count)
	{
		do_op(stacks, RRB, ops, op_count);
		i++;
	}
}

static void	quick_sort_recursive(t_Stacks *stacks, t_op *ops,
	unsigned int *op_count, int len)
{
	int	pivot1, pivot2;
	int	small_count, mid_count, large_count;
	int i;

	if (len <= BASE_CASE)
	{
		sort_small_stack_constrained(stacks, ops, op_count, len);
		return ;
	}
	find_dual_pivots(stacks, len, &pivot1, &pivot2);
	three_way_partition(stacks, ops, op_count, len, pivot1, pivot2,
		&small_count, &mid_count, &large_count);
	if (large_count > 1)
		quick_sort_recursive(stacks, ops, op_count, large_count);
	i = 0;
	while (i < mid_count)
	{
		do_op(stacks, PA, ops, op_count);
		i++;
	}
	if (mid_count > 1)
		quick_sort_recursive(stacks, ops, op_count, mid_count);
	i = 0;
	while (i < small_count)
	{
		do_op(stacks, PA, ops, op_count);
		i++;
	}
	if (small_count > 1)
		quick_sort_recursive(stacks, ops, op_count, small_count);
}

void	sort_stacks(t_Stacks *stacks, t_op *ops)
{
	unsigned int	op_count;

	op_count = 0;
	if (stacks->a_stack.size <= 1)
		return (ops[0] = LAST, (void)0);
	if (stacks->a_stack.size <= BASE_CASE)
		sort_small_stack_constrained(stacks, ops, &op_count,
			stacks->a_stack.size);
	else
		quick_sort_recursive(stacks, ops, &op_count, stacks->a_stack.size);
	ops[op_count] = LAST;
}
