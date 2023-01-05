#include <iostream>
#include <cassert>

#include "lexer.h"


int main()
{
	auto func1 = [](auto optionalItem, auto errorCode){
		FCLexer::item_type res;
		if(optionalItem)
		{
			res = optionalItem.value();
			switch (errorCode)
			{
				case LexerErrorCode::INTEGER :
				{
					res.integetNumber = atoi(res.identifier.c_str());
					res.identifier.clear();
					break;
				}
				case LexerErrorCode::DOUBLE :
				{
					res.floatNumber = strtod(res.identifier.c_str(), 0);
					res.identifier.clear();
					break;
				}
				case LexerErrorCode::IDENTIFIER :
				{
					break;
				}
			}
		}
		return res;
	};


	{
		FCLexer lexer{"abc"};
		assert(lexer.generateNextTok() == LexerErrorCode::IDENTIFIER);
		assert(func1(lexer.getTok(), LexerErrorCode::IDENTIFIER).identifier == "abc");
	}

	{
		FCLexer lexer{"abc "};
		assert(lexer.generateNextTok() == LexerErrorCode::INVALID);
	}

	{
		FCLexer lexer{"abc1"};
		assert(lexer.generateNextTok() == LexerErrorCode::IDENTIFIER);
		assert(func1(lexer.getTok(), LexerErrorCode::IDENTIFIER).identifier == "abc1");
	}

	{
		FCLexer lexer{"abc1."};
		assert(lexer.generateNextTok() == LexerErrorCode::INVALID);
	}

	{
		FCLexer lexer{"1"};
		assert(lexer.generateNextTok() == LexerErrorCode::INTEGER);
		assert(func1(lexer.getTok(), LexerErrorCode::INTEGER).integetNumber == 1);
	}

	{
		FCLexer lexer{"1."};
		assert(lexer.generateNextTok() == LexerErrorCode::DOUBLE);
		assert(abs(func1(lexer.getTok(), LexerErrorCode::DOUBLE).floatNumber - 1) <= 1e-5);
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
		FCLexer lexer{"1 "};
		assert(lexer.generateNextTok() == LexerErrorCode::INVALID);
	}

	{
		FCLexer lexer{"1. "};
		assert(lexer.generateNextTok() == LexerErrorCode::INVALID);
	}

	return 0;
}