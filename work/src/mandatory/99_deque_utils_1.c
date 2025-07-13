/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   99.0_deque_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjikuhar <kjikuhar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 20:19:02 by kjikuhar          #+#    #+#             */
/*   Updated: 2025/05/26 21:12:26 by kjikuhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "deque.h"
#include "libft.h"

void	deque_init(t_Deque *deque)
{
	deque->top = 0;
	deque->bottom = 0;
	deque->size = 0;
	ft_bzero(deque->array, sizeof(int) * DEQUE_CAPACITY);
}

void	deque_clear(t_Deque *deque)
{
	deque_init(deque);
}

bool	deque_is_empty(const t_Deque *deque)
{
	return (deque->size == 0);
}

bool	deque_is_full(const t_Deque *deque)
{
	return (deque->size == DEQUE_CAPACITY);
}

int	deque_peek_at_Nth(const t_Deque *deque, unsigned int index)
{
	size_t	position;

	if (index >= deque->size)
		return (0);
	position = (deque->top + index) % DEQUE_CAPACITY;
	return (deque->array[position]);
}
