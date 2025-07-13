/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selection_sort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjikuhar <kjikuhar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 20:17:32 by kjikuhar          #+#    #+#             */
/*   Updated: 2025/05/07 20:33:41 by kjikuhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"

void selection_sort(int *data[], int n)
{
	int	tmp;
	int	min;

	for (size_t i = 0; i < n - 1; i++)
	{
		min = i;
		for (size_t j = i + 1; j < n; j++)
		{
			if (*data[j] < *data[min])
				min = j;
		}
		ft_swap (data[i], data[min]);
	}

}

int main(void)
{
	int	data[] = {1, 2, 3, 4, 5, 7, 6};
	int count = sizeof(data) / sizeof(data[0]);
	for (size_t i = 0; i < count; i++)
		printf("%zu : %d\n", i, data[i]);
	selection_sort(&data, count);
	for (size_t i = 0; i < count; i++)
		printf("%zu : %d\n", i, data[i]);
	return (0);
}
