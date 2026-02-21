# Palindrome Checker (std::deque)

## What it does
Reads **one word** from stdin (assumed lowercase letters only) and prints either:
- `palindrome`
- `not palindrome`

## Why `std::deque` instead of `std::queue`?
Palindrome checking compares the **front** and **back** characters repeatedly.
- `std::deque`: efficient `front/back` access + `pop_front/pop_back`
- `std::queue`: FIFO-only interface; no direct `back` removal, so it’s not a good fit here

## Build
```bash
g++ -std=c++17 -O2 -Wall -Wextra -pedantic PalindromeDequeAssignment/main.cpp -o palindrome
```

## Run
```bash
echo racecar | ./palindrome
echo hello | ./palindrome
```