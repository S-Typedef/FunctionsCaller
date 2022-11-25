#include "lexer.h"



FCLexer::FCLexer(const ::std::string& input):m_inputSrc(input)
{
	m_curTok=' ';
	m_currentIdentifier = "";
	m_currentIdx = m_inputSrc.cbegin();
}

FCLexer::result_value& FCLexer::getResult()
{
	return m_tokens;
}

LexerErrorCode FCLexer::getNextTok(token_value&)
{
	while (isspace(*m_currentIdx++));
	if(isalpha(*m_currentIdx))
	{
		
	}
}

LexerErrorCode FCLexer::getLastTok(token_value&)
{

}