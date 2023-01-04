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

	assert(static_cast<int>(lexer1.generateNextTok()) == 1);

	assert(static_cast<int>(lexer2.generateNextTok()) == 1);

	assert(static_cast<int>(lexer3.generateNextTok()) == 4);

	assert(static_cast<int>(lexer4.generateNextTok()) == 1);

	assert(static_cast<int>(lexer5.generateNextTok()) == 4);

	assert(static_cast<int>(lexer6.generateNextTok()) == 5);

	return 0;
}