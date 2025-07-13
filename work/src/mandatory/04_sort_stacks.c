/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_sort_stacks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kei2003730 <kei2003730@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 18:24:20 by kjikuhar          #+#    #+#             */
/*   Updated: 2025/07/14 08:35:00 by kei2003730       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	do_op(t_Stacks *stacks, t_op op, t_op *ops, unsigned int *op_count)
{
	if (*op_count >= OPS_MAX)
		exit_with_error();
	ops[(*op_count)++] = op;
	operation(&stacks->a_stack, &stacks->b_stack, op);
}

/* quick_sort_index.c – 値範囲で分割する push_swap QuickSort */

//
	/*---------------------------------- util ----------------------------------*/
// static void	sort_small(t_Stacks *s, t_op *ops, unsigned int *c,
// 		size_t n)
// {
// 	int	a;
// 	int	b;
// 	int	d;

// 	// 	/* DEQUE_CAPACITY で wrap させる -------------------------------*/
// 	a = s->a_stack.array[s->a_stack.top];
// 	b = s->a_stack.array[(s->a_stack.top + 1) % DEQUE_CAPACITY];
// 	d = (n == 3) ? s->a_stack.array[(s->a_stack.top + 2) % DEQUE_CAPACITY] : 0;
// 	if (n == 2 && a > b)
// 		do_op(s, SA, ops, c);
// 	else if (n == 3)
// 	{
// 		if (a > b && b < d && a < d)
// 			do_op(s, SA, ops, c);
// 		else if (a > b && b > d)
// 		{
// 			do_op(s, SA, ops, c);
// 			do_op(s, RRA, ops, c);
// 		}
// 		else if (a > b && b < d && a > d)
// 			do_op(s, RA, ops, c);
// 		else if (a < b && b > d && a < d)
// 		{
// 			do_op(s, SA, ops, c);
// 			do_op(s, RA, ops, c);
// 		}
// 		else if (a < b && b > d && a > d)
// 			do_op(s, RRA, ops, c);
// 	}
// }

// /* forward decl */
// static void		qs_A(t_Stacks *, t_op *, unsigned int *, int, int);
// static void		qs_B(t_Stacks *, t_op *, unsigned int *, int, int);

// /*---------------------------------- A→B ----------------------------------*/
// static void	qs_A(t_Stacks *s, t_op *ops, unsigned int *cnt,
		// int low,
// 		int high)
// {
// 	size_t	n;
// 	int		pivot;
// 	size_t	pb_cnt;
// 	int		val;

// 	pb_cnt = 0, ra_cnt;
// 	pb_cnt = 0, ra_cnt = 0, processed;
// 	n = high - low + 1;
// 	if (n <= 3)
// 		return (sort_small(s, ops, cnt, n));
// 	pivot = (low + high) / 2;
// 	pb_cnt = 0, ra_cnt = 0, processed = 0;
// 	while (processed++ < n)
// 	{
// 		val = s->a_stack.array[s->a_stack.top];
// 		if (val < pivot)
// 		{
// 			do_op(s, PB, ops, cnt);
// 			++pb_cnt;
// 		}
// 		else
// 		{
// 			do_op(s, RA, ops, cnt);
// 			++ra_cnt;
// 		}
// 	}
// 	while (ra_cnt--)
// 		do_op(s, RRA, ops, cnt);
// 	/* 右 (A) → 再帰, 左 (B) → 戻して再帰 */
// 	qs_A(s, ops, cnt, pivot, high);
// 	qs_B(s, ops, cnt, low, pivot - 1);
// }

// /*---------------------------------- B→A ----------------------------------*/
// static void	qs_B(t_Stacks *s, t_op *ops, unsigned int *cnt,
		// int low,
// 		int high)
// {
// 	size_t	n;
// 	int		pivot;
// 	size_t	pa_cnt;
// 	int		val;

// 	pa_cnt = 0, rb_cnt;
// 	pa_cnt = 0, rb_cnt = 0, processed;
// 	n = high - low + 1;
// 	if (!n)
// 		return ;
// 	if (n <= 3)
// 	{
// 		for (size_t i = 0; i < n; ++i)
// 			do_op(s, PA, ops, cnt);
// 		sort_small(s, ops, cnt, n);
// 		return ;
// 	}
// 	pivot = (low + high) / 2;
// 	pa_cnt = 0, rb_cnt = 0, processed = 0;
// 	while (processed++ < n)
// 	{
// 		val = s->b_stack.array[s->b_stack.top];
// 		if (val >= pivot)
// 		{
// 			do_op(s, PA, ops, cnt);
// 			++pa_cnt;
// 		}
// 		else
// 		{
// 			do_op(s, RB, ops, cnt);
// 			++rb_cnt;
// 		}
// 	}
// 	while (rb_cnt--)
// 		do_op(s, RRB, ops, cnt);
// 	/* 先に大きい側 (A) -> 再帰，あとで小さい側 (B) */
// 	qs_A(s, ops, cnt, pivot, high);
// 	qs_B(s, ops, cnt, low, pivot - 1);
// }

//
	/*-------------------------------- public ----------------------------------*/
// void	sort_stacks(t_Stacks *s, t_op *ops)
// {
// 	unsigned int	op_cnt;

// 	op_cnt = 0;
// 	if (s->a_stack.size <= 1)
// 		return (void)(ops[0] = LAST);
// 	qs_A(s, ops, &op_cnt, 0, (int)s->a_stack.size - 1);
// 	ops[op_cnt] = LAST;
// }

// /* -------------------------------- 小ツール -------------------------------- */

// static void	rotate_to_top(t_Stacks *s, size_t idx, t_op *ops,
// 		unsigned int *cnt)
// {
// 	size_t	reverse_moves;

// 	if (idx == 0)
// 		return ; // 既にtopにある場合は何もしない
// 	if (idx <= s->a_stack.size / 2)
// 		while (idx--)
// 			do_op(s, RA, ops, cnt);
// 	else
// 	{
// 		reverse_moves = s->a_stack.size - idx;
// 		while (reverse_moves--)
// 			do_op(s, RRA, ops, cnt);
// 	}
// }

// static size_t	find_in_range(t_Deque *a, int min_val, int max_val)
// {
// 	size_t	pos;
// 	int		val;

// 	pos = a->top;
// 	for (size_t i = 0; i < a->size; ++i)
// 	{
// 		val = a->array[pos];
// 		if (val >= min_val && val <= max_val)
// 			return (i);
// 		pos = (pos + 1) % DEQUE_CAPACITY;
// 	}
// 	return (a->size); // NOT FOUND
// }

// /* -------------------------------- メイン -------------------------------- */

// void	sort_stacks(t_Stacks *s, t_op *ops)
// {
// 	const size_t	n = s->a_stack.size;
// 	unsigned int	op_cnt;
// 	int				min_val;
// 	const size_t	chunk_size = (n <= 100) ? n / 5 : n / 8;
// 	size_t			chunks_processed;
// 	size_t			total_chunks;
// 	int				min_val;
// 	int				max_val;
// 	size_t			pushed_count;
// 	size_t			target_count;
// 	size_t			idx;
// 	int				val;
// 	int				mid_val;
// 	int				max_val;
// 	size_t			max_idx;
// 	size_t			pos;
// 	size_t			reverse_moves;

// 	op_cnt = 0;
// 	if (n <= 1)
// 		return (void)(ops[0] = LAST);
// 	// 小さい配列は専用処理
// 	if (n <= 5)
// 	{
// 		// 選択ソートベースの小規模ソート
// 		while (!deque_is_empty(&s->a_stack))
// 		{
// 			// 最小値をtopに持ってきてBに送る
// 			min_val = min(&s->a_stack);
// 			while (s->a_stack.array[s->a_stack.top] != min_val)
// 				do_op(s, RA, ops, &op_cnt);
// 			do_op(s, PB, ops, &op_cnt);
// 		}
// 		// Bから戻す
// 		while (!deque_is_empty(&s->b_stack))
// 			do_op(s, PA, ops, &op_cnt);
// 		ops[op_cnt] = LAST;
// 		return ;
// 	}
// 	// チャンクソート
// 	chunks_processed = 0;
// 	total_chunks = (n + chunk_size - 1) / chunk_size;
// 	/* 1) チャンクごとに A→B へ搬送 */
// 	while (chunks_processed < total_chunks && !deque_is_empty(&s->a_stack))
// 	{
// 		min_val = chunks_processed * chunk_size;
// 		max_val = (chunks_processed + 1) * chunk_size - 1;
// 		if (max_val >= (int)n)
// 			max_val = n - 1;
// 		pushed_count = 0;
// 		target_count = chunk_size;
// 		if (chunks_processed == total_chunks - 1)
// 			target_count = n - chunks_processed * chunk_size;
// 		// 現在のチャンクをすべてBに移動
// 		while (pushed_count < target_count && !deque_is_empty(&s->a_stack))
// 		{
// 			idx = find_in_range(&s->a_stack, min_val, max_val);
// 			if (idx < s->a_stack.size)
// 			{
// 				rotate_to_top(s, idx, ops, &op_cnt);
// 				val = s->a_stack.array[s->a_stack.top];
// 				do_op(s, PB, ops, &op_cnt);
// 				// Bでの順序制御：大きい値ほど下に送る
// 				if (s->b_stack.size > 1)
// 				{
// 					mid_val = (min_val + max_val) / 2;
// 					if (val <= mid_val)
// 						do_op(s, RB, ops, &op_cnt);
// 				}
// 				pushed_count++;
// 			}
// 			else
// 			{
// 				// 範囲内の要素が見つからない場合はチャンク完了
// 				break ;
// 			}
// 		}
// 		chunks_processed++;
// 	}
// 	/* 2) B から A へ戻す（降順になるように） */
// 	while (!deque_is_empty(&s->b_stack))
// 	{
// 		// Bの最大値を見つけてAに戻す
// 		max_val = INT_MIN;
// 		max_idx = 0;
// 		pos = s->b_stack.top;
// 		for (size_t i = 0; i < s->b_stack.size; ++i)
// 		{
// 			if (s->b_stack.array[pos] > max_val)
// 			{
// 				max_val = s->b_stack.array[pos];
// 				max_idx = i;
// 			}
// 			pos = (pos + 1) % DEQUE_CAPACITY;
// 		}
// 		// 最大値をBのtopに移動
// 		if (max_idx <= s->b_stack.size / 2)
// 		{
// 			while (max_idx--)
// 				do_op(s, RB, ops, &op_cnt);
// 		}
// 		else
// 		{
// 			reverse_moves = s->b_stack.size - max_idx;
// 			while (reverse_moves--)
// 				do_op(s, RRB, ops, &op_cnt);
// 		}
// 		do_op(s, PA, ops, &op_cnt);
// 	}
// 	ops[op_cnt] = LAST;
// }
