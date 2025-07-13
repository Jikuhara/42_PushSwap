/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_1_radix_sort.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kei2003730 <kei2003730@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 16:00:37 by kjikuhar          #+#    #+#             */
/*   Updated: 2025/06/10 13:25:23 by kei2003730       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* radix_sort */
static int	get_max_bits(size_t n)
{
	int	max_bits;

	max_bits = 0;
	while ((n - 1) >> max_bits)
		++max_bits;
	return (max_bits);
}

static void	process_single_bit(t_Stacks *stacks, unsigned char *ops,
		t_op *op_count, int bit)
{
	size_t	j;
	size_t	n;
	int		val;

	n = stacks->a_stack.size;
	j = 0;
	while (j < n)
	{
		val = deque_peek_at_Nth(&stacks->a_stack, 0);
		if ((val >> bit) & 1)
			do_op(stacks, RA, ops, op_count);
		else
			do_op(stacks, PB, ops, op_count);
		j++;
	}

}

static void	return_all_to_stack_a(t_Stacks *stacks, unsigned char *ops,
	t_op *op_count)
{
while (!deque_is_empty(&stacks->b_stack))
	do_op(stacks, PA, ops, op_count);
}

void	sort_stacks(t_Stacks *stacks, unsigned char *ops)
{
	const size_t	n = stacks->a_stack.size;
	unsigned int	op_count;
	int				max_bits;
	int				bit;

	op_count = 0;
	if (n <= 1)
		return (ops[0] = LAST, (void)0);
	max_bits = get_max_bits(n);
	bit = 0;
	while (bit < max_bits)
	{
		process_single_bit(stacks, ops, &op_count, bit);
		return_all_to_stack_a(stacks, ops, &op_count);
		bit++;
	}
	ops[op_count] = LAST;
}
