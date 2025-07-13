/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjikuhar <kjikuhar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 15:04:32 by kjikuhar          #+#    #+#             */
/*   Updated: 2025/05/21 15:39:52 by kjikuhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

int	*create_table(size_t count, ...)
{
	int		*tab;
	size_t	i;
	va_list	args;

	tab = malloc(sizeof(int) * count);
	if (!tab)
		return (NULL);
	va_start(args, count);
	i = 0;
	while (i < count)
	{
		tab[i] = va_arg(args, int);
		i++;
	}
	return (tab);
}

void	print_table(size_t count, int *tab)
{
	printf("tabを出力。\n");
	for (size_t i = 0; i < count; i++)
		printf("%3zu : ", i);
	printf("\n");
	for (size_t i = 0; i < count; i++)
		printf("%3d : ", tab[i]);
	printf("\n");
	printf("出力完了。\n");
	return ;
}

void	print_array(int *tab, size_t count, size_t step)
{
	printf("step_%zu: ", step);
	for (size_t i = 0; i < count; i++)
	{
		printf("%d ", tab[i]);
	}
	putchar('\n');
}

void	ft_swap(int *a, int *b)
{
	int	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	selection_sort(int *tab, size_t count)
{
	size_t	min;
	size_t	step = 0;

	print_array(tab, count, step++);
	for (size_t i = 0; i + 1 < count; i++)
	{
		min = i;
		for (size_t j = i + 1; j < count; j++)
		{
			if (tab[j] < tab[min])
				min = j;
		}
		if (min != i)
			ft_swap(&tab[i], &tab[min]);
		print_array(tab, count, step++);
	}
}

void	buble_sort(int *tab, size_t count)
{
	size_t	step = 0;
	print_array(tab, count, step++);
	for (size_t i = 0; i < count; i++)
	{
		for (size_t j = i + 1; j < count; j++)
		{
			if (tab[i] > tab[j])
				ft_swap(&tab[i], &tab[j]);
		}
		print_array(tab, count, step++);
	}
}

int	main(void)
{
	size_t	count;
	int		*tab;
	int		tab_cpy[] = {42, 24, 7, 101, 111};

	count = 5;
	printf("buble_sort\n");
	tab = create_table(count, 2, 1, 5, 10, 9);
	buble_sort(tab, count);

	printf("selsction_sort\n");
	tab = create_table(count, 2, 1, 5, 10, 9);
	selection_sort(tab, count);
	return (0);
}
