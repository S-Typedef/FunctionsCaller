#pragma once

#include<memory>
#include<string>
#include<vector>
#include<tuple>

#include "lexerErrorInfo.h"

class FCExprAST;

//词法分析器
//读取输入字符串生成语法要素
class FCLexer
{
	using item_type = ::std::string::value_type;
	using iterator = ::std::string::const_iterator;

public:
	FCLexer(const ::std::string&);
	LexerErrorCode generateNextTok();
private:
	item_type m_curTok;
	iterator m_currentIdx;
	::std::string m_inputSrc;
};