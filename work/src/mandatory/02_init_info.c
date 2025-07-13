/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_init_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjikuhar <kjikuhar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 17:40:52 by kjikuhar          #+#    #+#             */
/*   Updated: 2025/05/23 21:35:30 by kjikuhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	init_info(t_Stacks *Stacks)
{
	deque_init(&Stacks->a_stack);
	deque_init(&Stacks->b_stack);
}
