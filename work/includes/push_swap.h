/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kei2003730 <kei2003730@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 15:24:13 by kjikuhar          #+#    #+#             */
/*   Updated: 2025/07/14 08:24:54 by kei2003730       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "deque.h"
# include "libft.h"
# define INPUT_MAX_LIMIT 1001
# define OPS_MAX 1000000
# define ERR_MSG "Error"

typedef struct s_Stacks
{
	t_Deque	a_stack;
	t_Deque	b_stack;
}			t_Stacks;

typedef enum e_op
{
			LAST = 0,
			SA,
			SB,
			SS,
			PA,
			PB,
			RA,
			RB,
			RR,
			RRA,
			RRB,
			RRR
}			t_op;

// 00_main.c
void		exit_with_error(void);

// 01_is_valid_int.c
void		is_valid_int(int argc, char const *argv[]);

// 02_init_info.c
void		init_info(t_Stacks *stacks);

// 03_parse_num.c
void		parse_num(int argc, char const *argv[], int *tab);

// 04_sort_Stacks.c
void		operation(t_Deque *A, t_Deque *B, t_op op);
void		do_op(t_Stacks *stacks, t_op op, t_op *ops, unsigned int *op_count);
void		sort_stacks(t_Stacks *Stacks, t_op *ops);
void		sort_small_stack_constrained(t_Stacks *stacks, t_op *ops,
				unsigned int *op_count, int len);

// Test functions (temporary)
void		three_way_partition(t_Stacks *stacks, t_op *ops,
				unsigned int *op_count, int len, int pivot1, int pivot2,
				int *small_count, int *mid_count, int *large_count);

void		print_operation(t_op *ops);

#endif
