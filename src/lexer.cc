#include "lexer.h"

FCLexer::FCLexer(const ::std::string& input):m_inputSrc(input)
{
	m_curTok=' ';
	m_currentIdx = m_inputSrc.cbegin();
	m_inputEnd = m_inputSrc.cend();
} 

LexerErrorCode FCLexer::generateNextTok()
{
	//处理由空白符分割的字符串，生成第一个字符串序列对应的语素

	//跳过空白符
	while (inputRemain() && isspace(*m_currentIdx))
		m_currentIdx++;
	
	//处理标识符
	//合法标识符应以字母开头
	if(inputRemain() && isalpha(*m_currentIdx))
	{
		m_curTok = *m_currentIdx++;
		//标识符由字母和数字组成
		while (inputRemain() && isalnum(*m_currentIdx))
		{
			m_curTok += *m_currentIdx++;
		}

		return LexerErrorCode::IDENTIFIER;
	}

	return LexerErrorCode::INVALID;
}

FCLexer::item_type FCLexer::getTok()
{
	return m_curTok;
}