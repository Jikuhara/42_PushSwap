# C言語で実装する円形配列を使ったDeque（両端キュー）

## はじめに

Deque（Double-ended queue：両端キュー）は、データ構造の一つで、先頭と末尾の両方から要素の挿入・削除が可能なキューです。今回は、C++のDequeをC言語で再実装し、42Tokyoのpush_swapプロジェクトで活用した例を解説します。

## C++のDequeの実装方法

C++のstd::dequeには主に3つの実装方法があります：

### 1. 単純基盤配列実装（Simple Array-based Implementation）
- 固定サイズの配列を円形に使用
- メモリ効率が良く、実装がシンプル
- **今回採用した方法**

### 2. 動的基盤配列実装（Dynamic Array-based Implementation）
- 複数の固定サイズブロックを管理
- メモリ使用量を動的に調整可能
- 一般的なstd::dequeの実装方法

### 3. 連結リスト基盤実装（Linked List-based Implementation）
- ノードをリンクで繋いだ構造
- メモリ使用量が要素数に比例
- ポインタ操作が複雑

それぞれにメリット・デメリットがありますが、今回は**単純基盤配列実装**でC++のDequeをC言語で再実装しました。この方法は理解しやすく、push_swapのような用途には最適です。

## Dequeとは

Dequeは以下の特徴を持つデータ構造です：

- **前方挿入・削除**: `push_front`, `pop_front`
- **後方挿入・削除**: `push_back`, `pop_back`
- **ランダムアクセス**: インデックスによる要素アクセス

配列とリンクリストの良いところを組み合わせたような性質を持ちます。

## 実装方針

今回の実装では、**円形配列（Circular Array）**を使用しています。この方法には以下のメリットがあります：

- メモリ効率が良い（動的メモリ確保が不要）
- キャッシュ効率が良い
- インデックスアクセスが高速（O(1)）

## データ構造の定義

```c
#define DEQUE_CAPACITY 1001

typedef struct s_Deque
{
    int             top;        // 先頭要素のインデックス
    int             bottom;     // 末尾要素の次のインデックス
    unsigned int    size;       // 現在の要素数
    int             array[DEQUE_CAPACITY];  // データ格納用配列
} t_Deque;
```

### ポイント

- `top`: 先頭要素の位置を示す
- `bottom`: 末尾要素の**次の位置**を示す
- `size`: 現在格納されている要素数
- 配列は固定サイズで、円形に使用する

## 基本操作の実装

### 初期化

```c
void deque_init(t_Deque *deque)
{
    deque->top = 0;
    deque->bottom = 0;
    deque->size = 0;
    ft_bzero(deque->array, sizeof(int) * DEQUE_CAPACITY);
}
```

### 状態確認関数

```c
bool deque_is_empty(const t_Deque *deque)
{
    return (deque->size == 0);
}

bool deque_is_full(const t_Deque *deque)
{
    return (deque->size == DEQUE_CAPACITY);
}
```

### 前方への挿入 (push_front)

```c
bool deque_push_front(t_Deque *deque, int num)
{
    if (deque_is_full(deque))
        return (false);
    
    // topを一つ前に移動（円形配列なので余りを取る）
    deque->top = (deque->top - 1 + DEQUE_CAPACITY) % DEQUE_CAPACITY;
    deque->array[deque->top] = num;
    deque->size += 1;
    return (true);
}
```

**ポイント**: `(deque->top - 1 + DEQUE_CAPACITY) % DEQUE_CAPACITY`で負の数を避けながら円形配列を実現

### 後方への挿入 (push_back)

```c
bool deque_push_back(t_Deque *deque, int num)
{
    if (deque_is_full(deque))
        return (false);
    
    if (deque->size == 0)
    {
        // 空の場合はtopの位置に挿入
        deque->array[deque->top] = num;
        deque->bottom = (deque->top + 1) % DEQUE_CAPACITY;
    }
    else
    {
        // bottomの位置に挿入してbottomを進める
        deque->array[deque->bottom] = num;
        deque->bottom = (deque->bottom + 1) % DEQUE_CAPACITY;
    }
    deque->size += 1;
    return (true);
}
```

### 前方からの削除 (pop_front)

```c
bool deque_pop_front(t_Deque *deque, int *out)
{
    if (deque_is_empty(deque))
        return (false);
    
    *out = deque->array[deque->top];
    deque->top = (deque->top + 1) % DEQUE_CAPACITY;
    deque->size -= 1;
    return (true);
}
```

### 後方からの削除 (pop_back)

```c
bool deque_pop_back(t_Deque *deque, int *out)
{
    if (deque_is_empty(deque))
        return (false);
    
    deque->bottom = (deque->bottom - 1 + DEQUE_CAPACITY) % DEQUE_CAPACITY;
    *out = deque->array[deque->bottom];
    deque->size -= 1;
    return (true);
}
```

### インデックスアクセス

```c
int deque_peek_at_Nth(const t_Deque *deque, unsigned int index)
{
    size_t position;
    
    if (index >= deque->size)
        return (0);  // エラー値として0を返す
    
    position = (deque->top + index) % DEQUE_CAPACITY;
    return (deque->array[position]);
}
```

## 円形配列の仕組み

この実装の核心は**円形配列**の概念です：

```
初期状態: top=0, bottom=0, size=0
[_, _, _, _, _]
 ^
 top=bottom

push_back(1): top=0, bottom=1, size=1
[1, _, _, _, _]
 ^  ^
 top bottom

push_front(2): top=4, bottom=1, size=2
[1, _, _, _, 2]
          ^  ^
          top bottom

push_back(3): top=4, bottom=2, size=3
[1, 3, _, _, 2]
    ^     ^
    bottom top
```

## 実装のメリット・デメリット

### メリット

1. **メモリ効率**: 固定サイズの配列を使用するため、メモリの断片化が起きない
2. **高速アクセス**: 全ての操作がO(1)
3. **キャッシュフレンドリー**: 連続したメモリ領域を使用
4. **シンプル**: ポインタ操作が不要

### デメリット

1. **容量制限**: 事前に最大サイズを決める必要がある
2. **メモリ使用量**: 使用していない領域も確保される

## 使用例

```c
t_Deque deque;
int value;

// 初期化
deque_init(&deque);

// データの挿入
deque_push_front(&deque, 10);
deque_push_back(&deque, 20);
deque_push_front(&deque, 5);

// データの取得
deque_pop_front(&deque, &value);  // value = 5
deque_pop_back(&deque, &value);   // value = 20

// インデックスアクセス
int first = deque_peek_at_Nth(&deque, 0);  // first = 10
```

## まとめ

円形配列を使ったDequeの実装は、効率的で理解しやすいデータ構造です。特に42Tokyoのpush_swapのような、決まった範囲内でのデータ操作が中心となるプロジェクトには最適だと思います。

これらは、アルゴリズムの学習やデータ構造の実装でも役立つので、ぜひマスターしてください！

## 参考資料

- [cpprefjp - std::deque](https://cpprefjp.github.io/reference/deque/deque.html)
- [Wikipedia - 両端キュー](https://ja.wikipedia.org/wiki/%E4%B8%A1%E7%AB%AF%E3%82%AD%E3%83%A5%E3%83%BC)
- [deque(両端キュー)とは](http://vivi.dyndns.org/tech/cpp/deque.html)
- 入門 データ構造とアルゴリズム

---

*Feedbackしていただけると幸いです！*