#include "parser.h"
#include "exprAST.h"

#include <map>

std::unique_ptr<ExprAST> Parser::analyse(const std::string& source)
{
	m_lexer = FCLexer{source};
	switch (m_lexer.generateNextTok())
	{
		case LexerErrorCode::FUNCDEF :
			break;
		case LexerErrorCode::COMMENT :
			break;
		default :
			parseFullExpr();
			break;
	}
	
	return nullptr;
}

std::unique_ptr<ExprAST> Parser::parseFullExpr()
{
	if (auto E = parseExpression())
	{
		return nullptr;
		// //有名函数亦被封装为匿名函数调用
		// auto Proto = std::make_unique<KPrototypeAST>("__anon_expr",
		// 	std::vector<KVariableExprAST>());
		// return std::make_unique<KFunctionAST>(std::move(Proto), std::move(E));
	}
	return nullptr;
}

std::unique_ptr<ExprAST> Parser::parseExpression()
{
	auto LHS = parsePrimaryExpr();
	if (!LHS)
		return nullptr;
	
	return parseBinOpRHSExpr(0, std::move(LHS));
}

std::unique_ptr<ExprAST> Parser::parsePrimaryExpr()
{
	switch (m_lastErrorCode)
	{
	default:
		break;
	case LexerErrorCode::IDENTIFIER :
		return parseIdentifierExpr();
	case LexerErrorCode::INTEGER :
		return parseIntegerExpr();
	case LexerErrorCode::DOUBLE :
		return parseFloatExpr();
	case LexerErrorCode::STRING :
		return parseStringExpr();
	case LexerErrorCode::LEFTBRACKET :
		return parseParenExpr();
	}
	return nullptr;
}

std::unique_ptr<ExprAST> Parser::parseBinOpRHSExpr(int ExprPrec, std::unique_ptr<ExprAST> LHS)
{
	while (true)
	{
		int TokPrec = getTokPrecedence();

		//优先级从低到高处理
		if (TokPrec < ExprPrec)
			return LHS;

		char Binop = m_curTok.op;
		getNextToken();

		//获取右操作数
		auto RHS = parsePrimaryExpr();
		if (!RHS)
			return nullptr;
		int NextPrec = getTokPrecedence();
		//当前操作符优先级低于下一个，构建子树
		if (TokPrec < NextPrec)
		{
			RHS = parseBinOpRHSExpr(TokPrec + 1, ::std::move(RHS));
			if (!RHS)
				return nullptr;
		}

		//合并子树
		LHS = ::std::make_unique<BinaryExprAST>(Binop,
			::std::move(LHS),
			::std::move(RHS));
	}
}

std::unique_ptr<ExprAST> Parser::parseIdentifierExpr()
{
	std::string id = m_curTok.identifier;

	getNextToken();
	if (LexerErrorCode::INVALID == m_lastErrorCode)
		return nullptr;

	//进行函数调用
	if (LexerErrorCode::LEFTBRACKET == m_lastErrorCode)
	{
		std::vector<std::unique_ptr<ExprAST>> args;
		//解析参数
		while (true)
		{
			getNextToken();
			if (LexerErrorCode::INVALID == m_lastErrorCode)
				return nullptr;
			if (LexerErrorCode::RIGHTBRACKET == m_lastErrorCode && args.size() == 0)
				return nullptr;
			if (LexerErrorCode::COMMA == m_lastErrorCode && args.size() != 0)
				continue;
			if (auto arg = parseExpression())
				args.emplace_back(std::move(arg));
		}
		getNextToken();
		if (LexerErrorCode::INVALID == m_lastErrorCode)
			return nullptr;
		return std::make_unique<CallExprAST>(id, std::move(args));
	}
	else
	{
		//变量标识符
		return std::make_unique<VariableExprAST>(id);
	}
	return nullptr;
}

std::unique_ptr<ExprAST> Parser::parseStringExpr()
{
	return std::make_unique<IntegerExprAST>(m_lexer.getTok().value().integetNumber);
}

std::unique_ptr<ExprAST> Parser::parseParenExpr()
{
	return std::make_unique<IntegerExprAST>(m_lexer.getTok().value().integetNumber);
}

std::unique_ptr<ExprAST> Parser::parseIntegerExpr()
{
	return std::make_unique<IntegerExprAST>(m_lexer.getTok().value().integetNumber);
}

std::unique_ptr<ExprAST> Parser::parseFloatExpr()
{
	return std::make_unique<FloatExprAST>(m_lexer.getTok().value().floatNumber);
}

void Parser::getNextToken()
{
	m_lastErrorCode = m_lexer.generateNextTok();
	if (LexerErrorCode::INVALID != m_lastErrorCode)
		m_curTok = m_lexer.getTok().value();
}

int Parser::getTokPrecedence()
{
	static ::std::map<char, int> binopPrecedence =
	{
		{'+',10},
		{'-',10},
		{'*',20},
		{'/',20}
	};
	if (m_lastErrorCode == LexerErrorCode::INVALID || binopPrecedence.cend() != binopPrecedence.find(m_curTok.op))
		return -1;

	//是否为二元操作
	int TokPrec = binopPrecedence[m_curTok.op];
	if (TokPrec <= 0)
		return -1;
	return TokPrec;
}