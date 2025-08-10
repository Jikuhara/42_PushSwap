/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_2_insertion_sort.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjikuhar <kjikuhar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 15:38:38 by kjikuhar          #+#    #+#             */
/*   Updated: 2025/08/08 00:49:31 by kjikuhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#define BASE_CASE 2

/* insertion_sort */
static void	insert_element_to_stack_b(t_Stacks *stacks, t_op *ops,
		t_op *op_count)
{
	unsigned int	rb_count;
	unsigned int	i;
	unsigned int	a_value;
	unsigned int	b_value;

	a_value = deque_peek_at_Nth(&stacks->a_stack, 0);
	rb_count = 0;
	i = 0;
	while (i < stacks->b_stack.size)
	{
		b_value = deque_peek_at_Nth(&stacks->b_stack, i);
		if (a_value > b_value)
			break ;
		i++;
	}
	while (rb_count < i)
	{
		do_op(stacks, RB, ops, op_count);
		rb_count++;
	}
	do_op(stacks, PB, ops, op_count);
	while (rb_count-- > 0)
		do_op(stacks, RRB, ops, op_count);
}

static void	return_all_to_stack_a(t_Stacks *stacks, t_op *ops,
		t_op *op_count)
{
	while (!deque_is_empty(&stacks->b_stack))
		do_op(stacks, PA, ops, op_count);
}

void	sort_stacks(t_Stacks *stacks, t_op *ops)
{
	unsigned int	op_count;

	op_count = 0;
	if (stacks->a_stack.size <= 1)
		return (ops[0] = LAST, (void)0);
	else if (stacks->a_stack.size <= BASE_CASE)
	{
		sort_small_stack_constrained(stacks, ops, &op_count,
			stacks->a_stack.size);
	}
	else
	{
		while (!deque_is_empty(&stacks->a_stack))
			insert_element_to_stack_b(stacks, ops, &op_count);
		return_all_to_stack_a(stacks, ops, &op_count);
	}
	ops[op_count] = LAST;
}
