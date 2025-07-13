/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjikuhar <kjikuhar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 18:08:15 by kjikuhar          #+#    #+#             */
/*   Updated: 2025/05/26 19:54:21 by kjikuhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int argc, char *argv[])
{
	int				tab[INPUT_MAX_LIMIT];
	unsigned char	ops[OPS_MAX];

	is_valid_input(argc, argv);
	parse_args(argc, argv, tab, ops);
	exec_ops(tab, ops);
	if (check_sort(tab))
		printf("OK\n");
	else
		printf("NG\n");
}

void	is_valid_ops(int argc, char *argv[])
{
	/* ちょっとわからんなぁ */
}

void	is_valid_input(int argc, char *argv[])
{
	is_valid_int(argc, argv);
	is_valid_ops(argc, argv);
}

void	parse_args(int argc, char argv[], int *tab, unsigned char *ops)
{
	parse_num(&argc, &argv, tab);
	parse_ops(&argc, &argv, ops);
}

void	exec_ops(int *tab, unsigned char *ops)
{
	unsigned int	i;
	
	i = 0;
	while (ops[i] != LAST)
	{
		operation(A, B, ops[i]);
		i++;
	}
}

bool	check_sort(int *tab)
{
	unsigned int	i;

	if (!tab)
		return (false);
	i = 1;
	while (tab + i)
	{
		if (tab[i] < tab[i - 1])
			return (false);
		i++;
	}
	return (true);
}
