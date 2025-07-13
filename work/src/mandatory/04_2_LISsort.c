/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_2_LISsort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kei2003730 <kei2003730@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 13:48:20 by kei2003730        #+#    #+#             */
/*   Updated: 2025/07/14 08:26:09 by kei2003730       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_stacks(t_Stacks *stacks, t_op *ops)
{
    unsigned int	op_count;
    t_chunk			initial_chunk;

    op_count = 0;
    if (stacks->a_stack.size <= 1)
        return (ops[0] = LAST, (void)0);
    if (stacks->a_stack.size <= BASE_CASE)
    {
        sort_small_stack_constrained(stacks, ops, &op_count,
            stacks->a_stack.size);
        ops[op_count] = LAST;
        return ;
    }
    
    ops[op_count] = LAST;
}

void    dicide_lis_tag(t_Stacks *stacks, t_op *ops)
{
    
}