/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deque.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjikuhar <kjikuhar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 20:20:37 by kjikuhar          #+#    #+#             */
/*   Updated: 2025/05/26 21:04:38 by kjikuhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEQUE_H
# define DEQUE_H

# include "libft.h"

# define DEQUE_CAPACITY 1001
typedef struct s_Deque
{
	int				top;
	int				bottom;
	unsigned int	size;
	int				array[DEQUE_CAPACITY];
}					t_Deque;

void	deque_init(t_Deque *deque);
void	deque_clear(t_Deque *deque);
bool	deque_is_empty(const t_Deque *deque);
bool	deque_is_full(const t_Deque *deque);
int		deque_peek_at_Nth(const t_Deque *deque, unsigned int index);

bool	deque_push_front(t_Deque *deque, int num);
bool	deque_push_back(t_Deque *deque, int num);
bool	deque_pop_front(t_Deque *deque, int *out);
bool	deque_pop_back(t_Deque *deque, int *out);

#endif
