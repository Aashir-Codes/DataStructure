// ============================================================
//  Bscs25079 — DT-02  |  Stack Implementations Test Suite
//  Tests: MinStack, Stack_Array, Stack_Vector
//  Compile: g++ -std=c++17 -Wall -Wextra -o test main.cpp
// ============================================================

#include <iostream>
#include <stdexcept>
#include <string>

#include "Bscs25079-DT-02-MIn-Stack.h"
#include "Bscs25079-DT-02-STACK-ARRAY.h"
#include "Bscs25079-DT-02-STACK-VECTOR.h"

// ── Tiny test framework ──────────────────────────────────────
static int passed = 0;
static int failed = 0;

void check(bool condition, const std::string &label)
{
    if (condition)
    {
        std::cout << "  [PASS]  " << label << "\n";
        ++passed;
    }
    else
    {
        std::cout << "  [FAIL]  " << label << "\n";
        ++failed;
    }
}

// Checks that calling f() throws std::runtime_error
template <typename Func>
void check_throws(Func f, const std::string &label)
{
    try
    {
        f();
        std::cout << "  [FAIL]  " << label << " (no exception thrown)\n";
        ++failed;
    }
    catch (const std::runtime_error &)
    {
        std::cout << "  [PASS]  " << label << "\n";
        ++passed;
    }
    catch (...)
    {
        std::cout << "  [FAIL]  " << label << " (wrong exception type)\n";
        ++failed;
    }
}

// ── Section header helper ────────────────────────────────────
void section(const std::string &title)
{
    std::cout << "\n============================================\n";
    std::cout << "  " << title << "\n";
    std::cout << "============================================\n";
}

// ============================================================
//  TEST GROUP 1 — Stack_Array
// ============================================================
void test_stack_array()
{
    section("Stack_Array — Basic Operations");

    Stack_Array<int> s;

    // push and top
    s.push(10);
    check(s.top() == 10, "top() == 10 after pushing 10");

    s.push(20);
    check(s.top() == 20, "top() == 20 after pushing 20");

    s.push(30);
    check(s.top() == 30, "top() == 30 after pushing 30");

    // pop
    s.pop();
    check(s.top() == 20, "top() == 20 after popping 30");

    s.pop();
    check(s.top() == 10, "top() == 10 after popping 20");

    s.pop();

    // ── Edge case: empty stack ───────────────────────────────
    section("Stack_Array — Empty Stack Guards");

    check_throws([&]()
                 { s.top(); },
                 "top() throws on empty stack");

    check_throws([&]()
                 { s.pop(); },
                 "pop() throws on empty stack");

    // ── Resize / auto-grow ───────────────────────────────────
    section("Stack_Array — Auto-Resize (push 100 elements)");

    Stack_Array<int> big(2); // starts with capacity 2
    for (int i = 1; i <= 100; i++)
        big.push(i);

    check(big.top() == 100, "top() == 100 after 100 pushes");

    for (int i = 100; i >= 2; i--)
        big.pop();

    check(big.top() == 1, "top() == 1 after popping down to first element");

    // ── String type ─────────────────────────────────────────
    section("Stack_Array — String Type");

    Stack_Array<std::string> ss;
    ss.push("hello");
    ss.push("world");
    check(ss.top() == "world", "top() == \"world\" for string stack");
    ss.pop();
    check(ss.top() == "hello", "top() == \"hello\" after pop");
}

// ============================================================
//  TEST GROUP 2 — Stack_Vector
// ============================================================
void test_stack_vector()
{
    section("Stack_Vector — Basic Operations");

    Stack_Vector<int> sv;

    sv.push(5);
    check(sv.top() == 5, "top() == 5 after pushing 5");

    sv.push(15);
    sv.push(25);
    check(sv.top() == 25, "top() == 25 after pushing 15, 25");

    sv.pop();
    check(sv.top() == 15, "top() == 15 after pop");

    sv.pop();
    sv.pop();

    // ── Edge cases ───────────────────────────────────────────
    section("Stack_Vector — Empty Stack Guards");

    check_throws([&]()
                 { sv.top(); },
                 "top() throws on empty stack");

    check_throws([&]()
                 { sv.pop(); },
                 "pop() throws on empty stack");

    // ── With capacity hint ───────────────────────────────────
    section("Stack_Vector — Capacity Hint Constructor");

    Stack_Vector<int> sv2(50);
    for (int i = 0; i < 200; i++) // push well beyond reserved capacity
        sv2.push(i);

    check(sv2.top() == 199, "top() == 199 after 200 pushes beyond reserved capacity");

    // ── Double type ──────────────────────────────────────────
    section("Stack_Vector — Double Type");

    Stack_Vector<double> sd;
    sd.push(3.14);
    sd.push(2.71);
    check(sd.top() == 2.71, "top() == 2.71 for double stack");
    sd.pop();
    check(sd.top() == 3.14, "top() == 3.14 after pop");
}

// ============================================================
//  TEST GROUP 3 — MinStack
// ============================================================
void test_min_stack()
{
    section("MinStack — Basic Push / Top / get_min");

    MinStack<int> ms;

    ms.push(5);
    check(ms.top() == 5, "top()    == 5 after pushing 5");
    check(ms.get_min() == 5, "get_min()== 5 after pushing 5");

    ms.push(3);
    check(ms.top() == 3, "top()    == 3 after pushing 3");
    check(ms.get_min() == 3, "get_min()== 3 (new min)");

    ms.push(7);
    check(ms.top() == 7, "top()    == 7 after pushing 7");
    check(ms.get_min() == 3, "get_min()== 3 (min unchanged after pushing larger value)");

    ms.push(1);
    check(ms.top() == 1, "top()    == 1 after pushing 1");
    check(ms.get_min() == 1, "get_min()== 1 (new global min)");

    // ── Pop restores correct min ─────────────────────────────
    section("MinStack — get_min() Correct After pop()");

    ms.pop(); // remove 1
    check(ms.get_min() == 3, "get_min()== 3 after popping 1");

    ms.pop(); // remove 7
    check(ms.get_min() == 3, "get_min()== 3 after popping 7");

    ms.pop(); // remove 3
    check(ms.get_min() == 5, "get_min()== 5 after popping 3 (original element)");

    ms.pop(); // remove 5 — stack now empty

    // ── Edge case: empty ─────────────────────────────────────
    section("MinStack — Empty Stack Guards");

    check_throws([&]()
                 { ms.top(); },
                 "top()     throws on empty stack");

    check_throws([&]()
                 { ms.get_min(); },
                 "get_min() throws on empty stack");

    check_throws([&]()
                 { ms.pop(); },
                 "pop()     throws on empty stack");

    // ── Duplicate values ─────────────────────────────────────
    section("MinStack — Duplicate Minimum Values");

    MinStack<int> dup;
    dup.push(2);
    dup.push(2);
    dup.push(2);
    check(dup.get_min() == 2, "get_min()== 2 with three duplicate 2s");

    dup.pop();
    check(dup.get_min() == 2, "get_min()== 2 after popping one duplicate");

    dup.pop();
    check(dup.get_min() == 2, "get_min()== 2 after popping second duplicate");

    dup.pop(); // stack empty

    // ── Negative numbers ────────────────────────────────────
    section("MinStack — Negative Numbers");

    MinStack<int> neg;
    neg.push(0);
    neg.push(-1);
    neg.push(-2);
    check(neg.get_min() == -2, "get_min()== -2 with negatives");

    neg.pop();
    check(neg.get_min() == -1, "get_min()== -1 after popping -2");

    neg.pop();
    check(neg.get_min() == 0, "get_min()== 0 after popping -1");
}

// ============================================================
//  ENTRY POINT
// ============================================================
int main()
{
    test_stack_array();
    test_stack_vector();
    test_min_stack();

    // ── Final report ─────────────────────────────────────────
    std::cout << "\n============================================\n";
    std::cout << "  RESULTS: " << passed << " passed, " << failed << " failed\n";
    std::cout << "============================================\n\n";

    return (failed == 0) ? 0 : 1;
}