#include <vector>
#include <iostream>

struct ExprAST
{
public:
	virtual ~ExprAST() = default;
	virtual void showInfo() = 0;
};

struct IntegerExprAST : public ExprAST
{
private:
	int num;
public:
	IntegerExprAST(const int& id):num(id){showInfo();}
	~IntegerExprAST() = default;
	void showInfo() override
	{
		std::cout<<this->num<<std::endl;
	}
};

struct FloatExprAST : public ExprAST
{
private:
	double f;
public:
	FloatExprAST(const double& id):f(id){showInfo();}
	~FloatExprAST() = default;
	void showInfo() override
	{
		std::cout<<this->f<<std::endl;
	}
};

struct StringExprAST : public ExprAST
{
private:
	std::string m_data;
public:
	StringExprAST(const std::string& str):m_data(str){showInfo();}
	~StringExprAST() = default;
	void showInfo() override
	{
		std::cout<<this->m_data<<std::endl;
	}
};

struct VariableExprAST : public ExprAST
{
private:
	std::string m_name;
public:
	VariableExprAST(const std::string& id):m_name(id){showInfo();}
	void showInfo() override
	{
		std::cout<<this->m_name<<std::endl;
	}
};

struct PrototypeExprAST : public ExprAST
{
	void showInfo() override
	{
	}
};

struct FunctionExprAST : public ExprAST
{
	void showInfo() override
	{
	}
};

struct BinaryExprAST : public ExprAST
{
private:
	char m_Op;
	std::unique_ptr<ExprAST> mup_LHS, mup_RHS;
public:
	BinaryExprAST(char op,
		std::unique_ptr<ExprAST> lhs,
		std::unique_ptr<ExprAST> rhs):m_Op(op),mup_LHS(std::move(lhs)),mup_RHS(std::move(rhs)){showInfo();}
	~BinaryExprAST()=default;
	void showInfo() override
	{
		std::cout<<"m_Op: "<<this->m_Op<<std::endl;
		std::cout<<"mup_LHS: "<<this->mup_LHS<<std::endl;
		std::cout<<"mup_RHS: "<<this->mup_RHS<<std::endl;
	}
};

struct CallExprAST : public ExprAST
{
private:
	std::string m_callee;
	std::vector<std::unique_ptr<ExprAST>> m_args;
public:
	CallExprAST(const std::string& callee,
		std::vector<std::unique_ptr<ExprAST>> args): m_callee(std::move(callee)), m_args(std::move(args)){showInfo();}
	~CallExprAST() = default;
	void showInfo() override
	{
		std::cout<<"m_callee: "<<this->m_callee<<std::endl;
		for (const auto& item : m_args)
			std::cout<<"item: "<<item<<std::endl;
	}
};