/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_6_chunk_sort.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codex <codex@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 00:00:00 by codex             #+#    #+#             */
/*   Updated: 2025/07/22 00:00:00 by codex            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "chunk_sort.h"

void		sort_stacks(t_Stacks *s, t_op *ops)
{
	const size_t	n = s->a_stack.size;
	t_chunks		chunks;
	unsigned int	op_count = 0;

	if ((int)n <= 1)
		return (ops[0] = LAST, (void)0);
	init_chunks(&chunks, n);
	split_each_chunks(s, ops, &op_count, &chunks);
	sort_all_chunks(s, ops, &op_count, &chunks);
	ops[op_count] = LAST;
}
