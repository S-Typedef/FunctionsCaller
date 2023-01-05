#include <iostream>
#include <cassert>

#include "lexer.h"


int main()
{
	FCLexer lexer1{"abc"};
	FCLexer lexer2{"abc 1"};
	FCLexer lexer3{"1abc"};
	FCLexer lexer4{"abc1"};
	FCLexer lexer5{"1"};
	FCLexer lexer6{"1."};
	FCLexer lexer7{"1 a"};
	FCLexer lexer8{"1. a"};

	auto func1 = [](auto optionalItem){
		if(optionalItem)
		{
			switch (optionalItem.value())
			{
				case LexerErrorCode::INTEGER :
				{
					m_resTok.integetNumber = atoi(m_resTok.identifier.c_str());
					m_resTok.identifier.clear();
					return m_resTok;
				}
				case LexerErrorCode::DOUBLE :
				{
					m_resTok.floatNumber = strtod(m_resTok.identifier.c_str(), 0);
					m_resTok.identifier.clear();
					return m_resTok;
				}
				case LexerErrorCode::IDENTIFIER :
				{
					return m_resTok;
				}
			}
		}
	};

	assert(lexer1.generateNextTok() == LexerErrorCode::IDENTIFIER);

	assert(lexer2.generateNextTok() == LexerErrorCode::IDENTIFIER);

	assert(lexer3.generateNextTok() == LexerErrorCode::INVALID);

	assert(lexer4.generateNextTok() == LexerErrorCode::IDENTIFIER);

	assert(lexer5.generateNextTok() == LexerErrorCode::INTEGER);

	assert(lexer6.generateNextTok() == LexerErrorCode::DOUBLE);

	assert(lexer7.generateNextTok() == LexerErrorCode::INTEGER);

	assert(lexer8.generateNextTok() == LexerErrorCode::DOUBLE);

	return 0;
}