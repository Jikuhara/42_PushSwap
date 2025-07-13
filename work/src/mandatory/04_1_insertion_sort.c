/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_1_insertion_sort.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kei2003730 <kei2003730@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 15:38:38 by kjikuhar          #+#    #+#             */
/*   Updated: 2025/07/14 08:25:26 by kei2003730       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* insertion_sort */
// Stack Aの先頭の要素をStack Bの適切な位置(RBを用いて)に移動する。
// その後、RBした回数分RRBして、もとに戻す。
// 最後にPAをN回使用して、Stack Aに戻す。
static void	insert_element_to_stack_b(t_Stacks *stacks, unsigned char *ops,
		t_op *op_count)
{
	int	rb_count;
	int	i;
	int	a_value;
	int	b_value;

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

static void	return_all_to_stack_a(t_Stacks *stacks, unsigned char *ops,
		t_op *op_count)
{
	while (!deque_is_empty(&stacks->b_stack))
		do_op(stacks, PA, ops, op_count);
}

void	sort_stacks(t_Stacks *stacks, unsigned char *ops)
{
	unsigned int	op_count;

	op_count = 0;
	if (stacks->a_stack.size <= 1)
		return (ops[0] = LAST, (void)0);
	do_op(stacks, PB, ops, &op_count);
	while (!deque_is_empty(&stacks->a_stack))
		insert_element_to_stack_b(stacks, ops, &op_count);
	return_all_to_stack_a(stacks, ops, &op_count);
	ops[op_count] = LAST;
}
