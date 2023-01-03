#include <iostream>
#include <cassert>

#include "lexer.h"


int main()
{
	FCLexer lexer1{"abc"};
	FCLexer lexer2{"abc 1"};
	FCLexer lexer3{"1abc"};
	FCLexer lexer4{"abc1"};

	assert(static_cast<int>(lexer1.generateNextTok()) == 1);
	assert(lexer1.getTok() == "abc");

	assert(static_cast<int>(lexer2.generateNextTok()) == 1);
	assert(lexer2.getTok() == "abc");

	assert(static_cast<int>(lexer3.generateNextTok()) == 4);
	assert(lexer3.getTok() == " ");

	assert(static_cast<int>(lexer4.generateNextTok()) == 1);
	assert(lexer4.getTok() == "abc1");

	return 0;
}