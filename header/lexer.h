﻿#ifndef LEXER_H
#define LEXER_H

#include<tuple>
#include<optional>
#include<string>

#include "lexerErrorInfo.h"

class FCExprAST;

//词法分析器
//读取输入字符串生成语法要素
class FCLexer
{
	using iterator = ::std::string::const_iterator;
	using tok_type = ::std::string::value_type;

public:
	struct item_type
	{
		int 			integetNumber = 0;
		double 			floatNumber = 0.;
		::std::string 	identifier;
		::std::string 	stringDate;
		char 			op;
	};

public:
	FCLexer()=default;
	FCLexer(const ::std::string&);
	FCLexer& operator=(const FCLexer& oth)
	{
		m_inputSrc = oth.m_inputSrc;
		m_currentIdx = m_inputSrc.cbegin();
		m_inputEnd = m_inputSrc.cend();
		return *this;
	}
	~FCLexer() = default;
	LexerErrorCode generateNextTok();
	::std::optional<item_type> getTok();

private:
	bool readInput();
private:
	LexerErrorCode m_lastGenerateResult;

	tok_type m_curTok;
	item_type m_resTok;
	iterator m_currentIdx;
	::std::string m_inputSrc;
	iterator m_inputEnd;
};

#endif