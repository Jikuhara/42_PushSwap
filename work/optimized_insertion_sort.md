# PushSwap ― Step 1: Rear‑Insertion Plan

## 🎯 Objective

Enable **rear‑side insertion** of `StackA`'s head element into the *tail* of already‑sorted `StackB`, while preserving the descending order that PushSwap commonly maintains in `StackB` (largest at the top). This will cut the number of rotates when the correct slot is closer to the bottom than the top.

---

## 1. Design Rationale

| Before                                                                                                 | After                                                                                                                      |
| ------------------------------------------------------------------------------------------------------ | -------------------------------------------------------------------------------------------------------------------------- |
| Only *top‑side* insertion: rotate **RB** *i* times until slot is at top, `PB`, then **RRB** *i* times. | Offer symmetrical *bottom‑side* insertion: rotate **RRB** *j* times to bring tail segment up, `PB`, then **RB** *j* times. |

* If `j < i`, bottom‑side insertion wins → fewer ops.
* Lays groundwork for later steps (②⑨④) by generalising insert‑point search from both ends.

---

## 2. Algorithm Sketch

1. `a_value ← deque_peek_at_Nth(&A, 0)`
2. Scan `StackB` **from the tail** to find the first `b_value` *smaller* than `a_value`.

   ```c
   j = 0;
   while (j < B.size) {
       b_value = deque_peek_at_Nth(&B, B.size - 1 - j);
       if (a_value < b_value) break;
       j++;
   }
   // j == number of reverse‑rotates needed
   ```
3. Perform `RRB` **j** times.
4. `PB` (push `a_value` onto B’s top).
5. Perform `RB` **j** times (restore original orientation).
6. **Compare** `j` with the forward‑insertion cost `i` from the existing routine; execute whichever is smaller (this arbitration wrapper will be added in Step 2).

---

## 3. New Helper Functions

| Function                    | Prototype                                                        | Responsibility          |
| --------------------------- | ---------------------------------------------------------------- | ----------------------- |
| `find_insert_pos_from_tail` | `unsigned int find_insert_pos_from_tail(t_Deque *b, int a_val);` | Return `j`.             |
| `insert_tail_side`          | `void insert_tail_side(t_Stacks *s, t_op *ops, t_op *cnt);`      | Execute sequence in §2. |

These should mirror naming/style of existing forward‑path helpers for consistency.

---

## 4. Pseudocode Implementation

```c
static unsigned int find_insert_pos_from_tail(const t_Deque *b, int a_val)
{
    unsigned int j = 0;
    while (j < b->size)
    {
        int b_val = deque_peek_at_Nth(b, b->size - 1 - j);
        if (a_val < b_val)
            break;
        j++;
    }
    return j;
}

static void insert_tail_side(t_Stacks *stacks, t_op *ops, t_op *op_cnt)
{
    unsigned int j = find_insert_pos_from_tail(&stacks->b_stack,
                                              deque_peek_at_Nth(&stacks->a_stack, 0));
    for (unsigned int k = 0; k < j; ++k)
        do_op(stacks, RRB, ops, op_cnt);

    do_op(stacks, PB, ops, op_cnt);

    while (j--)
        do_op(stacks, RB, ops, op_cnt);
}
```

---

## 5. Integration Points

1. **Header:** add prototypes in `pushswap.h` (or equivalent).
2. **Dispatcher:**

   * Replace current `insert_element_to_stack_b` with a *strategy function* that computes both `i` (front) and `j` (rear) and calls the cheaper path.
3. **Op counter:** ensure both branches increment `op_cnt` identically.

---

## 6. Edge‑Case Handling

* **Empty `StackB`**: `j = 0`; simply `PB`.
* **`a_value` smallest of all**: full‑length rotation (`j = B.size`); still safe.
* **Duplicates**: maintain strict `>` / `<` rule you already use; duplicates land *after* earlier identicals, preserving stability.

---

## 7. Complexity & Expected Win

| Metric                                 | Top‑only | Symmetric |
| -------------------------------------- | -------- | --------- |
| Worst‑case rotates per insert          | `O(n)`   | unchanged |
| Average rotates (uniform distribution) | \~`n⁄4`  | \~`n⁄8`   |

Empirically the op‑count should drop \~25–40 % for mixed‑order inputs.

---

## 8. Unit‑Test Matrix

\| Scenario | A head | B (top→tail) | Expected ops | Notes |
\|---|---|---|---|
\| Tail insert wins | 2 | 9 8 7 6 5 1 | `RRB×2 PB RB×2` | j=2 < i=4 |
\| Head insert equal | 7 | 9 8 6 5 4 3 | Either | tie breaker rule = forward |
\| Empty B | 5 | – | `PB` | |

Use your existing harness; assert resulting B order and op‑count.

---

## 9. Milestones & Timeline (est.)

1. **Day 1** – Implement helper + tail‑side path, compile.
2. **Day 2** – Add unit tests, benchmark on random sets.
3. **Day 3** – Refactor dispatcher, push to repo, PR review.

---

## 10. Next Steps Preview

* **Step 2 (②):** Evaluate `StackA` tail element; choose between head/tail push.
* **Step 3 (③):** Exhaustive search across all A positions with smart pruning.
* **Step 4 (④):** Introduce simultaneous rotations (`RR`, `RRR`).

---

### ✨ End of Plan — Let’s build it!
