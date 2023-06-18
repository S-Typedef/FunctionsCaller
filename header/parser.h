#ifndef PARSER_H
#define PARSER_H

#include <memory>
#include <utility>

#include "lexer.h"

struct ExprAST;

class Parser
{
public:

	Parser()=default;

	std::unique_ptr<ExprAST> analyse(const std::string&);

	std::unique_ptr<ExprAST> parseIdentifierExpr();
	std::unique_ptr<ExprAST> parseIntegerExpr();
	std::unique_ptr<ExprAST> parseFloatExpr();
	std::unique_ptr<ExprAST> parseStringExpr();
	std::unique_ptr<ExprAST> parseParenExpr();
	std::unique_ptr<ExprAST> parseBinOpRHSExpr(int ExprPrec, std::unique_ptr<ExprAST> LHS);

	
	std::unique_ptr<ExprAST> parseFullExpr();
	std::unique_ptr<ExprAST> parsePrimaryExpr();
	std::unique_ptr<ExprAST> parseExpression();
	void setLexer(const FCLexer oth)
	{
		m_lexer = oth;
	}
	void Parser::getNextToken();
	int Parser::getTokPrecedence();

private:
	LexerErrorCode m_lastErrorCode;
	FCLexer::item_type m_curTok;
	FCLexer m_lexer;
};

#endif