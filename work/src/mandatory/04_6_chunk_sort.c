/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_1_chunk_sort.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjikuhar <kjikuhar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 19:14:34 by kei2003730        #+#    #+#             */
/*   Updated: 2025/06/02 21:25:55 by kjikuhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define BASE_CASE 3
#include "chunk_sort.h"
#include "push_swap.h"

void	sort_stacks(t_Stacks *stacks, t_op *ops)
{
	unsigned int	op_count;
	t_chunk			initial_chunk;

	op_count = 0;
	if (stacks->a_stack.size <= 1)
		return (ops[0] = LAST, (void)0);
	if (stacks->a_stack.size <= BASE_CASE)
	{
		sort_small_stack_constrained(stacks, ops, &op_count,
			stacks->a_stack.size);
		ops[op_count] = LAST;
		return ;
	}
	initial_chunk.position = TOP_A;
	initial_chunk.size = stacks->a_stack.size;
	initial_chunk.min_val = 0;
	initial_chunk.max_val = stacks->a_stack.size - 1;
	chunk_sort_recursive(stacks, ops, &op_count, initial_chunk);
	ops[op_count] = LAST;
}

// メイン再帰関数：チャンクソートのコア
void	chunk_sort_recursive(t_Stacks *stacks, t_op *ops, t_op *op_count,
		t_chunk input_chunk)
{
	t_chunk_set	output_chunks;

	if (input_chunk.size <= BASE_CASE)
	{
		move_chunk_to_position(stacks, ops, op_count, &input_chunk, TOP_A);
		sort_small_stack_constrained(stacks, ops, op_count, input_chunk.size);
		return ;
	}
	split_chunk(stacks, ops, op_count, &input_chunk, &output_chunks);
	if (output_chunks.max.size > 0)
		chunk_sort_recursive(stacks, ops, op_count, output_chunks.max);
	if (output_chunks.mid.size > 0)
		chunk_sort_recursive(stacks, ops, op_count, output_chunks.mid);
	if (output_chunks.min.size > 0)
		chunk_sort_recursive(stacks, ops, op_count, output_chunks.min);
}

// Better Pivots最適化：動的ピボット計算
void	calculate_pivots(t_Stacks *stacks, t_chunk chunk, int *pivot_small,
		int *pivot_big)
{
	int	range;

	(void)stacks;
	range = chunk.max_val - chunk.min_val + 1;
	printf("%i\n", range);
	if (range <= 2)
	{
		*pivot_small = chunk.min_val;
		*pivot_big = chunk.max_val;
	}
	else if (range <= 3)
	{
		*pivot_small = chunk.min_val;
		*pivot_big = chunk.min_val + 1;
	}
	else
	{
		*pivot_small = chunk.min_val + range / 3;
		*pivot_big = chunk.min_val + (range * 2) / 3;
	}
}

/* チャンクの分割先位置を設定 */
void	set_split_locations(t_position source, t_position *min_pos,
		t_position *mid_pos, t_position *max_pos)
{
	if (source == TOP_A)
	{
		*min_pos = TOP_B;
		*mid_pos = BOTTOM_B;
		*max_pos = BOTTOM_A;
	}
	else if (source == BOTTOM_A)
	{
		*min_pos = TOP_B;
		*mid_pos = BOTTOM_B;
		*max_pos = TOP_A;
	}
	else if (source == TOP_B)
	{
		*min_pos = BOTTOM_A;
		*mid_pos = TOP_A;
		*max_pos = BOTTOM_B;
	}
	else if (source == BOTTOM_B)
	{
		*min_pos = BOTTOM_A;
		*mid_pos = TOP_A;
		*max_pos = TOP_B;
	}
}

/* チャンクが部分的にソート済みかチェック */
int	detect_sorted_portion(t_Stacks *stacks, t_chunk chunk)
{
	int	sorted_count;
	int	current_val;
	int	next_val;

	sorted_count = 0;
	if (chunk.position != TOP_A)
		return (0);
	while (sorted_count < chunk.size - 1)
	{
		current_val = deque_peek_at_Nth(&stacks->a_stack, sorted_count);
		next_val = deque_peek_at_Nth(&stacks->a_stack, sorted_count + 1);
		if (current_val > next_val)
			break ;
		sorted_count++;
	}
	return (sorted_count);
}

/* チャンクを分割して3つのサブチャンクに振り分ける */
void	split_chunk(t_Stacks *stacks, t_op *ops, t_op *op_count,
		t_chunk *to_split, t_chunk_set *dest)
{
	int	pivot_small;
	int	pivot_big;
	int	current;
	int	remaining;

	init_size(&dest->min, &dest->mid, &dest->max);
	set_split_locations(to_split->position, &dest->min.position,
		&dest->mid.position, &dest->max.position);
	calculate_pivots(stacks, *to_split, &pivot_small, &pivot_big);
	move_chunk_to_position(stacks, ops, op_count, to_split, TOP_A);
	remaining = to_split->size;
	while (remaining--)
	{
		current = deque_peek_at_Nth(&stacks->a_stack, 0);
		if (current >= pivot_big)
		{
			do_op(stacks, RA, ops, op_count);
			dest->max.size++;
		}
		else if (current >= pivot_small)
		{
			do_op(stacks, PB, ops, op_count);
			dest->mid.size++;
		}
		else
		{
			do_op(stacks, PB, ops, op_count);
			do_op(stacks, RB, ops, op_count);
			dest->min.size++;
		}
	}
	dest->max.max_val = to_split->max_val;
	dest->max.min_val = pivot_big;
	dest->mid.max_val = pivot_big - 1;
	dest->mid.min_val = pivot_small;
	dest->min.max_val = pivot_small - 1;
	dest->min.min_val = to_split->min_val;
}

// void	split_chunk(t_Stacks *stacks, t_op *ops,
// 		t_op *op_count, t_chunk chunk, t_chunk *chunk_set.max,
// 		t_chunk *chunk_set.mid, t_chunk *min_chunk)
// {
// 	int	processed;
// 	int	current;
// 	int	max_count;
// 	int	mid_count;
// 	int	min_count;
// 	int	moves_for_sorted;
// 	int	i;
// 	int	sorted_from_top;
// 	int	pivot_small;
// 	int	pivot_big;
// 	int	current_val;
// 	int	next_val;

// 	max_count = 0;
// 	mid_count = 0;
// 	min_count = 0;
// 	processed = 0;
// 	sorted_from_top = 0;
// 	calculate_pivots(stacks, chunk, &pivot_small, &pivot_big);
// 	move_chunk_to_position(stacks, ops, op_count, &chunk, TOP_A);
// 	// // Sort ASAP最適化：上から既にソートされている部分をチェック
// 	while (sorted_from_top < chunk.size - 1)
// 	{
// 		current_val = deque_peek_at_Nth(&stacks->a_stack, sorted_from_top);
// 		next_val = deque_peek_at_Nth(&stacks->a_stack, sorted_from_top + 1);
// 		if (current_val > next_val) // 順序が乱れている場合は停止
// 			break ;
// 		sorted_from_top++;
// 	}
// 	// ソート済み部分をTOP_Aの最上位に保持
// 	moves_for_sorted = 0;
// 	while (moves_for_sorted < sorted_from_top)
// 	{
// 		do_op(stacks, RA, ops, op_count);
// 		moves_for_sorted++;
// 	}
// 	// 残りの未ソート部分のみ処理
// 	processed = 0;
// 	// 分割処理
// 	while (processed < chunk.size - sorted_from_top)
// 	{
// 		current = deque_peek_at_Nth(&stacks->a_stack, 0);
// 		if (current >= pivot_big)
// 		{
// 			// 大きい値 → BOTTOM_Aに移動
// 			do_op(stacks, RA, ops, op_count);
// 			max_count++;
// 		}
// 		else if (current >= pivot_small)
// 		{
// 			// 中間値 → TOP_Bに移動
// 			do_op(stacks, PB, ops, op_count);
// 			mid_count++;
// 		}
// 		else
// 		{
// 			// 小さい値 → BOTTOM_Bに移動
// 			do_op(stacks, PB, ops, op_count);
// 			do_op(stacks, RB, ops, op_count);
// 			min_count++;
// 		}
// 		processed++;
// 	}
// 	// BOTTOM_Aの大きい値をTOP_Aに移動（ソート済み部分の下に配置）
// 	i = 0;
// 	while (i < max_count)
// 	{
// 		do_op(stacks, RRA, ops, op_count);
// 		i++;
// 	}
// 	// ソート済み部分を元の位置に戻す
// 	i = 0;
// 	while (i < sorted_from_top)
// 	{
// 		do_op(stacks, RRA, ops, op_count);
// 		i++;
// 	}
// 	// BOTTOM_Bの小さい値をTOP_Bに移動
// 	i = 0;
// 	while (i < min_count)
// 	{
// 		do_op(stacks, RRB, ops, op_count);
// 		i++;
// 	}
// 	// チャンク情報を設定
// 	chunk_set.max->position = TOP_A;
// 	chunk_set.max->size = max_count + sorted_from_top; // ソート済み部分を含む
// 	chunk_set.max->min_val = (sorted_from_top > 0) ? chunk.min_val : pivot_big;
// 	chunk_set.max->max_val = chunk.max_val;
// 	chunk_set.mid->position = BOTTOM_B;
// 	chunk_set.mid->size = mid_count;
// 	chunk_set.mid->min_val = pivot_small;
// 	chunk_set.mid->max_val = pivot_big - 1;
// 	min_chunk->position = TOP_B;
// 	min_chunk->size = min_count;
// 	min_chunk->min_val = chunk.min_val;
// 	min_chunk->max_val = pivot_small - 1;
// }
