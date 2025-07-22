/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_6_chunk_sort.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codex <codex@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 00:00:00 by codex             #+#    #+#             */
/*   Updated: 2025/07/22 00:00:00 by codex            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "chunk_sort.h"

// void	init_chunks(t_chunks *chunks, size_t n)
// {
// 	int	chunk_count;
// 	int	i;

// 	chunk_count = (n + CHUNK_SIZE - 1) / CHUNK_SIZE;
// 	i = 0;
// 	while (i < chunk_count)
// 	{
// 		chunks->chunks[i].min_val = i * CHUNK_SIZE;
// 		chunks->chunks[i].max_val = (i + 1) * CHUNK_SIZE - 1;
// 		if (chunks->chunks[i].max_val >= (int)n)
// 			chunks->chunks[i].max_val = (int)n - 1;
// 		chunks->chunks[i].index = i;
// 		chunks->chunks[i].size = chunks->chunks[i].max_val - chunks->chunks[i].min_val + 1;
// 		i++;
// 	}
// 	chunks->count = chunk_count;
// }

int	chunk_contains(const t_chunk *chunk, int val)
{
	return (val >= chunk->min_val && val <= chunk->max_val);
}

#include <math.h>          // sqrt
#include <stddef.h>        // size_t

/* 最低でも 5 要素は確保するようにしつつ、
   残り個数に応じて base → 5 へ滑らかに縮む */
static size_t  next_chunk_size(size_t n_total, size_t remain, size_t base)
{
    size_t s = base + (remain * base) / n_total;   // 線形減衰
    return (s < 5) ? 5 : s;
}

/*---------------------------------------------------------------------------*/
/*  動的 chunk 生成                                                           */
/*---------------------------------------------------------------------------*/
void    init_chunks(t_chunks *chunks, size_t n)
{
    size_t  base  = (size_t)floor(sqrt((double)n));      // 初期 chunk 幅
    if (base < 10)                                       // 小規模入力の下限
        base = 10;

    size_t  pos   = 0;           // 現在のインデックス
    int     idx   = 0;           // chunk 配列の添字

    while (pos < n)
    {
        size_t sz = next_chunk_size(n, n - pos, base);
        if (sz > n - pos)                         // 最後の端数調整
            sz = n - pos;

        chunks->chunks[idx].min_val = (int)pos;
        chunks->chunks[idx].max_val = (int)(pos + sz - 1);
        chunks->chunks[idx].index   = idx;
        chunks->chunks[idx].size    = (int)sz;

        pos += sz;
        idx++;
    }
    chunks->count = idx;
}
