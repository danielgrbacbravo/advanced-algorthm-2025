# Problem 2B: Chaos in Algsterdam! (25 points)

The city **Algsterdam** is divided into two parts by the Egg river. For pedestrians (and cyclists), the main way to cross it is to take the ferry. However, due to a segmentation fault in the centralized control software, all ferries have sunk. This leaves pedestrians with no way to cross the river!

There is also a tunnel, the **Egg tunnel**, which is only available for cars and buses. In panic, the traffic regulation centre of Algsterdam contacted several bus companies and sold them temporary licenses to transport pedestrians through the Egg tunnel.

Now, the regulators are worried about congestion. They want to know:

- On which day is the **number of valid licenses the largest**?
- For that day, also print the **names of all companies with a valid license**, in **alphabetical (ASCII) order**.
- If multiple days tie, select the **earliest** one.

---

## Input

- The first line contains an integer `n`, the number of licenses.
- Then follow `n` lines, each containing:
  - The first valid day of the license
  - The first day the license is no longer valid
  - The bus company name

Dates are given in the format `dd.mm.yyyy`.

---

## Output

- Print the **busiest day** (when most licenses are valid).
- Then print the company names (one per line, alphabetical order).
- Always print a newline at the end of the output.
