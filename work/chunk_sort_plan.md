# ChunkSort 設計プラン

## 目的

push_swap において入力された数値を複数の値域（チャンク）に分割し、チャンクごとに処理を行うことでソート操作を簡略化する「ChunkSort」戦略を実装する。

## 構造体

### `t_chunk_range`
1 つのチャンクの境界を表す。

```c
typedef struct s_chunk_range
{
    int min_val;  // 下限（含む）
    int max_val;  // 上限（含む）
} t_chunk_range;
```

### `t_chunk_map`
すべてのチャンク範囲を保持し、任意のチャンク数に対応する。

```c
typedef struct s_chunk_map
{
    size_t        chunk_count;   // チャンク数
    t_chunk_range *ranges;       // 範囲配列（size = chunk_count）
} t_chunk_map;
```

この構造体により、`chunk_count` で使用するチャンク数を、`ranges[i].min_val` ～ `ranges[i].max_val` で各チャンクの値域を指定できる。

## 関数概要

### `bool chunk_contains(const t_chunk_range *chunk, int value);`
指定した `chunk` に `value` が含まれているか確認する。

```c
bool chunk_contains(const t_chunk_range *chunk, int value);
```

- `chunk->min_val <= value && value <= chunk->max_val` の場合 `true`
- それ以外は `false`

この関数はスタック間で要素を移動する際に、各値が属するチャンクを判断するための基本手段となる。

## 実装手順

1. **チャンク範囲の計算**
   - `chunk_count` を決定した後、ソート済み値列や順位表から各チャンクの `min_val` と `max_val` を求める。
   - `t_chunk_range` の配列を確保し、求めた値を設定する。
2. **所属判定**
   - `chunk_contains` を上記の境界チェックとして実装する。
   - これにより、現在処理中のチャンク内に対象要素が含まれるかを確認できる。

実際の C 実装とソートループへの統合は、今後のコミットで追加する予定である。
