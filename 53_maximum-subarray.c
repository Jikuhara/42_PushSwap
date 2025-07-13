/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   53_maximum-subarray.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kei2003730 <kei2003730@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 22:42:04 by kei2003730        #+#    #+#             */
/*   Updated: 2025/06/02 22:47:40 by kei2003730       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int	maxSubArray(int *nums, int numsSize)
{
	int	*dp;
	int	i;
	int	max_sum;

	dp = malloc(sizeof(int) * numsSize);
	if (!dp)
		return (0);
	memcpy(dp, nums, sizeof(int) * numsSize);
    max_sum = dp[0];
    i = 1;
	while (i < numsSize)
	{
		if (dp[i] < dp[i - 1] + nums[i])
			dp[i] = dp[i - 1] + nums[i];
        if (max_sum < dp[i])
			max_sum = dp[i];
		i++;
	}
    free(dp);
	return (max_sum);
}

int	main(void)
{
	int nums[] = {1, 2, -3, 4};
	int numsSize = 4;

	printf("%i\n", maxSubArray(nums, numsSize));
	return (0);
}