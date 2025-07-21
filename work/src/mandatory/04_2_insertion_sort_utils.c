/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_1_insertion_sort.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kei2003730 <kei2003730@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 15:38:38 by kjikuhar          #+#    #+#             */
/*   Updated: 2025/07/14 08:25:26 by kei2003730       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* ---------- ヘルパ ---------- */
static void	swap(int *a, int *b)
{
	int	tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

/* Hoare 版パーティション
   戻り値 j は「左側サブ配列の最終インデックス」*/
static int partition(int nums[], int left, int right)
{
	int pivot;
	int i;
	int j;

	pivot = nums[(left + right) / 2];  /* 中央値をピボットに */
	i = left - 1;
	j = right + 1;
	while (1)
	{
		do { ++i; } while (nums[i] < pivot);
		do { --j; } while (nums[j] > pivot);
		if (i >= j)
			return j;
		swap(&nums[i], &nums[j]);
	}
}

/* 再帰版クイックソート本体 */
static void quicksort(int nums[], int left, int right)
{
	if (left < right) {
		int mid = partition(nums, left, right);
		quicksort(nums, left,  mid);	 /* pivot 未満 */
		quicksort(nums, mid + 1, right); /* pivot 以上 */
	}
}

/* 使いやすいラッパ ― 配列と要素数だけ渡す */
void quicksort_array(int nums[], size_t n)
{
	if (n > 0)
		quicksort(nums, 0, (int)n - 1);
}

// int main(void)
// {
// 	int nums[] = {1, 2, 3, 5, 4};
// 	size_t size = sizeof(nums) / sizeof(nums[0]);

// 	quicksort_array(nums, size);
// 	for (size_t i = 0; i < size; i++)
// 	{
// 		printf("%d ", nums[i]);
// 	}
// 	return (0);
// }
