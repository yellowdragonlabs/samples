#include "tdd.h"

// 144 tests in one:
struct Base {};
struct Derived : Base {};
TESTX(test_is_base, parameters<for_each<and_cvref<Base>>,
                               for_each<and_cvref<Derived>>>) {
	EXPECT(is_base_of<Xs...>);
}

struct A; struct B; struct C; struct D; struct E; struct F; 
TESTX(test_set, parameters<set<A, B, C>, set<D, E, F>>) {
	// A, D
	// B, E
	// C, F
	EXPECT(sizeof...(Xs) == 2);
}

TESTX(test_for_each, parameters<for_each<A, B, C>, set<D, E, F>>) {
	// A, D
	// A, E
	// A, F
	// B, D
	// B, E
	// B, F
	// C, D
	// C, E
	// C, F
	EXPECT(sizeof...(Xs) == 2);
}

// Print custom format
struct S {
	int a = 14, b = 16;
};

namespace test {
	const printer_t& operator<<(const printer_t& p, const S& s) { return p.print("custom [%d, %d] format\n", s.a, s.b); }
}

TEST(custom_print) {
	EXPECT(0) << S();
}

// Tests within the same category and translation unit run in the order in which they are declared.
unsigned order = 0;
TEST(before) { EXPECT(++order == 1); }
TEST(after)  { EXPECT(++order == 2); }

RUN_ALL();
