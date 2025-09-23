# Advanced Algorithms: Practical III

**Deadline:** Saturday, September 27, 23:59
**Course code:** WBCS052-05

---

## Problem 3A: Matter and antimatter (25 points)

Researchers at the University of Algoritbury have recently constructed antimatter robots.
They want to research how antimatter robots interact with normal robots.
Therefore, they created a robot playground in the form of an `n × m` grid.

- In the **top-left square**, they place a number of **antimatter robots**.
- In each other square, they either place:
  - normal robots,
  - antimatter robots, or
  - an unbreakable barrier.
- Initially, the robots are not activated.

At the start of the experiment:

- The group of antimatter robots in the top-left square is activated.
- This group leaves **one antimatter robot behind** in that square, and the rest move either **one square right** or **one square down**.
- If the destination square contains antimatter robots, they merge and move forward together (again leaving one behind).
- If the destination square contains normal robots, annihilation happens in pairs until one type runs out.

The activated antimatter robots continue advancing one square right or down each step, leaving one behind each time, until:

- they reach the **bottom-right square**, or
- they are all annihilated, or
- only one remains in a square (which must stay there).

Robots cannot pass through unbreakable barriers.

### Task

If the activated antimatter robots choose the **optimal path**, what is the **maximum number of antimatter robots** that can eventually occupy the bottom-right square?

---

### Input

- First line: integers `n` and `m`.
- Next `n` lines: each containing `m` integers describing the playground.
  - `k` (positive) → `k` antimatter robots.
  - `-k` (negative) → `k` normal robots.
  - `0` → unbreakable barrier.

**Example Input:**

4 4
10 -3 -2 3
-6 0 -1 0
2 -1 1 1
0 0 3 -1

---

### Output

- The maximum number of antimatter robots that can reach the bottom-right square.

**Example Output:**

2

---

### Constraints

- At least one antimatter robot can always reach the bottom-right square.
- `2 ≤ n, m ≤ 4000`
- Each grid number is between `-100000` and `100000`
- The top-left square always contains at least 2 antimatter robots.
- The bottom-right square never contains a barrier.
- **Time limit:** 3 seconds per test case
- **Memory limit:** 50 MiB per test case
