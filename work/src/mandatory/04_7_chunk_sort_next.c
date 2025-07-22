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

#include "../../includes/push_swap.h"

typedef struct s_chunk_info
{
	size_t	chunk_count;
	size_t	threshold[MAX_CHUNK];
}		t_chunk_info;

void	set_chunk_info(t_chunk_info *chunk_info, size_t size);

static void		first_divide_diff_2_and_3(t_chunk_info *c_info, t_Stacks *s, t_op *ops)
{
	int i = 0;
	int center = (4 + chunk_count - 1) / 2;
	int len = stacks->a_size;
	int inside_border_size = chunk_threshold[center + 1] - chunk_threshold[center];

	while (s->a_stack.size)
	{
		if (stacks->a_size == inside_border_size)
			break;
		if (to_go_b(stacks, chunk_threshold, center, chunk_count, is_second))
			do_op(stacks, PB, ops, op_count);
		else if (to_go_bottom_b(stacks, chunk_threshold, center, chunk_count))
		{
			do_op(stacks, PB, ops, op_count);
			do_op(stacks, RB, ops, op_count);
		}
		else
		{
			do_op(stacks, RA, ops, op_count);
		}
		i++;
	}
}

static void		second_divide_diff_0_and_1(t_chunk_info *c_info, t_Stack *s, t_op *ops)

void	divide_a_to_b_by_diff(t_chunk_info *c_info, t_Stacks *s t_op *ops)
{
	first_divide_diff_2_and_3(c_info, s, ops);
	second_divide_diff_0_and_1(c_info, s, ops);
}

void	split_b_to_a_by_chunks()
{

}

void	sort_each_chunks()
{

}

void	main_sort_function(t_Stacks *stacks, t_op *ops)
{
	t_chunk_info *chunk_info;

	set_chunk_info(chunk_info, stack->a_stack.size);
	divide_a_to_b_by_diff(chunk_info, stacks, ops);
	split_b_to_a_by_chunks();
	sort_each_chunks();
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
	else if (stacks->a_stack.size == 100 || stacks->a_stack.size == 500)
	{
		main_sort_function();
	}
	else
	{
		sub_sort_function();
	}
	ops[op_count] = LAST;
}
