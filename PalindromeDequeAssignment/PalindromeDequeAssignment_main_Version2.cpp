#include <deque>
#include <iostream>
#include <string>

/*
Why std::deque (and not std::queue) for palindrome checking?

- Palindrome logic needs to compare BOTH ends of the sequence repeatedly:
  front vs back, then remove both ends, etc.
- std::deque supports efficient access/removal at BOTH ends:
  - front(), back(), pop_front(), pop_back()
- std::queue is an adaptor that only exposes FIFO operations:
  you can access/pop ONLY the front, not the back, so you can't directly
  compare both ends without extra data structures or copying.

Therefore std::deque is the most suitable standard container for this task.
*/

static bool isPalindrome(const std::string& s) {
    std::deque<char> d;

    // Requirement assumption: input is lowercase letters only.
    for (char c : s) d.push_back(c);

    while (d.size() > 1) {
        if (d.front() != d.back()) return false;
        d.pop_front();
        d.pop_back();
    }
    return true;
}

int main() {
    std::string word;
    std::cin >> word; // read a single word from stdin
    std::cout << (isPalindrome(word) ? "palindrome" : "not palindrome") << '\n';
    return 0;
}