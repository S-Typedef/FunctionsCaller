#include <cstdlib>

#include "lexer.h"

FCLexer::FCLexer(const ::std::string& input):m_inputSrc(input)
{
	m_curTok = ' ';
	m_resTok.identifier = "";
	m_currentIdx = m_inputSrc.cbegin();
	m_inputEnd = m_inputSrc.cend();
} 

bool FCLexer::readInput()
{
	auto hasTok = m_currentIdx != m_inputEnd;
	if(hasTok)
		m_curTok = *m_currentIdx++;
	
	return hasTok;
}


LexerErrorCode FCLexer::generateNextTok()
{
	//处理由空白符分割的字符串，生成第一个字符串序列对应的语素

	//跳过空白符
	while(readInput() && isspace(m_curTok));
	
	//处理标识符
	//合法标识符应以字母开头
	if(isalpha(m_curTok))
	{
		m_resTok.identifier = m_curTok;
		//标识符由字母和数字组成
		while (readInput() && isalnum(m_curTok))
			m_resTok.identifier += m_curTok;
		return LexerErrorCode::IDENTIFIER;
	}

	//数字字面量
	//整数或者浮点数
	auto flagFloat = false;
	if((isdigit(m_curTok) || m_curTok == '.'))
	{
		do
		{
			m_resTok.identifier += m_curTok;
			if(m_curTok == '.')
				flagFloat = true;
			
		} while (readInput() && (isdigit(m_curTok) || m_curTok == '.'));
		if(flagFloat)
			return LexerErrorCode::DOUBLE;
		return LexerErrorCode::INTEGER;
	}
	return LexerErrorCode::INVALID;
}

::std::optional<FCLexer::item_type> FCLexer::getTok()
{
	switch(lastGenerateResult)
	{
		case LexerErrorCode::KEYWORD :
		{
			return ::std::nullopt;
		}
			break;
		case LexerErrorCode::LITERAL :
		{
			return ::std::nullopt;
		}
			break;
		case LexerErrorCode::DIGIT :
		{
			return ::std::nullopt;
		}
			break;
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
		case LexerErrorCode::INVALID :
		{
			return ::std::nullopt;
		}
			break;
		default:
			return ::std::nullopt;
	}
	return ::std::nullopt;
}