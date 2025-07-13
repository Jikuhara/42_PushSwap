/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_0_operation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjikuhar <kjikuhar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 19:36:08 by kjikuhar          #+#    #+#             */
/*   Updated: 2025/06/02 21:16:35 by kjikuhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"


static void	swap(t_Deque *deque)
{
	int	a;
	int	b;

	if (deque->size < 2)
		return ;
	deque_pop_front(deque, &a);
	deque_pop_front(deque, &b);
	deque_push_front(deque, a);
	deque_push_front(deque, b);
}

static void	push(t_Deque *src, t_Deque *dst)
{
	int	tmp;

	if (deque_pop_front(src, &tmp))
		deque_push_front(dst, tmp);
}

static void	rotate(t_Deque *deque)
{
	int	tmp;

	if (deque_pop_front(deque, &tmp))
		deque_push_back(deque, tmp);
}

static void	reverse_rotate(t_Deque *deque)
{
	int	tmp;

	if (deque_pop_back(deque, &tmp))
		deque_push_front(deque, tmp);
}

void	operation(t_Deque *A, t_Deque *B, t_op op)
{
	if (op == SA)
		swap(A);
	else if (op == SB)
		swap(B);
	else if (op == SS)
		return (swap(A), swap(B), (void)0);
	else if (op == PA)
		push(B, A);
	else if (op == PB)
		push(A, B);
	else if (op == RA)
		rotate(A);
	else if (op == RB)
		rotate(B);
	else if (op == RR)
		return (rotate(A), rotate(B), (void)0);
	else if (op == RRA)
		reverse_rotate(A);
	else if (op == RRB)
		reverse_rotate(B);
	else if (op == RRR)
		return (reverse_rotate(A), reverse_rotate(B), (void)0);
	else
		exit_with_error();
}
