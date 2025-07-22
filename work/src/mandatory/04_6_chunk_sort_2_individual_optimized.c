/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_2_LISsort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kei2003730 <kei2003730@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 13:48:20 by kei2003730        #+#    #+#             */
/*   Updated: 2025/07/14 08:26:09 by kei2003730       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "chunk_sort.h"
#include <stdint.h>
#include <string.h>

#define N 9

typedef struct s_state {
	uint8_t	a[N];
	uint8_t	b[N];
	uint8_t	size_a;
	uint8_t	size_b;
	uint8_t	head_a;
	uint8_t	head_b;
} t_state;

static int	is_goal(const t_state *s) __attribute__((unused));
static int	is_goal(const t_state *s)
{
	int		i;

	if (s->size_b)
		return (0);
	i = 0;
	while (i < N - 1)
	{
		if (s->a[i] > s->a[i + 1])
			return (0);
		i++;
	}
	return (1);
}

static uint32_t	factorial[10] = {
	1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880
};

static uint32_t	lehmer_code(const uint8_t *perm, int n)
{
	uint32_t	code;
	uint8_t	tmp[N];
	int		i;
	int		j;
	int		smaller;

	code = 0;
	memcpy(tmp, perm, n);
	i = 0;
	while (i < n)
	{
		smaller = 0;
		j = i + 1;
		while (j < n)
		{
			if (tmp[j] < tmp[i])
				smaller++;
			j++;
		}
		code += smaller * factorial[n - 1 - i];
		i++;
	}
	return (code);
}

static uint32_t	state_hash(const t_state *s)
{
	uint8_t		perm[N];
	uint16_t	abmask;
	int			k;
	int			i;
	uint32_t	code;

	abmask = 0;
	k = 0;
	i = 0;
	while (i < s->size_a)
	{
		perm[k] = s->a[i];
		abmask |= (1 << k);
		k++;
		i++;
	}
	i = 0;
	while (i < s->size_b)
	{
		perm[k] = s->b[i];
		k++;
		i++;
	}
	code = lehmer_code(perm, N);
	return (code | ((uint32_t)abmask << 19) | ((uint32_t)s->size_b << 28));
}

static void	swap(uint8_t *x, uint8_t *y)
{
	uint8_t	t;
	t = *x;
	*x = *y;
	*y = t;
}

static int	apply_op(const t_state *in, t_state *out, t_op op)
{
	*out = *in;
	if (op == SA)
	{
		if (out->size_a >= 2)
			swap(&out->a[0], &out->a[1]);
		else
			return (0);
	}
	else if (op == SB)
	{
		if (out->size_b >= 2)
			swap(&out->b[0], &out->b[1]);
		else
			return (0);
	}
	else if (op == SS)
	{
		if (out->size_a >= 2)
			swap(&out->a[0], &out->a[1]);
		if (out->size_b >= 2)
			swap(&out->b[0], &out->b[1]);
	}
	else if (op == PA)
	{
		if (!out->size_b)
			return (0);
		memmove(out->a + 1, out->a, out->size_a);
		out->a[0] = out->b[0];
		memmove(out->b, out->b + 1, --out->size_b);
		out->size_a++;
	}
	else if (op == PB)
	{
		if (!out->size_a)
			return (0);
		memmove(out->b + 1, out->b, out->size_b);
		out->b[0] = out->a[0];
		memmove(out->a, out->a + 1, --out->size_a);
		out->size_b++;
	}
	else if (op == RA)
	{
		if (out->size_a >= 2)
		{
			uint8_t t = out->a[0];
			memmove(out->a, out->a + 1, out->size_a - 1);
			out->a[out->size_a - 1] = t;
		}
		else
			return (0);
	}
	else if (op == RB)
	{
		if (out->size_b >= 2)
		{
			uint8_t t = out->b[0];
			memmove(out->b, out->b + 1, out->size_b - 1);
			out->b[out->size_b - 1] = t;
		}
		else
			return (0);
	}
	else if (op == RRA)
	{
		if (out->size_a >= 2)
		{
			uint8_t t = out->a[out->size_a - 1];
			memmove(out->a + 1, out->a, out->size_a - 1);
			out->a[0] = t;
		}
		else
			return (0);
	}
	else if (op == RRB)
	{
		if (out->size_b >= 2)
		{
			uint8_t t = out->b[out->size_b - 1];
			memmove(out->b + 1, out->b, out->size_b - 1);
			out->b[0] = t;
		}
		else
			return (0);
	}
	else if (op == RR)
	{
		apply_op(out, out, RA);
		apply_op(out, out, RB);
	}
	else if (op == RRR)
	{
		apply_op(out, out, RRA);
		apply_op(out, out, RRB);
	}
	else
		return (0);
	return (1);
}

static t_op	inverse_op(t_op op)
{
	if (op == SA)
		return (SA);
	else if (op == SB)
		return (SB);
	else if (op == SS)
		return (SS);
	else if (op == PA)
		return (PB);
	else if (op == PB)
		return (PA);
	else if (op == RA)
		return (RRA);
	else if (op == RB)
		return (RRB);
	else if (op == RRA)
		return (RA);
	else if (op == RRB)
		return (RB);
	else if (op == RR)
		return (RRR);
	else if (op == RRR)
		return (RR);
	return (LAST);
}

#define MAX_NODE 6000000

typedef struct s_node {
	t_state	st;
	int		parent;
	uint8_t	op;
} t_node;

static const t_op g_ops[] = {SA, SB, SS, PA, PB, RA, RB, RRA, RRB, RR, RRR};

int	bfs_solve9(const t_state *start, t_op *out_seq, int *out_len)
{
	static t_node	fwd[MAX_NODE];
	static t_node	rev[MAX_NODE];
	static uint32_t vis_fwd_hash[MAX_NODE / 2];
	static uint32_t vis_rev_hash[MAX_NODE / 2];
	int				head_f;
	int				tail_f;
	int				head_r;
	int				tail_r;
	head_f = 0;
	tail_f = 1;
	head_r = 0;
	tail_r = 1;
	fwd[0].st = *start;
	fwd[0].parent = -1;
	t_state goal = {.size_a = N, .size_b = 0};
	int i = 0;
	while (i < N)
	{
		goal.a[i] = i;
		i++;
	}
	rev[0].st = goal;
	rev[0].parent = -1;
	vis_fwd_hash[0] = state_hash(&fwd[0].st);
	vis_rev_hash[0] = state_hash(&rev[0].st);
	while (head_f < tail_f && head_r < tail_r)
	{
		int expand_fwd = (tail_f - head_f <= tail_r - head_r);
		int cur_head = expand_fwd ? head_f++ : head_r++;
		t_node *cur = expand_fwd ? &fwd[cur_head] : &rev[cur_head];
		int k = 0;
		while (k < 11)
		{
			t_state next;
			if (!apply_op(&cur->st, &next, g_ops[k]))
			{
				k++;
				continue;
			}
			uint32_t h = state_hash(&next);
			uint32_t *vis = expand_fwd ? vis_fwd_hash : vis_rev_hash;
			int *tail = expand_fwd ? &tail_f : &tail_r;
			int sz = expand_fwd ? tail_f : tail_r;
			int seen = 0;
			int i2 = 0;
			while (i2 < sz)
			{
				if (vis[i2] == h)
				{
					seen = 1;
					break;
				}
				i2++;
			}
			if (seen)
			{
				k++;
				continue;
			}
			uint32_t *vis_opp = expand_fwd ? vis_rev_hash : vis_fwd_hash;
			int sz_opp = expand_fwd ? tail_r : tail_f;
			int join_idx = -1;
			int i3 = 0;
			while (i3 < sz_opp)
			{
				if (vis_opp[i3] == h)
				{
					join_idx = i3;
					break;
				}
				i3++;
			}
			if (join_idx != -1)
			{
				int len_front = 0;
				int len_back = 0;
				t_op seq_front[128];
				t_op seq_back[128];
				int idx = cur_head;
				while (idx != -1)
				{
					seq_front[len_front++] = g_ops[k];
					seq_front[len_front++] = fwd[idx].op;
					idx = fwd[idx].parent;
				}
				idx = join_idx;
				while (idx != -1)
				{
					seq_back[len_back++] = rev[idx].op;
					idx = rev[idx].parent;
				}
				int pos = 0;
				int i4 = len_front - 2;
				while (i4 >= 0)
					out_seq[pos++] = seq_front[i4--];
				int i5 = 0;
				while (i5 < len_back - 1)
					out_seq[pos++] = inverse_op(seq_back[i5++]);
				*out_len = pos;
				return (1);
			}
			t_node *dst = expand_fwd ? &fwd[*tail] : &rev[*tail];
			*dst = (t_node){.st = next, .parent = cur_head, .op = g_ops[k]};
			(expand_fwd ? vis_fwd_hash : vis_rev_hash)[(*tail)++] = h;
			k++;
		}
	}
	return (0);
}

void	sort_all_chunks(t_Stacks *st, t_op *ops, unsigned int *op_count, const t_chunks *chunks)
{
	t_state	start;
	int		i;
	int		len;

	start.size_a = st->a_stack.size;
	start.size_b = st->b_stack.size;
	i = 0;
	while (i < start.size_a)
	{
		start.a[i] = st->a_stack.array[(st->a_stack.top + i) % DEQUE_CAPACITY];
		i++;
	}
	i = 0;
	while (i < start.size_b)
	{
		start.b[i] = st->b_stack.array[(st->b_stack.top + i) % DEQUE_CAPACITY];
		i++;
	}
	len = 0;
	if (bfs_solve9(&start, ops, &len))
	{
		ops[len] = LAST;
		*op_count = len;
		return ;
	}
	for (int i = 0; i < chunk_sz; ++i)
    	ops[len + i] = RA;
	ops[len + chunk_sz] = LAST;
	*op_len = len + chunk_sz;

	i = 0;
	while (i < chunks->count)
	{
		size_t count = chunks->chunks[i].size;
		size_t j = 0;
		while (j < count)
		{
			do_op(st, PB, ops, op_count);
			j++;
		}
		j = 0;
		while (j < count)
		{
			do_op(st, PA, ops, op_count);
			j++;
		}
		i++;
	}
	ops[*op_count] = LAST;
}
