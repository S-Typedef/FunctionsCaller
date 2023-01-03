#ifndef LEXER_H
#define LEXER_H

#include<string>

#include "lexerErrorInfo.h"

class FCExprAST;

//词法分析器
//读取输入字符串生成语法要素
class FCLexer
{
	using item_type = ::std::string;
	using iterator = ::std::string::const_iterator;

public:
	FCLexer(const ::std::string&);
	LexerErrorCode generateNextTok();
	item_type getTok();

private:
	bool inputRemain(){return m_currentIdx != m_inputEnd;}

private:
	item_type m_curTok;
	iterator m_currentIdx;
	::std::string m_inputSrc;
	iterator m_inputEnd;
};

#endif