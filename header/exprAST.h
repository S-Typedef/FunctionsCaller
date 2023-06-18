#include <vector>

struct ExprAST
{
public:
	virtual ~ExprAST() = default;
};

struct IntegerExprAST : public ExprAST
{
private:
	int num;
public:
	IntegerExprAST(const int& id):num(id){}
	~IntegerExprAST() = default;
};

struct FloatExprAST : public ExprAST
{
private:
	double f;
public:
	FloatExprAST(const double& id):f(id){}
	~FloatExprAST() = default;
};

struct StringExprAST : public ExprAST
{
private:
	std::string m_data;
public:
	StringExprAST(const std::string& str):m_data(str){}
	~StringExprAST() = default;
};

struct VariableExprAST : public ExprAST
{
private:
	std::string m_name;
public:
	VariableExprAST(const std::string& id):m_name(id){}

};

struct PrototypeExprAST : public ExprAST
{

};

struct FunctionExprAST : public ExprAST
{

};

struct BinaryExprAST : public ExprAST
{
private:
	char m_Op;
	std::unique_ptr<ExprAST> mup_LHS, mup_RHS;
public:
	BinaryExprAST(char op,
		std::unique_ptr<ExprAST> lhs,
		std::unique_ptr<ExprAST> rhs):m_Op(op),mup_LHS(std::move(lhs)),mup_RHS(std::move(rhs)){}
	~BinaryExprAST()=default;
};

struct CallExprAST : public ExprAST
{
private:
	std::string m_callee;
	std::vector<std::unique_ptr<ExprAST>> m_args;
public:
	CallExprAST(const std::string& callee,
		std::vector<std::unique_ptr<ExprAST>> args): m_callee(std::move(callee)), m_args(std::move(args)){}
	~CallExprAST() = default;
};