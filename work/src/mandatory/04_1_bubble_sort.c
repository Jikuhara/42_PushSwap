/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_1_bubble_sort.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kei2003730 <kei2003730@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 21:14:49 by kjikuhar          #+#    #+#             */
/*   Updated: 2025/07/14 08:36:47 by kei2003730       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* bubble_sort */
static void	execute_bubble_cycle(t_Stacks *stacks, t_op *ops,
		t_op *op_count, int *swapped)
{
	int	j;
	int	size;

	size = stacks->a_stack.size;
	*swapped = 0;
	j = 0;
	while (j < size - 1)
	{
		if (deque_peek_at_Nth(&stacks->a_stack,
				0) > deque_peek_at_Nth(&stacks->a_stack, 1))
		{
			do_op(stacks, SA, ops, op_count);
			*swapped = 1;
		}
		do_op(stacks, RA, ops, op_count);
		j++;
	}
	do_op(stacks, RA, ops, op_count);
}

void	sort_stacks(t_Stacks *stacks, t_op *ops)
{
	const size_t	size = stacks->a_stack.size;
	unsigned int	op_count;
	int				swapped;

	op_count = 0;
	if (size <= 1)
		return (ops[0] = LAST, (void)0);
	swapped = 1;
	while (swapped)
	{
		execute_bubble_cycle(stacks, ops, &op_count, &swapped);
	}
	ops[op_count] = LAST;
}
