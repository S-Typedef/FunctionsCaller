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
		do
		{
			if(!readInput())
				break;
			if(!isalnum(m_curTok))
				return m_lastGenerateResult = LexerErrorCode::INVALID;
			m_resTok.identifier += m_curTok;
			
		}while (true);

		if ("def" == m_resTok.identifier)
			return m_lastGenerateResult = LexerErrorCode::FUNCDEF;
		return m_lastGenerateResult = LexerErrorCode::IDENTIFIER;
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
			
			if (!readInput())
				break;
			if(isspace(m_curTok))
				break;
			if(!(isdigit(m_curTok) || m_curTok == '.'))
				return m_lastGenerateResult = LexerErrorCode::INVALID;
		} while (true);
		if(flagFloat)
			return m_lastGenerateResult = LexerErrorCode::DOUBLE;
		return m_lastGenerateResult = LexerErrorCode::INTEGER;
	}

	if ('"' == m_curTok)
	{
		if (!readInput())
			return m_lastGenerateResult = LexerErrorCode::INVALID;
		
		if ('"' == m_curTok)
		{
			m_resTok.identifier = "";
			return m_lastGenerateResult = LexerErrorCode::STRING;
		}
		m_resTok.identifier += m_curTok;
		do
		{
			if (!readInput())
				break;
			if ('"' == m_curTok)
				break;
			if (!isalpha(m_curTok))
				return m_lastGenerateResult = LexerErrorCode::INVALID;

			m_resTok.identifier += m_curTok;
		}while (true);
		
		return m_lastGenerateResult = LexerErrorCode::STRING;
	}

	if ('#' == m_curTok)
	{
		do
		{
			if (!readInput())
				break;
		}while(m_curTok != EOF && m_curTok != '\n' && m_curTok != '\r');
		return m_lastGenerateResult = LexerErrorCode::COMMENT;
	}

	if (m_curTok == EOF || !readInput())
	{
		m_curTok = ' ';
		return m_lastGenerateResult = LexerErrorCode::END;
	}
	if (m_curTok == '(')
	{
		m_resTok.identifier += m_curTok;
		return m_lastGenerateResult = LexerErrorCode::LEFTBRACKET;
	}
	if (m_curTok == ')')
	{
		m_resTok.identifier += m_curTok;
		return m_lastGenerateResult = LexerErrorCode::RIGHTBRACKET;
	}
	if (m_curTok == '+')
	{
		m_resTok.identifier += m_curTok;
		return m_lastGenerateResult = LexerErrorCode::OPERATOR;
	}
	if (m_curTok == '-')
	{
		m_resTok.identifier += m_curTok;
		return m_lastGenerateResult = LexerErrorCode::OPERATOR;
	}
	if (m_curTok == '*')
	{
		m_resTok.identifier += m_curTok;
		return m_lastGenerateResult = LexerErrorCode::OPERATOR;
	}
	if (m_curTok == '/')
	{
		m_resTok.identifier += m_curTok;
		return m_lastGenerateResult = LexerErrorCode::OPERATOR;
	}
	if (m_curTok == '%')
	{
		m_resTok.identifier += m_curTok;
		return m_lastGenerateResult = LexerErrorCode::OPERATOR;
	}
	if (m_curTok == ',')
	{
		m_resTok.identifier += m_curTok;
		return m_lastGenerateResult = LexerErrorCode::COMMA;
	}

	return m_lastGenerateResult = LexerErrorCode::INVALID;
}

::std::optional<FCLexer::item_type> FCLexer::getTok()
{
	switch(m_lastGenerateResult)
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
		case LexerErrorCode::FUNCDEF :
		{
			return m_resTok;
		}
		case LexerErrorCode::STRING :
		{
			return m_resTok;
		}
		case LexerErrorCode::COMMENT :
		{
			return m_resTok;
		}
		case LexerErrorCode::OPERATOR :
		{
			return m_resTok;
		}
		case LexerErrorCode::COMMA :
		{
			return m_resTok;
		}
		case LexerErrorCode::INVALID :
		{
			return ::std::nullopt;
		}
			break;
		default:
			return m_resTok;
	}
	return ::std::nullopt;
}