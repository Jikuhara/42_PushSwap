/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_5_quick_sort.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjikuhar <kjikuhar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 19:14:34 by kei2003730        #+#    #+#             */
/*   Updated: 2025/08/08 00:26:58 by kjikuhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define BASE_CASE 3
#include "push_swap.h"

static int	find_pivot(t_Stacks *stacks, int len)
{
	int	temp_array[INPUT_MAX_LIMIT];
	int	i, j, temp;
	int	pivot_pos;

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
	pivot_pos = len / 2;
	if (pivot_pos >= len)
		pivot_pos = len - 1;
	temp = temp_array[pivot_pos];
	return (temp);
}

// 2-way パーティション：ピボットより小さい値をスタックBに移動
static void	two_way_partition(t_Stacks *stacks, t_op *ops,
		unsigned int *op_count, int len, int pivot, int *smaller_count)
{
	int	processed;
	int	current;

	*smaller_count = 0;
	processed = 0;
	while (processed < len)
	{
		current = deque_peek_at_Nth(&stacks->a_stack, 0);
		if (current < pivot)
		{
			do_op(stacks, PB, ops, op_count);
			(*smaller_count)++;
		}
		else
		{
			do_op(stacks, RA, ops, op_count);
		}
		processed++;
	}
	processed = 0;
	while (processed < len - *smaller_count)
	{
		do_op(stacks, RRA, ops, op_count);
		processed++;
	}
}

// クイックソートの再帰部分
static void	quick_sort_recursive(t_Stacks *stacks, t_op *ops,
	unsigned int *op_count, int len)
{
	int	pivot;
	int	smaller_count;
	int	i;

	if (len <= 2)
	{
		sort_small_stack_constrained(stacks, ops, op_count, len);
		return ;
	}
	pivot = find_pivot(stacks, len);
	two_way_partition(stacks, ops, op_count, len, pivot, &smaller_count);
	i = 0;
	if (len - smaller_count > 1)
		quick_sort_recursive(stacks, ops, op_count, len - smaller_count);
	while (i < smaller_count)
	{
		do_op(stacks, PA, ops, op_count);
		i++;
	}
	if (smaller_count > 1)
		quick_sort_recursive(stacks, ops, op_count, smaller_count);
}

// メインのソート関数
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
