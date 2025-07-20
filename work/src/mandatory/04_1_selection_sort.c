/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_1_selection_sort.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kei2003730 <kei2003730@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 21:14:05 by kjikuhar          #+#    #+#             */
/*   Updated: 2025/07/14 08:26:00 by kei2003730       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	min(t_Deque *deque)
{
	int		min_val;
	size_t	idx;
	size_t	i;

	if (deque_is_empty(deque))
		return (INT_MAX);
	min_val = INT_MAX;
	idx = deque->top;
	i = 0;
	while (i < deque->size)
	{
		if (deque->array[idx] < min_val)
			min_val = deque->array[idx];
		idx = (idx + 1) % DEQUE_CAPACITY;
		i++;
	}
	return (min_val);
}

/* selection_sort */
void	sort_stacks(t_Stacks *stacks, t_op *ops)
{
	unsigned int	op_count;

	if (stacks->a_stack.size <= 1)
	{
		ops[0] = LAST;
		return ;
	}
	op_count = 0;
	while (!deque_is_empty(&stacks->a_stack))
	{
		while (stacks->a_stack.array[stacks->a_stack.top]
			!= min(&stacks->a_stack))
			do_op(stacks, RA, ops, &op_count);
		do_op(stacks, PB, ops, &op_count);
	}
	while (!deque_is_empty(&stacks->b_stack))
		do_op(stacks, PA, ops, &op_count);
	ops[op_count] = LAST;
}
