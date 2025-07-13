/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_1_Quick_sort.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kei2003730 <kei2003730@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 19:14:34 by kei2003730        #+#    #+#             */
/*   Updated: 2025/07/14 08:25:48 by kei2003730       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define BASE_CASE 3
#include "push_swap.h"

static void	quick_sort_recursive(t_Stacks *stacks, unsigned char *ops,
		t_op *op_count, int len);
static void	find_dual_pivots(t_Stacks *stacks, int len, int *pivot1,
		int *pivot2);
void	three_way_partition(t_Stacks *stacks, unsigned char *ops,
		t_op *op_count, int len, int pivot1, int pivot2,
		int *small_count, int *mid_count, int *large_count);

// void	sort_stacks(t_Stacks *stacks, unsigned char *ops)
// {
// 	unsigned int	op_count;

// 	op_count = 0;
// 	if (stacks->a_stack.size <= 1)
// 		return (ops[0] = LAST, (void)0);
// 	if (stacks->a_stack.size <= BASE_CASE)
// 		sort_small_stack_constrained(stacks, ops, &op_count,
			stacks->a_stack.size);
// 	else
// 		quick_sort_recursive(stacks, ops, &op_count, stacks->a_stack.size);
// 	ops[op_count] = LAST;
// }

// static void	quick_sort_recursive(t_Stacks *stacks, unsigned char *ops,
//		t_op *op_count, int len)
// {
//	int	pivot1, pivot2;
//	int	small_count, mid_count, large_count;
//
//	if (len <= BASE_CASE)
//	{
//		sort_small_stack_constrained(stacks, ops, op_count, len);
//		return ;
//	}
//	find_dual_pivots(stacks, len, &pivot1, &pivot2);
//	three_way_partition(stacks, ops, op_count, len, pivot1, pivot2,
//		&small_count, &mid_count, &large_count);
	if (large_count > 1)
		quick_sort_recursive(stacks, ops, op_count, large_count);

	// 2. 中間値グループ (B_TOPにある)
	// まずBからAに移動してソート
	int i = 0;
	while (i < mid_count)
	{
		do_op(stacks, PA, ops, op_count);
		i++;
	}
	if (mid_count > 1)
		quick_sort_recursive(stacks, ops, op_count, mid_count);

	// 3. 小さい値グループ (B_TOPにある)
	// BからAに移動してソート
	i = 0;
	while (i < small_count)
	{
		do_op(stacks, PA, ops, op_count);
		i++;
	}
	if (small_count > 1)
		quick_sort_recursive(stacks, ops, op_count, small_count);
}

// 3-Way QuickSort用の2つのピボットを選択（33%点と66%点）
static void	find_dual_pivots(t_Stacks *stacks, int len, int *pivot1,
		int *pivot2)
{
	int	*temp_array;
	int	i;
	int	pos1, pos2;

	temp_array = malloc(sizeof(int) * len);
	if (!temp_array)
		exit_with_error();
	// 配列にコピー
	i = 0;
	while (i < len)
	{
		temp_array[i] = deque_peek_at_Nth(&stacks->a_stack, i);
		i++;
	}
	// バブルソートでソート
	i = 0;
	while (i < len - 1)
	{
		int j = 0;
		while (j < len - i - 1)
		{
			if (temp_array[j] > temp_array[j + 1])
			{
				int temp = temp_array[j];
				temp_array[j] = temp_array[j + 1];
				temp_array[j + 1] = temp;
			}
			j++;
		}
		i++;
	}

	// 33%点と66%点を選択
	pos1 = len / 3;           // 33%点
	pos2 = (len * 2) / 3;     // 66%点

	// 境界チェック
	if (pos1 >= len) pos1 = len - 1;
	if (pos2 >= len) pos2 = len - 1;
	if (pos1 == pos2 && len > 1) pos2 = pos1 + 1;
	if (pos2 >= len) pos2 = len - 1;

	*pivot1 = temp_array[pos1];
	*pivot2 = temp_array[pos2];

	free(temp_array);
}

// 3-Way パーティション：2つのピボットで3分割
// 小さい値(< pivot1) → B_TOP, 中間値(pivot1 ≤ x < pivot2) → B_BOTTOM,
	大きい値(≥ pivot2) → A_BOTTOM
void	three_way_partition(t_Stacks *stacks, unsigned char *ops,
		t_op *op_count, int len, int pivot1, int pivot2,
		int *small_count, int *mid_count, int *large_count)
{
	int	processed;
	int	current;

	*small_count = 0;
	*mid_count = 0;
	*large_count = 0;
	processed = 0;

	// 全要素を処理
	while (processed < len)
	{
		current = deque_peek_at_Nth(&stacks->a_stack, 0);

		if (current < pivot1)
		{
			// 小さい値 → B_TOPに移動
			do_op(stacks, PB, ops, op_count);
			(*small_count)++;
		}
		else if (current < pivot2)
		{
			// 中間値 → B_BOTTOMに移動 (PB + RB で底に送る)
			do_op(stacks, PB, ops, op_count);
			do_op(stacks, RB, ops, op_count);  // Bスタックの底に回転
			(*mid_count)++;
		}
		else
		{
			// 大きい値 → A_BOTTOMに移動 (RA で底に送る)
			do_op(stacks, RA, ops, op_count);
			(*large_count)++;
		}
		processed++;
	}

	// A_BOTTOMにある大きい値を元の位置に戻す
	int i = 0;
	while (i < *large_count)
	{
		do_op(stacks, RRA, ops, op_count);
		i++;
	}

	// B_BOTTOMにある中間値をB_TOPに移動 (RRB操作)
	i = 0;
	while (i < *mid_count)
	{
		do_op(stacks, RRB, ops, op_count);
		i++;
	}
}
