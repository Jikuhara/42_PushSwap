/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk_sort.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjikuhar <kjikuhar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:25:50 by kjikuhar          #+#    #+#             */
/*   Updated: 2025/06/02 21:19:27 by kjikuhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHUNK_SORT_H
# define CHUNK_SORT_H

# include "push_swap.h"
# define CHUNK_SIZE 42
# define MAXCHUNK 100

typedef struct s_chunk {
	int		min_val;
	int		max_val;
	int		index;
	size_t	size;
} t_chunk;

typedef struct s_chunks {
	t_chunk	chunks[MAXCHUNK];
	int		count;
} t_chunks;

void	init_chunks(t_chunks *chunks, size_t n);
int		chunk_contains(const t_chunk *chunk, int val);

void	split_each_chunks(t_Stacks *s, t_op *ops, unsigned int *op_count, const t_chunks *chunks);
void	sort_all_chunks(t_Stacks *s, t_op *ops, unsigned int *op_count, const t_chunks *chunks);

#endif

