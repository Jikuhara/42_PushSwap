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

typedef enum e_position
{
	TOP_A,
	BOTTOM_A,
	TOP_B,
	BOTTOM_B
}				t_position;

typedef struct s_chunk
{
	t_position	position;
	int			size;
	int			min_val;
	int			max_val;
}				t_chunk;

typedef struct s_chunk_set
{
	t_chunk		min;
	t_chunk		mid;
	t_chunk		max;
}				t_chunk_set;

// Function declarations
// static int	is_chunk_sorted(t_Stacks *stacks, t_chunk chunk);
void			calculate_pivots(t_Stacks *stacks, t_chunk chunk, int *pivot1,
					int *pivot2);
void			move_chunk_to_position(t_Stacks *stacks, t_op *ops,
					unsigned int *op_count, t_chunk *chunk, t_position target);
void			split_chunk(t_Stacks *stacks, t_op *ops,
					unsigned int *op_count, t_chunk *chunk, t_chunk_set *dest);
void			chunk_sort_recursive(t_Stacks *stacks, t_op *ops,
					unsigned int *op_count, t_chunk input_chunk);
bool			is_chunk_sorted(t_Stacks *stacks, t_chunk chunk);
void			init_size(t_chunk *min, t_chunk *mid, t_chunk *max);

#endif
