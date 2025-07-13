/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjikuhar <kjikuhar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 15:46:01 by kjikuhar          #+#    #+#             */
/*   Updated: 2025/06/02 21:16:18 by kjikuhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	exit_with_error(void)
{
	ft_putendl_fd(ERR_MSG, 2);
	exit(EXIT_FAILURE);
}

int	main(int argc, char const *argv[])
{
	t_Stacks	stacks;
	t_op		ops[OPS_MAX];

	is_valid_int(argc, argv);
	init_info(&stacks);
	parse_num(argc, argv, stacks.a_stack.array);
	stacks.a_stack.size = argc - 1;
	stacks.a_stack.bottom = argc - 1;
	sort_stacks(&stacks, ops);
	print_operation(ops);
	exit(EXIT_SUCCESS);
}
