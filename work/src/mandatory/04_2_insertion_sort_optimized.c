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

/* --- ヘルパ: A の値を配列にコピー --- */
static void copy_a_to_arr(const t_Deque *a, int *arr)
{
    for (size_t i = 0; i < a->size; ++i)
        arr[i] = deque_peek_at_Nth(a, i);
}

/* --- LIS を bool 配列にマーキング (true=LIS) --- */
static void mark_lis(const int *v, size_t n, bool *is_lis)
{
    /* patience sorting: tails[k] = LIS 長さ k+1 の末尾値の index */
    size_t tails[n];
    size_t prev [n];

    size_t len = 0;
    for (size_t i = 0; i < n; ++i) {
        /* lower_bound on tails */
        size_t l = 0, r = len;
        while (l < r) {
            size_t mid = (l + r) / 2;
            if (v[tails[mid]] < v[i]) l = mid + 1;
            else                     r = mid;
        }
        if (l == len) ++len;
        tails[l] = i;
        prev[i]  = (l ? tails[l-1] : SIZE_MAX);
    }
    /* 復元して is_lis[] にフラグ立て */
    for (size_t i = 0; i < n; ++i) is_lis[i] = false;
    for (size_t idx = tails[len-1]; idx != SIZE_MAX; idx = prev[idx])
        is_lis[idx] = true;
}

void move_lis_to_stack_b(t_Stacks *stacks, t_op *ops, t_op *op_cnt)
{
    const size_t n = stacks->a_stack.size;
    int  values[n];
    bool is_lis[n];

    copy_a_to_arr(&stacks->a_stack, values);
    mark_lis(values, n, is_lis);

    /* 1 周だけ走査: 先頭を見て LIS なら PB, そうでなければ RA */
    size_t processed = 0;
    while (processed < n) {
        if (is_lis[0]) {             /* いま先頭にある要素が LIS なら */
            do_op(stacks, PB, ops, op_cnt);
        } else {
            do_op(stacks, RA, ops, op_cnt);
        }
        /* is_lis[] を 1 つ左へローテート（RA/PB と同じ見かけ順に合わせる） */
        bool first = is_lis[0];
        for (size_t i = 0; i + 1 < n; ++i)
            is_lis[i] = is_lis[i+1];
        is_lis[n-1] = first;
        ++processed;
    }
}

static unsigned int find_insert_pos(const t_Deque *b, int a_val)
{
	unsigned int	j;
	int				b_val;

	j = 0;
	while (j < b->size)
	{
		b_val = deque_peek_at_Nth(b, j);
		if (b_val < a_val)
			break;
		j++;
	}
	return (j);
}

static int find_min_index(const unsigned int nums[], size_t n)
{
	size_t			i;
	int				min_idx;
	unsigned int	min_val;

	if (!nums || n == 0)
		return -1;
	min_val = UINT_MAX;
	min_idx = -1;
	i = 0;
	while (i < n)
	{
		if (nums[i] < min_val)
		{
			min_val = nums[i];
			min_idx = (int)i;
		}
		i++;
	}
	return min_idx;
}

/* insertion_sort */
static void	insert_element_to_stack_b(t_Stacks *stacks, t_op *ops,
	t_op *op_count, unsigned int size)
{
	unsigned int	rb_count;
	unsigned int	insert_pos[size];
	unsigned int	top_total_op[size];
	unsigned int	bottom_total_op[size];
	unsigned int	a_value;
	unsigned int	j;
	unsigned int	top_index;
	unsigned int	bottom_index;

	j = 0;
	while (j < size)
	{
		a_value = deque_peek_at_Nth(&stacks->a_stack, j);
		insert_pos[j] = find_insert_pos(&stacks->b_stack, a_value);
		top_total_op[j] = insert_pos[j] * 2 + j + 1;
		bottom_total_op[j] = (stacks->b_stack.size - insert_pos[j]) * 2 + j + 1 + 1;
		j++;
	}
	top_index = find_min_index(top_total_op, size);
	bottom_index = find_min_index(bottom_total_op, size);
	if (top_total_op[top_index] < bottom_total_op[bottom_index])
	{
		for (unsigned k = 0; k < top_index; k++)
		{
			do_op(stacks, RA, ops, op_count);
		}
		rb_count = 0;
		while (rb_count < insert_pos[top_index])
		{
			do_op(stacks, RB, ops, op_count);
			rb_count++;
		}
		do_op(stacks, PB, ops, op_count);
		while (rb_count-- > 0)
			do_op(stacks, RRB, ops, op_count);
	}
	else
	{
		for (unsigned k = 0; k < bottom_index; k++)
		{
			do_op(stacks, RA, ops, op_count);
		}
		if (insert_pos[bottom_index] == stacks->b_stack.size)
			{
				/* “最小値を底に入れる” 特例 */
				do_op(stacks, PB, ops, op_count);
				do_op(stacks, RB, ops, op_count);   /* 1 回回して底に送る */
				return;
			}
		rb_count = 0;
		while (rb_count < stacks->b_stack.size - insert_pos[bottom_index])
		{
			do_op(stacks, RRB, ops, op_count);
			rb_count++;
		}
		do_op(stacks, PB, ops, op_count);
		while (rb_count-- + 1> 0)
			do_op(stacks, RB, ops, op_count);
	}
}

static void	return_all_to_stack_a(t_Stacks *stacks, t_op *ops,
	t_op *op_count)
{
	while (!deque_is_empty(&stacks->b_stack))
		do_op(stacks, PA, ops, op_count);
}

void	sort_stacks(t_Stacks *stacks, t_op *ops)
{
	unsigned int	op_count;

	op_count = 0;
	if (stacks->a_stack.size <= 1)
		return (ops[0] = LAST, (void)0);
	else if (stacks->a_stack.size <= BASE_CASE)
	{
		sort_small_stack_constrained(stacks, ops, &op_count,
			stacks->a_stack.size);
	}
	else
	{
		move_lis_to_stack_b(stacks, ops, &op_count);
		while (!deque_is_empty(&stacks->a_stack))
			insert_element_to_stack_b(stacks, ops, &op_count, stacks->a_stack.size);
		return_all_to_stack_a(stacks, ops, &op_count);
	}
	ops[op_count] = LAST;
}
