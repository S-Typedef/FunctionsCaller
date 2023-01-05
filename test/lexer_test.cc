#include <iostream>
#include <cassert>

#include "lexer.h"


int main()
{

	{
		FCLexer lexer{"abc"};
		assert(lexer.generateNextTok() == LexerErrorCode::IDENTIFIER);
		assert(lexer.getTok().value().identifier == "abc");
	}

	{
		FCLexer lexer{"abc "};
		assert(lexer.generateNextTok() == LexerErrorCode::INVALID);
	}

	{
		FCLexer lexer{"abc1"};
		assert(lexer.generateNextTok() == LexerErrorCode::IDENTIFIER);
		assert(lexer.getTok().value().identifier == "abc1");
	}

	{
		FCLexer lexer{"abc1."};
		assert(lexer.generateNextTok() == LexerErrorCode::INVALID);
	}

	{
		FCLexer lexer{"1"};
		assert(lexer.generateNextTok() == LexerErrorCode::INTEGER);
		assert(lexer.getTok().value().integetNumber == 1);
	}

	{
		FCLexer lexer{"1."};
		assert(lexer.generateNextTok() == LexerErrorCode::DOUBLE);
		assert(abs(lexer.getTok().value().floatNumber - 1) <= 1e-5);
	}

	{
		FCLexer lexer{"1a"};
		assert(lexer.generateNextTok() == LexerErrorCode::INVALID);
	}

	{
		FCLexer lexer{"1.a"};
		assert(lexer.generateNextTok() == LexerErrorCode::INVALID);
	}

	{
		FCLexer lexer{"2 "};
		assert(lexer.generateNextTok() == LexerErrorCode::INTEGER);
		assert(lexer.getTok().value().integetNumber == 2);
	}

	{
		FCLexer lexer{"2. "};
		assert(lexer.generateNextTok() == LexerErrorCode::DOUBLE);
		assert(abs(lexer.getTok().value().floatNumber - 2) <= 1e-5);
	}

	return 0;
}