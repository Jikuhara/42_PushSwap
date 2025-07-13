/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_print_operation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjikuhar <kjikuhar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 18:25:14 by kjikuhar          #+#    #+#             */
/*   Updated: 2025/06/02 21:20:00 by kjikuhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
/* けしてね */
#include <stdio.h>

// 回転操作を統合最適化する関数
static void	optimize_rotation_operations(t_op *ops)
{
	unsigned int	i;
	unsigned int	write_pos;

	i = 0;
	write_pos = 0;

	while (ops[i] != LAST)
	{
		// 回転操作の連続をチェック (RA, RRA, RB, RRB)
		if (ops[i] == RA || ops[i] == RRA || ops[i] == RB || ops[i] == RRB)
		{
			unsigned int	ra_count = 0;
			unsigned int	rra_count = 0;
			unsigned int	rb_count = 0;
			unsigned int	rrb_count = 0;

			// 連続する回転操作をカウント
			while (ops[i] != LAST &&
				(ops[i] == RA || ops[i] == RRA || ops[i] == RB || ops[i] == RRB))
			{
				if (ops[i] == RA)
					ra_count++;
				else if (ops[i] == RRA)
					rra_count++;
				else if (ops[i] == RB)
					rb_count++;
				else if (ops[i] == RRB)
					rrb_count++;
				i++;
			}

			// Step 1: 相殺処理 (RA vs RRA, RB vs RRB)
			unsigned int	net_ra = 0;
			unsigned int	net_rra = 0;
			unsigned int	net_rb = 0;
			unsigned int	net_rrb = 0;

			if (ra_count > rra_count)
				net_ra = ra_count - rra_count;
			else if (rra_count > ra_count)
				net_rra = rra_count - ra_count;

			if (rb_count > rrb_count)
				net_rb = rb_count - rrb_count;
			else if (rrb_count > rb_count)
				net_rrb = rrb_count - rb_count;

			// Step 2: 同時操作への統合
			unsigned int	j;

			// RR統合 (RA + RB -> RR)
			unsigned int rr_count = (net_ra < net_rb) ? net_ra : net_rb;
			for (j = 0; j < rr_count; j++)
				ops[write_pos++] = RR;

			// RRR統合 (RRA + RRB -> RRR)
			unsigned int rrr_count = (net_rra < net_rrb) ? net_rra : net_rrb;
			for (j = 0; j < rrr_count; j++)
				ops[write_pos++] = RRR;

			// 残りの単独操作を追加
			unsigned int remaining_ra = net_ra - rr_count;
			unsigned int remaining_rb = net_rb - rr_count;
			unsigned int remaining_rra = net_rra - rrr_count;
			unsigned int remaining_rrb = net_rrb - rrr_count;

			for (j = 0; j < remaining_ra; j++)
				ops[write_pos++] = RA;
			for (j = 0; j < remaining_rb; j++)
				ops[write_pos++] = RB;
			for (j = 0; j < remaining_rra; j++)
				ops[write_pos++] = RRA;
			for (j = 0; j < remaining_rrb; j++)
				ops[write_pos++] = RRB;
		}
		// PA/PB の相殺をチェック
		else if (ops[i] == PA || ops[i] == PB)
		{
			unsigned int	pa_count = 0;
			unsigned int	pb_count = 0;
			while (ops[i] != LAST && (ops[i] == PA || ops[i] == PB))
			{
				if (ops[i] == PA)
					pa_count++;
				else
					pb_count++;
				i++;
			}

			if (pa_count > pb_count)
			{
				unsigned int remaining = pa_count - pb_count;
				unsigned int j;
				for (j = 0; j < remaining; j++)
					ops[write_pos++] = PA;
			}
			else if (pb_count > pa_count)
			{
				// PBの方が多い場合、余分なPBを追加
				unsigned int remaining = pb_count - pa_count;
				unsigned int j;
				for (j = 0; j < remaining; j++)
				{
					ops[write_pos++] = PB;
				}
			}
		}
		else
		{
			// その他の操作はそのままコピー
			ops[write_pos++] = ops[i++];
		}
	}

	// 終端マーカーを設定
	ops[write_pos] = LAST;
}

// 特定パターンの最適化関数 (RA PB RRA -> SA PB, RB PA RRB -> SB PA)
static void	optimize_specific_patterns(t_op *ops)
{
	unsigned int	i;
	unsigned int	write_pos;

	i = 0;
	write_pos = 0;

	while (ops[i] != LAST)
	{
		// パターン1: RA PB RRA -> SA PB (2番目の値をBへpush)
		if (ops[i] == RA && ops[i + 1] == PB && ops[i + 2] == RRA)
		{
			ops[write_pos++] = SA;
			ops[write_pos++] = PB;
			i += 3; // 3つの操作をスキップ
		}
		// パターン2: RB PA RRB -> SB PA (B->A 2番目挿入)
		else if (ops[i] == RB && ops[i + 1] == PA && ops[i + 2] == RRB)
		{
			ops[write_pos++] = SB;
			ops[write_pos++] = PA;
			i += 3; // 3つの操作をスキップ
		}
		else
		{
			// その他の操作はそのままコピー
			ops[write_pos++] = ops[i++];
		}
	}

	// 終端マーカーを設定
	ops[write_pos] = LAST;
}

void	print_operation(t_op *ops)
{
	unsigned int	i;
	int				tmp;
	char			*op_strs[] = {"sa", "sb", "ss", "pa", "pb", "ra", "rb",
		"rr", "rra", "rrb", "rrr"};

	// 特定パターンの最適化を実行
	optimize_specific_patterns(ops);
	// 統合最適化を実行（相殺 + 同時操作統合を一度に処理）
	optimize_rotation_operations(ops);
	// 念のため再度実行（複雑なパターンに対応）
	optimize_rotation_operations(ops);


	i = 0;
	while (ops[i] != LAST)
	{
		/* ほんまはft_pritntf */
		tmp = printf("%s\n", op_strs[ops[i]]);
		if (tmp == -1)
			exit_with_error();
		i++;
	}
}
