/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   99.1_deque_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjikuhar <kjikuhar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 19:37:41 by kjikuhar          #+#    #+#             */
/*   Updated: 2025/05/26 19:38:01 by kjikuhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "deque.h"

bool	deque_push_front(t_Deque *deque, int num)
{
	if (deque_is_full(deque))
		return (false);
	deque->top = (deque->top - 1 + DEQUE_CAPACITY) % DEQUE_CAPACITY;
	deque->array[deque->top] = num;
	deque->size += 1;
	return (true);
}

bool	deque_push_back(t_Deque *deque, int num)
{
	if (deque_is_full(deque))
		return (false);
	if (deque->size == 0)
	{
		deque->array[deque->top] = num;
		deque->bottom = (deque->top + 1) % DEQUE_CAPACITY;
	}
	else
	{
		deque->array[deque->bottom] = num;
		deque->bottom = (deque->bottom + 1) % DEQUE_CAPACITY;
	}
	deque->size += 1;
	return (true);
}

bool	deque_pop_front(t_Deque *deque, int *out)
{
	if (deque_is_empty(deque))
		return (false);
	*out = deque->array[deque->top];
	deque->top = (deque->top + 1) % DEQUE_CAPACITY;
	deque->size -= 1;
	return (true);
}

bool	deque_pop_back(t_Deque *deque, int *out)
{
	if (deque_is_empty(deque))
		return (false);
	deque->bottom = (deque->bottom - 1 + DEQUE_CAPACITY) % DEQUE_CAPACITY;
	*out = deque->array[deque->bottom];
	deque->size -= 1;
	return (true);
}
