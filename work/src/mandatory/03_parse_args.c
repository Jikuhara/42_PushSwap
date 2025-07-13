/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_parse_num.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjikuhar <kjikuhar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 17:55:02 by kjikuhar          #+#    #+#             */
/*   Updated: 2025/05/23 21:52:14 by kjikuhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

bool	depulication_exists(int *tab, int size)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = i + 1;
		while (j < size)
		{
			if (tab[i] == tab[j])
				return (true);
			j++;
		}
		i++;
	}
	return (false);
}

static void	coordinate_compression(int *tab, int size)
{
	int	i;
	int	j;
	int	original[size];

	i = 0;
	while (i < size)
	{
		original[i] = tab[i];
		i++;
	}
	ft_bzero(tab, sizeof(int) * size);
	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			if (original[i] > original[j])
				tab[i]++;
			j++;
		}
		i++;
	}
}

void	parse_num(int argc, char const *argv[], int *tab)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		tab[i - 1] = ft_atoi(argv[i]);
		i++;
	}
	if (depulication_exists(tab, argc - 1))
		exit_with_error();
	coordinate_compression(tab, argc - 1);
}
