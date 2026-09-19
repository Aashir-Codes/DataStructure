#include <iostream>
#include <exception>

// ─── paste class definitions inline for single-file compilation ───
#include "BSCS25079-ASM-04-CircularDeque.h"
#include "BSCS25079-ASM-04-InputRestrictedDeque.h"
#include "BSCS25079-ASM-04-OutputRestrictedDeque.h"

// ─── tiny helper ─────────────────────────────────────────────────
void section(const std::string &title)
{
    std::cout << "\n══════════════════════════════\n";
    std::cout << "  " << title << "\n";
    std::cout << "══════════════════════════════\n";
}

void pass(const std::string &msg) { std::cout << "[PASS] " << msg << "\n"; }
void fail(const std::string &msg) { std::cout << "[FAIL] " << msg << "\n"; }

// ─── CircularDeque tests ──────────────────────────────────────────
void testCircularDeque()
{
    section("CircularDeque");

    CircularDeque dq(5);

    // isEmpty on fresh deque
    dq.isEmpty() ? pass("isEmpty() on empty deque") : fail("isEmpty() on empty deque");

    // insertRear: 1 2 3
    dq.insertRear(1);
    dq.insertRear(2);
    dq.insertRear(3);
    std::cout << "  after insertRear 1 2 3 -> display: ";
    dq.display();

    dq.getFront() == 1 ? pass("getFront() == 1") : fail("getFront() == 1");
    dq.getRear() == 3 ? pass("getRear()  == 3") : fail("getRear()  == 3");

    // insertFront: 0 goes before 1
    dq.insertFront(0);
    std::cout << "  after insertFront 0    -> display: ";
    dq.display();
    dq.getFront() == 0 ? pass("getFront() == 0 after insertFront") : fail("getFront() == 0 after insertFront");

    // fill to capacity (cap=5, count=4 now, one more fits)
    dq.insertRear(4);
    dq.isFull() ? pass("isFull() after 5 elements") : fail("isFull() after 5 elements");

    // overflow guard
    dq.insertRear(99) == false ? pass("insertRear returns false when full") : fail("insertRear returns false when full");

    // deleteFront: removes 0
    dq.deleteFront();
    std::cout << "  after deleteFront      -> display: ";
    dq.display();
    dq.getFront() == 1 ? pass("getFront() == 1 after deleteFront") : fail("getFront() == 1 after deleteFront");

    // deleteRear: removes 4
    dq.deleteRear();
    std::cout << "  after deleteRear       -> display: ";
    dq.display();
    dq.getRear() == 3 ? pass("getRear() == 3 after deleteRear") : fail("getRear() == 3 after deleteRear");

    // wrap-around test: drain then refill across boundary
    dq.deleteFront();
    dq.deleteFront();
    dq.deleteFront();
    dq.isEmpty() ? pass("isEmpty() after draining") : fail("isEmpty() after draining");

    dq.insertRear(10);
    dq.insertRear(20);
    dq.insertFront(5);
    std::cout << "  wrap-around display    -> display: ";
    dq.display();
    dq.getFront() == 5 ? pass("wrap getFront() == 5") : fail("wrap getFront() == 5");
    dq.getRear() == 20 ? pass("wrap getRear()  == 20") : fail("wrap getRear()  == 20");

    // underflow guard
    CircularDeque empty(3);
    empty.deleteFront() == false ? pass("deleteFront returns false when empty") : fail("deleteFront returns false when empty");
    empty.deleteRear() == false ? pass("deleteRear  returns false when empty") : fail("deleteRear  returns false when empty");
}

// ─── InputRestrictedDeque tests ───────────────────────────────────
void testInputRestrictedDeque()
{
    section("InputRestrictedDeque");

    InputRestrictedDeque ird(4);

    // only rear insertion allowed
    ird.insertRear(10);
    ird.insertRear(20);
    ird.insertRear(30);
    std::cout << "  after insertRear 10 20 30 -> display: ";
    ird.display();

    ird.getFront() == 10 ? pass("getFront() == 10") : fail("getFront() == 10");
    ird.getRear() == 30 ? pass("getRear()  == 30") : fail("getRear()  == 30");

    // deleteFront
    ird.deleteFront();
    std::cout << "  after deleteFront         -> display: ";
    ird.display();
    ird.getFront() == 20 ? pass("getFront() == 20 after deleteFront") : fail("getFront() == 20 after deleteFront");

    // deleteRear
    ird.deleteRear();
    std::cout << "  after deleteRear          -> display: ";
    ird.display();
    ird.getRear() == 20 ? pass("getRear() == 20 after deleteRear") : fail("getRear() == 20 after deleteRear");

    // fill and overflow
    ird.insertRear(40);
    ird.insertRear(50);
    ird.insertRear(60);
    ird.isFull() ? pass("isFull() correct") : fail("isFull() correct");
    ird.insertRear(99) == false ? pass("insertRear false when full") : fail("insertRear false when full");

    // drain and underflow
    ird.deleteFront();
    ird.deleteFront();
    ird.deleteFront();
    ird.deleteFront();
    ird.isEmpty() ? pass("isEmpty() after drain") : fail("isEmpty() after drain");
    ird.deleteFront() == false ? pass("deleteFront false when empty") : fail("deleteFront false when empty");
    ird.deleteRear() == false ? pass("deleteRear  false when empty") : fail("deleteRear  false when empty");
}

// ─── OutputRestrictedDeque tests ──────────────────────────────────
void testOutputRestrictedDeque()
{
    section("OutputRestrictedDeque");

    OutputRestrictedDeque ord(5);

    // both insertions allowed
    ord.insertRear(2);
    ord.insertRear(3);
    ord.insertFront(1);
    ord.insertFront(0);
    std::cout << "  after inserts 0 1 2 3  -> display: ";
    ord.display();

    ord.getFront() == 0 ? pass("getFront() == 0") : fail("getFront() == 0");
    ord.getRear() == 3 ? pass("getRear()  == 3") : fail("getRear()  == 3");

    // only front deletion allowed
    ord.deleteFront();
    std::cout << "  after deleteFront       -> display: ";
    ord.display();
    ord.getFront() == 1 ? pass("getFront() == 1 after deleteFront") : fail("getFront() == 1 after deleteFront");

    // fill test
    ord.insertFront(0);
    ord.insertRear(4);
    ord.isFull() ? pass("isFull() correct") : fail("isFull() correct");
    ord.insertRear(99) == false ? pass("insertRear false when full") : fail("insertRear false when full");
    ord.insertFront(99) == false ? pass("insertFront false when full") : fail("insertFront false when full");

    // drain and underflow
    ord.deleteFront();
    ord.deleteFront();
    ord.deleteFront();
    ord.deleteFront();
    ord.deleteFront();
    ord.isEmpty() ? pass("isEmpty() after drain") : fail("isEmpty() after drain");
    ord.deleteFront() == false ? pass("deleteFront false when empty") : fail("deleteFront false when empty");
}

// ─── entry point ──────────────────────────────────────────────────
int main()
{
    testCircularDeque();
    testInputRestrictedDeque();
    testOutputRestrictedDeque();

    std::cout << "\nAll tests done.\n";
    return 0;
}