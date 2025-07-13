/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_is_valid_int.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjikuhar <kjikuhar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 17:39:32 by kjikuhar          #+#    #+#             */
/*   Updated: 2025/05/23 21:51:41 by kjikuhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static bool	will_overflow(unsigned int acc, unsigned int digit, bool negative)
{
	if (negative == false)
	{
		if (acc > (INT_MAX - digit) / 10)
			return (true);
	}
	else if (negative == true)
	{
		if (acc > -(INT_MIN - digit) / 10)
			return (true);
	}
	return (false);
}

static bool	ft_safe_atoi(const char *str)
{
	int				negative;
	unsigned int	acc;
	unsigned int	digit;

	if (!str || !*str)
		return (false);
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			negative = 1;
		str++;
	}
	acc = 0;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (false);
		digit = *str - '0';
		if (will_overflow(acc, digit, negative))
			return (false);
		acc = acc * 10 + digit;
		str++;
	}
	return (true);
}

void	is_valid_int(int argc, char const *argv[])
{
	int	i;

	if (argc < 2 || argc > INPUT_MAX_LIMIT)
		return (exit_with_error());
	i = 1;
	while (i < argc)
	{
		if (!ft_safe_atoi(argv[i]))
			return (exit_with_error());
		i++;
	}
}
