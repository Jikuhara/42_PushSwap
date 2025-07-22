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

#include "push_swap.h"

typedef struct s_chunk_info
{
	size_t	chunk_count;
	int	threshold[MAX_CHUNK];
}		t_chunk_info;

void	set_chunk_division(t_chunk_info *chunk_info, size_t size)
{
	if (size == 100)
	{
		chunk_info->chunk_count = 13;

	}
	else
	{
		chunk_info->chunk_count = MAX_CHUNK;
	}
}

void set_chunk_threshold(t_chunk_info *chunk_info, int chunk_count)
{
	int base_size = 500 / chunk_count;

	int chunk_size_delta[21] = {
		0, 0, 0, 0, -3, 0, 0, 0, -3, -5, -5, 8, 12, 5, 5, 5, 3, 3, 3, 3, 7
	};
	for (int i = 0; i < chunk_count; i++) {
		chunk_info->threshold[i] = base_size + chunk_size_delta[i];
	}
}

void	set_chunk_info(t_chunk_info *chunk_info, size_t size)

{
	set_chunk_division(chunk_info, size);
	set_chunk_threshold(chunk_info, size);

}
