#include "functionmanager.h"


FCMyFunctional::FCMyFunctional()
{
	m_funcTable = {};
}

FCMyFunctional::~FCMyFunctional()
{

}

::std::vector<::std::string> FCMyFunctional::getRegistedFuncs()
{
	::std::vector<::std::string> res;
	for (auto& i : m_funcTable)
	{
		res.push_back(i.first);
	}
	return res;
}

void FCMyFunctional::registerFunc(::std::string name, func_type func)
{
	m_funcTable.insert({ name,func });
}
void FCMyFunctional::deRegisterFunc(::std::string name)
{

}

FCMyFunctional::func_type FCMyFunctional::getFuncByName(::std::string name)
{
	//仅用于查找普通函数
	if (m_funcTable.find(name) != m_funcTable.end())
		return m_funcTable.at(name);
	else
		return nullptr;
}