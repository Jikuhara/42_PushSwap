# Push Swap

## 概要
整数のスタックを最小限の操作でソートするプログラム。２つのスタック（A, B）と指定された操作のみを使用して効率的にソートを行う。

## 使用可能な操作
- `sa`: stack A の先頭2要素を交換
- `sb`: stack B の先頭2要素を交換
- `ss`: sa と sb を同時に実行
- `pa`: stack B の先頭を stack A の先頭に移動
- `pb`: stack A の先頭を stack B の先頭に移動
- `ra`: stack A を上方向に1要素ローテーション
- `rb`: stack B を上方向に1要素ローテーション
- `rr`: ra と rb を同時に実行
- `rra`: stack A を下方向に1要素ローテーション
- `rrb`: stack B を下方向に1要素ローテーション
- `rrr`: rra と rrb を同時に実行

## アルゴリズム戦略

### 1. 少数要素 (≤ 5要素)
**手法**: ハードコーディングされた最適解
- 要素数ごとに最適な操作手順を実装
- 3要素：最大3操作
- 5要素：最大12操作

### 2. 中規模要素 (6～100要素v)
**手法**: チャンク分割戦略
1. 要素を順位に基づいて複数のチャンクに分類
2. チャンクごとにB側へ移動（最適な位置に回転）
3. Bから最大値を順にA側へ戻す

### 3. 大規模要素 (101～500要素)
**手法**: ビット単位基数ソート
1. 各数値のビット表現を最下位ビットから順に処理
2. 現在のビットが0ならB側へ、1ならA側でローテーション
3. 全ビット処理後、B側の要素を全てA側へ戻す

## 性能目標
- 100要素: 700操作未満（優）/ 1100操作未満（良）
- 500要素: 5500操作未満（優）/ 8500操作未満（良）

## 実装方針

### データ構造
- 双方向リンクリスト：回転操作が効率的
- 各要素に「順位」情報を付与：ソート位置の判断に使用

### 実装ステップ
1. 引数解析と入力検証
   - 整数値チェック
   - 重複値チェック
   - オーバーフロー検出

2. スタック操作の基本機能実装
   - push, pop, swap, rotate, reverse-rotate

3. サイズ別ソートアルゴリズム実装
   - 小規模（≤5）
   - 中規模（6～100）
   - 大規模（101～500）

4. 最適化とテスト
   - 特殊ケースの対応
   - エッジケースのテスト

## プロジェクト構成
```
push_swap/
├── includes/         # ヘッダファイル
├── libft/            # 自作ライブラリ
├── main.c            # メインプログラム
├── parse.c           # 引数解析
├── stack.c           # スタック構造と基本操作
├── operations.c      # push_swap操作実装
├── sort_small.c      # 小規模ソート
├── sort_medium.c     # 中規模ソート
├── sort_large.c      # 大規模ソート
├── utils.c           # ユーティリティ関数
└── Makefile          # ビルド設定
```

## ボーナス：Checker
- 操作列を標準入力から受け取り、正しくソートされるか検証
- `OK` または `KO` を表示


# 具体的に使用可能なアルゴリズム
列挙していく。
# Push_swap で使用可能なアルゴリズム一覧

## 1. バブルソート
**概要**: 隣接する要素を比較・交換していくシンプルなソート
**実装**: SA + RA の組み合わせで一周し、交換が発生しなくなるまで繰り返す
**操作数**: O(n²) - 約 n²+n(n-1)/2 操作
**適用範囲**: 要素数≤10程度の小規模データに限る

## 2. 選択ソート
**概要**: 最小値を順に選択してソート済み領域に移動
**実装**: 最小値をRA操作で先頭に移動→PBでBに移動→最後にPA
**操作数**: O(n²) - 約 (n²+3n)/2 操作
**適用範囲**: 要素数≤20程度の小規模データ

## 3. 挿入ソート
**概要**: 要素を1つずつ適切な位置に挿入
**実装**: 各要素をStackBの適切な位置にRB+PB+RRBで挿入→最後にPA
**操作数**: O(n²) - 約 n(n+1) 操作
**適用範囲**: 小～中規模データ(≤30)

## 4. クイックソート
**概要**: ピボットを基準にデータを分割して再帰的にソート
**実装**: ピボット未満をStackBへ→Aをソート→Bをソート→マージ
**操作数**: 平均O(n log n)、最悪O(n²)
**適用範囲**: 中規模データ(20～100)に効果的

## 5. チャンク分割戦略
**概要**: データを複数のチャンクに分けて効率的に移動
**実装**: 要素を順位でチャンク分類→B側へ移動→効率的に戻す
**操作数**: チャンク数に依存、約 O(n log n)
**適用範囲**: 中規模データ(50～200)に最適

## 6. 基数ソート (Radix Sort)
**概要**: 数値の各ビットを順に処理するノンコンパラティブソート
**実装**: 最下位ビットから順に、0はBへ1はAに残す→次のビットへ
**操作数**: O(d×n) (dはビット数)、約 11n 操作(32ビット整数)
**適用範囲**: 大規模データ(100～500)に最適

## 7. ハイブリッドアプローチ
**概要**: データサイズに応じて異なるアルゴリズムを適用
**実装**: ≤5:ハードコード、≤50:挿入、≤100:チャンク、>100:基数
**操作数**: 各アルゴリズムの特性を組み合わせて最適化
**適用範囲**: すべてのサイズに対応

## 8. 最適化Stack Aローテーション
**概要**: 挿入操作前にStackAを最適な位置に回転させる
**実装**: RAとRRAのコスト計算→最小コスト操作を選択
**操作数**: 約 25～30%の操作削減が可能
**適用範囲**: 他アルゴリズムと組み合わせて使用

これらのアルゴリズムの中から、データサイズやパフォーマンス要件に応じて最適なものを選択するか、組み合わせて使用するのが効果的です。


## Bubble Sort
手数
一周で最大1つの要素を正しい位置に移動。最悪ケースでO(n^2)の時間計算量。
基本的に、1周（$= n$）で、1つ。swap操作が入れば$+1$。
最悪の場合、$n$週目にn-1回swapが発生する。
最も最悪の場合の手数は、
$n(n-1)/2 + n^2 = 3/2 n^2 - 1/2n$
例えば、
| n | 計算式 | 総操作数 |
|---|--------|----------|
| 5 | $\frac{5(5-1)}{2} + 5^2 = \frac{20}{2} + 25$ | 35 |
| 10 | $\frac{10(10-1)}{2} + 10^2 = \frac{90}{2} + 100$ | 145 |
| 20 | $\frac{20(20-1)}{2} + 20^2 = \frac{380}{2} + 400$ | 590 |
| 30 | $\frac{30(30-1)}{2} + 30^2 = \frac{870}{2} + 900$ | 1455 |
| 100 | $\frac{100(100-1)}{2} + 100^2 = \frac{4950}{2} + 10000$ | 14950 |
| 500 | $\frac{500(500-1)}{2} + 500^2 = \frac{124750}{2} + 250000$ | 624750 |

具体例。
```
n = 5
5 4 3 2 1
1週目: 4 3 2 1 5 (4回swap)
2週目: 3 2 1 4 5 (3回swap)
3週目: 2 1 3 4 5 (2回swap)
4週目: 1 2 3 4 5 (1回swap)
5週目: 1 2 3 4 5 (0回swap)
合計: 4 + 3 + 2 + 1 = 10回swap
合計手数: 10 + 5 * 5 = 35
```

```
n = 10
10 9 8 7 6 5 4 3 2 1
1週目: 9 8 7 6 5 4 3 2 1 10 (9回swap)
2週目: 8 7 6 5 4 3 2 1 9 10 (8回swap)
3週目: 7 6 5 4 3 2 1 8 9 10 (7回swap)
4週目: 6 5 4 3 2 1 7 8 9 10 (6回swap)
5週目: 5 4 3 2 1 6 7 8 9 10 (5回swap)
6週目: 4 3 2 1 5 6 7 8 9 10 (4回swap)
7週目: 3 2 1 4 5 6 7 8 9 10 (3回swap)
8週目: 2 1 3 4 5 6 7 8 9 10 (2回swap)
9週目: 1 2 3 4 5 6 7 8 9 10 (1回swap)
10週目: 1 2 3 4 5 6 7 8 9 10 (0回swap)
合計: 9 + 8 + 7 + 6 + 5 + 4 + 3 + 2 + 1 = 45回swap
合計手数: 45 + 10 * 10 = 145
```
##### 実装方法
```c

/* bubble_sort */
static void	execute_bubble_cycle(t_Stacks *stacks, unsigned char *ops,
		unsigned int *op_count, int *swapped)
{
	int	j;
	int	size;

	size = stacks->a_stack.size;
	*swapped = 0;
	j = 0;
	while (j < size - 1)
	{
		if (deque_peek_at_Nth(&stacks->a_stack,
				0) > deque_peek_at_Nth(&stacks->a_stack, 1))
		{
			do_op(stacks, SA, ops, op_count);
			*swapped = 1;
		}
		do_op(stacks, RA, ops, op_count);
		j++;
	}
	do_op(stacks, RA, ops, op_count);
}

void	sort_stacks(t_Stacks *stacks, unsigned char *ops)
{
	const size_t	size = stacks->a_stack.size;
	unsigned int	op_count;
	int				swapped;
	int				j;

	op_count = 0;
	if (size <= 1)
		return (ops[0] = LAST, (void)0);
	swapped = 1;
	while (swapped)
	{
		execute_bubble_cycle(stacks, ops, &op_count, &swapped);
	}
	ops[op_count] = LAST;
}
```
v

## Selection Sort
最小値を探索し、そこまで$RA$して、Stack Aの先頭に移動。最悪$n - 1$ 手数。
その後、$PB$でStack Bに移動。$1$ 手数。
Stack Bで逆三角形にして、Stack Aに戻す。$n$ 手数。
最悪の場合、合計で、
$$
\begin{align}
\sum _{k = 1} ^{n} [{(k - 1) + 1}] + n &= 1/2n(n + 1) + n \\
&= 1/2n^2 + 3/2n
\end{align}
$$
例えば、

| n | 計算式 | 総操作数 |
|---|--------|----------|
| 5 | $\frac{5^2+3(5)}{2} = \frac{25+15}{2}$ | 20 |
| 10 | $\frac{10^2+3(10)}{2} = \frac{100+30}{2}$ | 65 |
| 20 | $\frac{20^2+3(20)}{2} = \frac{400+60}{2}$ | 230 |
| 30 | $\frac{30^2+3(30)}{2} = \frac{900+90}{2}$ | 495 |
| 100 | $\frac{100^2+3(100)}{2} = \frac{10000+300}{2}$ | 5,150 |
| 500 | $\frac{500^2+3(500)}{2} = \frac{250000+1500}{2}$ | 125,750 |

具体例
```
n = 5
5 4 3 2 1
Stack A: 5 4 3 2 1
Stack B:
1. 最小値1を見つけて、RAして先頭に移動
   Stack A: 1 5 4 3 2
   Stack B:
2. PBでStack Bに移動
   Stack A: 5 4 3 2
   Stack B: 1

3. 最小値2を見つけて、RAして先頭に移動
   Stack A: 2 5 4 3
   Stack B: 1
4. PBでStack Bに移動
   Stack A: 5 4 3
   Stack B: 1 2

Stack Bを逆三角形にして、Stack Aに戻す
5. Stack A:
   Stack B: 5 4 3 2 1

PAでStack Aに戻す
   Stack A:　1 2 3 4 5
   Stack B:

合計20手数
```

実装方法
```c
/* selection_sort */
#include "push_swap.h"

int	min(t_Deque *deque)
{
	int		min_val;
	size_t	idx;

	if (deque_is_empty(deque))
		return (INT_MAX);
	min_val = INT_MAX;
	idx = deque->top;
	for (size_t i = 0; i < deque->size; ++i)
	{
		if (deque->array[idx] < min_val)
			min_val = deque->array[idx];
		idx = (idx + 1) % DEQUE_CAPACITY;
	}
	return (min_val);
}

void	sort_stacks(t_Stacks *stacks, unsigned char *ops)
{
	unsigned int	op_count;

	if (stacks->a_stack.size <= 1)
	{
		ops[0] = LAST;
		return ;
	}
	op_count = 0;
	while (!deque_is_empty(&stacks->a_stack))
	{
		while (stacks->a_stack.array[stacks->a_stack.top]
			!= min(&stacks->a_stack))
			do_op(stacks, RA, ops, &op_count);
		do_op(stacks, PB, ops, &op_count);
	}
	while (!deque_is_empty(&stacks->b_stack))
		do_op(stacks, PA, ops, &op_count);
	ops[op_count] = LAST;
}
```

## Insertion Sort

```
##### memo
挿入ソートはn^2/4回の比較しか行わないらしい。平均で。なぜ？

GitHub Copilot
挿入ソートの比較回数が平均n²/4回になる理由
挿入ソートが平均でn²/4回の比較しか行わない理由は、その動作原理に基づいています：

理論的な説明
挿入ソートの基本動作:

配列の各要素を順番に取り出し、既にソートされた部分配列の適切な位置に挿入します
i番目の要素を挿入するには、それより前のソート済み要素と比較が必要です
平均比較回数の計算:

1番目の要素：比較不要（0回）
2番目の要素：最悪1回、平均0.5回（1/2回）
3番目の要素：最悪2回、平均1回（2/2回）
4番目の要素：最悪3回、平均1.5回（3/2回）
...
n番目の要素：最悪(n-1)回、平均(n-1)/2回
全体の平均比較回数:

Push Swapでの意味
Push Swapでの挿入ソート実装では、この特性は特に重要です：

StackAからStackBに要素を挿入する際、平均して要素数の半分のRB操作が必要
最悪の場合と比較して、操作回数が大幅に少なくなる可能性がある
要素数が小さい場合（~30要素以下）、他のアルゴリズムより効率的になる場合がある
このため、挿入ソートは小～中規模のデータに対して効率的な選択肢となります。

Jikuhara
うわーーーなるほどね！！！ 選択ソートは、未ソート内で比較を行って最小値を求めるため、n^2/2回の比較が必要やけど、 挿入ソートはソート済内で比較を行うため、半分は比較する必要がなくなり、n^2/4回に減るんや！！
```

挿入ソートは、要素を1つずつ適切な位置に挿入していく手法。
具体的操作。
1. Stack Aの先頭から要素に対して、Stack Bの適切な位置までRBを行う。
2. Stack AからStack Bに対して、PBを行う。
3. Stack BをRBした回数分だけRRBを行う。
4. n回繰り返す。
5. Stack Bの要素を全てStack Aに戻す。

最悪の場合、合計で、
$$
\begin{align}
\sum _{k = 1} ^{n} [(k - 1) + 1 (k - 1)] + n &= n(n - 1) + n  + n\\
&= n^2 + n \\L
&= n(n + 1)
\end{align}
$$

例えば、
| n | 計算式 | 総操作数 |
|---|--------|----------|
| 5 | $5(5+1) = 30$ | 30 |
| 10 | $10(10+1) = 110$ | 110 |
| 20 | $20(20+1) = 420$ | 420 |
| 30 | $30(30+1) = 930$ | 930 |
| 100 | $100(100+1) = 10100$ | 10100 |
| 500 | $500(500+1) = 250500$ | 250500 |

具体例
```
n = 5
5 4 3 2 1
Stack A: 5 4 3 2 1
Stack B:
1. 5をStack Bに移動
   Stack A: 4 3 2 1
   Stack B: 5
手数: 1

2. 4をStack Bに移動
   Stack A: 3 2 1
   Stack B: 5 4
手数: 3

3. 3をStack Bに移動
   Stack A: 2 1
   Stack B: 5 4 3
手数: 5

4. 2をStack Bに移動
   Stack A: 1
   Stack B: 5 4 3 2
手数: 7

5. 1をStack Bに移動
   Stack A:
   Stack B: 5 4 3 2 1
手数: 9

Stack Bの要素をStack Aに戻す
Stack A: 1 2 3 4 5
手数: 1 + 3 + 5 + 7 + 9 + 5 = 30
合計手数: 30
```

実装方法
```c

#include "push_swap.h"

/* insertion_sort */
// Stack Aの先頭の要素をStack Bの適切な位置(RBを用いて)に移動する。
// その後、RBした回数分RRBして、もとに戻す。
// 最後にPAをN回使用して、Stack Aに戻す。
static void	insert_element_to_stack_b(t_Stacks *stacks, unsigned char *ops,
		unsigned int *op_count)
{
	int	rb_count;
	int	i;
	int	a_value;
	int	b_value;

	a_value = deque_peek_at_Nth(&stacks->a_stack, 0);
	rb_count = 0;
	i = 0;
	while (i < stacks->b_stack.size)
	{
		b_value = deque_peek_at_Nth(&stacks->b_stack, i);
		if (a_value > b_value)
			break ;
		i++;
	}
	while (rb_count < i)
	{
		do_op(stacks, RB, ops, op_count);
		rb_count++;
	}
	do_op(stacks, PB, ops, op_count);
	while (rb_count-- > 0)
		do_op(stacks, RRB, ops, op_count);
}

static void	return_all_to_stack_a(t_Stacks *stacks, unsigned char *ops,
		unsigned int *op_count)
{
	while (!deque_is_empty(&stacks->b_stack))
		do_op(stacks, PA, ops, op_count);
}

void	sort_stacks(t_Stacks *stacks, unsigned char *ops)
{
	unsigned int	op_count;

	op_count = 0;
	if (stacks->a_stack.size <= 1)
		return (ops[0] = LAST, (void)0);
	do_op(stacks, PB, ops, &op_count);
	while (!deque_is_empty(&stacks->a_stack))
		insert_element_to_stack_b(stacks, ops, &op_count);
	return_all_to_stack_a(stacks, ops, &op_count);
	ops[op_count] = LAST;
}
```


## Radix Sort
基数ソートは、数値の各ビットを順に処理するバケットソートの一種。
最下位ビットから順に、0はStack Bへ、1はStack Aに残す。
各ビット処理後、Stack Bの要素を全てStack Aへ戻す。


### 基数ソートの操作数計算

基数ソートの操作数を求める：

#### 最大ビット数の計算

n個の要素をソートするのに必要なビット数は $\lbrack \log_2(n) \rbrack + 1 $ 。
ここでは順位付け（1からn）に必要なビット数として計算。

#### 1ビットあたりの操作数

各ビットの処理では：
1. ビットが0ならPB操作、1ならRA操作 ($n$操作)
2. すべてのStack B要素をStack Aに戻す (約$1/2n$操作)

したがって、1ビットあたり約 $3/2n$ 操作が必要。

#### 総操作数の概算

$$
\begin{align}
総操作数 &= ビット数 \times ビットあたりの操作数 \\
&= (\lfloor \log_2(n) \rfloor + 1) \times 3/2 n
\end{align}
$$

### 計算例

| n | ビット数 | 計算式 | 総操作数 |
|---|---------|-------|----------|
| 5 | 3 | $3 \times \frac{3 \times 5}{2}$ | 22.5 ≈ 23 |
| 10 | 4 | $4 \times \frac{3 \times 10}{2}$ | 60 |
| 20 | 5 | $5 \times \frac{3 \times 20}{2}$ | 150 |
| 30 | 5 | $5 \times \frac{3 \times 30}{2}$ | 225 |
| 100 | 7 | $7 \times \frac{3 \times 100}{2}$ | 1,050 |
| 500 | 9 | $9 \times \frac{3 \times 500}{2}$ | 6,750 |



##### 具体例
```
n = 5
5 4 3 2 1
先頭がHead.
Stack A: 5 4 3 2 1
Stack B:

1. 1桁目のビットを確認
   - 5: 101 → 1 → Stack A
   - 4: 100 → 0 → Stack B
   - 3: 011 → 1 → Stack A
   - 2: 010 → 0 → Stack B
   - 1: 001 → 1 → Stack A

Stack A: 5 3 1
Stack B:   2 4

Stack Bの要素を全てStack Aに戻す
   Stack A: 4 2 5 3 1
   Stack B:

2. 2桁目のビットを確認
   - 2: 010 → 1 → Stack A
   - 4: 100 → 0 → Stack B
   - 5: 101 → 0 → Stack B
   - 3: 011 → 1 → Stack A
   - 1: 001 → 0 → Stack B

Stack A:   2 3
Stack B: 1 5 4

Stack Bの要素を全てStack Aに戻す
Stack A: 4 5 1 2 3
Stack B:

3. 最後のビットを確認
   - 5: 101 → 1 → Stack A
   - 3: 011 → 0 → Stack B
   - 1: 001 → 0 → Stack B
   - 4: 100 → 1 → Stack A
   - 2: 010 → 0 → Stack B

Stack A:   4 5
Stack B: 3 2 1

4. Stack Bの要素を全てStack Aに戻す
Stack A: 1 2 3 4 5
Stack B:
```

##### 実装方法
```c

#include "push_swap.h"
/* radix_sort */
static int	get_max_bits(size_t n)
{
	int	max_bits;

	max_bits = 0;
	while ((n - 1) >> max_bits)
		++max_bits;
	return (max_bits);
}

static void	process_single_bit(t_Stacks *stacks, unsigned char *ops,
		unsigned int *op_count, int bit)
{
	size_t	j;
	size_t	n;
	int		val;

	n = stacks->a_stack.size;
	j = 0;
	while (j < n)
	{
		val = deque_peek_at_Nth(&stacks->a_stack, 0);
		if ((val >> bit) & 1)
			do_op(stacks, RA, ops, op_count);
		else
			do_op(stacks, PB, ops, op_count);
		j++;
	}

}

static void	return_all_to_stack_a(t_Stacks *stacks, unsigned char *ops,
	unsigned int *op_count)
{
while (!deque_is_empty(&stacks->b_stack))
	do_op(stacks, PA, ops, op_count);
}

void	sort_stacks(t_Stacks *stacks, unsigned char *ops)
{
	const size_t	n = stacks->a_stack.size;
	unsigned int	op_count;
	int				max_bits;
	int				bit;

	op_count = 0;
	if (n <= 1)
		return (ops[0] = LAST, (void)0);
	max_bits = get_max_bits(n);
	bit = 0;
	while (bit < max_bits)
	{
		process_single_bit(stacks, ops, &op_count, bit);
		return_all_to_stack_a(stacks, ops, &op_count);
		bit++;
	}
	ops[op_count] = LAST;
}
```

あとShell_Sort Marge_sort Qick_Sort などもあるが、Push_swapでは使用しない。
