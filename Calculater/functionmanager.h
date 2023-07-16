#pragma once

#include <functional>
#include <set>
#include <string>
#include <map>
#include <memory>
#include <utility>
#include "token.h"

class FCMyFunctional {
	using func_type = ::std::function<
		FCMarks::FCValue(::std::vector<std::unique_ptr<FCExprClass::FCExprAST>>*)
	>;
public:

	FCMyFunctional();
	~FCMyFunctional();

	void registerFunc(::std::string, func_type);
	void deRegisterFunc(::std::string);

	::std::vector<::std::string> getRegistedFuncs();

	func_type getFuncByName(::std::string);

private:

	::std::map<::std::string, func_type> m_funcTable;

};

using sfunc_table_type = ::std::vector<FCExprClass::FCFunctionAST*>;
using nfunc_table_type = FCMyFunctional;
using var_table_type = ::std::map<::std::string,
	::std::map<::std::string,
	FCExprClass::FCVariableExprAST
	>
>;
extern sfunc_table_type* specailFunc;
extern nfunc_table_type* funcManager;
extern var_table_type* varTableInFunc;