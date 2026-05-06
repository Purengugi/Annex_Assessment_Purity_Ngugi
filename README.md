# Annex Assessment - Purity Ngugi

## Overview
This repository contains solutions to coding assessment problems implemented in C, C++, and SQL:

| File               | Language | Problem Description |
|--------------------|----------|---------------------|
| `pth_factor.c`     | C        | Find the p-th smallest factor of number n (1-indexed) |
| `top_articles.cpp` | C++      | Fetch and rank top articles from HackerRank JSON mock API by comments (DESC), then title (DESC) |
| `top_students.sql` | SQL      | Query top 3 students by score (DESC), then ID (ASC) |

## Prerequisites
- macOS/Linux/Unix-like system with:
  - `gcc` (for C)
  - `g++` (for C++)
  - `libcurl` and `json.hpp` (required for `top_articles.cpp` API fetches)
- SQL client (e.g., sqlite3, psql) for SQL query

Install libcurl on Ubuntu/Debian:
```bash
sudo apt install libcurl4-openssl-dev
```

Download the nlohmann JSON header:
```bash
curl -o json.hpp https://raw.githubusercontent.com/nlohmann/json/develop/single_include/nlohmann/json.hpp
```

## How to Run

### 1. pth_factor.c (Pth Factor)
```bash
gcc -o pth_factor pth_factor.c
echo "10 3" | ./pth_factor
```

**Expected Output:**
```
5
```

Additional test cases:
```
Input: 12 6  → Output: 12   (factors of 12: 1,2,3,4,6,12)
Input: 12 7  → Output: 0    (only 6 factors exist)
```

### 2. top_articles.cpp (Top Articles)
Place `json.hpp` in the same directory as `top_articles.cpp`, then:
```bash
g++ -std=c++17 -o top_articles top_articles.cpp -lcurl
echo "2" | ./top_articles
```

**Expected Output:**
```
UK votes to leave EU
F.C.C. Repeals Net Neutrality Rules
```

*Note: Fetches live data from `https://jsonmock.hackerrank.com/api/articles`; requires internet.*

### 3. top_students.sql (Top Students)
Assuming a `STUDENT` table with columns `ID`, `NAME`, `SCORE`:
```bash
sqlite3 test.db
```

Then paste/run the query:
```sql
SELECT ID, NAME
FROM STUDENT
ORDER BY SCORE DESC, ID ASC
LIMIT 3;
```

**Expected Output:** (based on sample data provided in the assessment)
```
6|Sid
7|Tom
4|Dick
```

## Author
Purity Ngugi
