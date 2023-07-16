#include "preimpifunc.h"


FCMarks::FCValue testPower(::std::vector<std::unique_ptr<FCExprClass::FCExprAST>>* args)
{
	//返回值
	FCMarks::FCValue res;
	res.type = FCMarks::FCValueCategory::Dangle;
	res.evaluteVal.danglingVal = nullptr;
	//仅接受两个参数
	if (args->size() != 2)
	{
		fprintf(stderr, "Power just receive TWO args\n");
		return res;
	}
	auto a1 = (*args)[0]->evaluate();
	auto a2 = (*args)[1]->evaluate();

	//仅接受整型参数
	if (a1.type != FCMarks::FCValueCategory::Integer || a2.type != FCMarks::FCValueCategory::Integer)
	{
		return res;
	}

	res.type = FCMarks::FCValueCategory::Integer;
	int base = a1.evaluteVal.intVal;
	int exp = a2.evaluteVal.intVal;
	//若干特殊情况
		//底数为0
	if (base == 0)
	{
		res.evaluteVal.intVal = 0;
		return res;
	}
	//底数为1或者指数为0
	if (base == 1 || exp == 0)
	{
		res.evaluteVal.intVal = 1;
		return res;
	}

	//快速幂
	int ans = 1;
	while (exp)
	{
		if (exp & 1)
			ans *= base;
		base *= base;
		exp >>= 1;
	}

	res.evaluteVal.intVal = ans;
	return res;
}

FCMarks::FCValue testAverage(::std::vector<std::unique_ptr<FCExprClass::FCExprAST>>* args)
{
	FCMarks::FCValue res;
	res.type = FCMarks::FCValueCategory::Dangle;
	res.evaluteVal.danglingVal = nullptr;
	//记录所有浮点参数和
	double sumDoubleRes = 0.0;
	//记录所有整型参数和
	int sumIntRes = 0;

	auto& argVec = *args;
	for (size_t i = 0; i < argVec.size(); i++)
	{
		auto tmp = argVec[i]->evaluate();
		if (tmp.type == FCMarks::FCValueCategory::String || tmp.type == FCMarks::FCValueCategory::Dangle)
			return res;//非数字不求值
		//分别计算浮点数和、整型数和
		if (tmp.type == FCMarks::FCValueCategory::Floating)
		{
			sumDoubleRes += tmp.evaluteVal.doubleVal;
		}
		else {
			sumIntRes += tmp.evaluteVal.intVal;
		}
	}
	res.evaluteVal.doubleVal = (sumDoubleRes + sumIntRes) / args->size();
	res.type = FCMarks::FCValueCategory::Floating;
	return res;
}

FCMarks::FCValue testSum(::std::vector<std::unique_ptr<FCExprClass::FCExprAST>>* args)
{
	auto& argVec = *args;

	//判断参数是否全为数字或全为字符串
	bool numbersicFlag = false, stringFlag = false;
	//判断是否具有浮点值
	bool hasDouble = false;
	size_t numbersicCount = 0, stringCount = 0;

	//记录所有浮点参数和
	double sumDoubleRes = 0.0;
	//记录所有整型参数和
	int sumIntRes = 0;
	//记录所有字符串按参数顺序拼接值
	::std::string sumStringRes = "";

	FCMarks::FCValue res;
	res.evaluteVal.danglingVal = nullptr;
	res.type = FCMarks::FCValueCategory::Dangle;


	for (size_t i = 0; i < argVec.size(); i++)
	{
		if (stringCount != 0 && numbersicCount != 0)
		{//混合值，不计算
			return res;
		}
		auto tmp = argVec[i]->evaluate();
		switch (tmp.type)
		{
		case FCMarks::FCValueCategory::Floating:
		{
			hasDouble = true;
			sumDoubleRes += tmp.evaluteVal.doubleVal;
			numbersicCount++;
			break;
		}
		case FCMarks::FCValueCategory::Integer:
		{
			sumIntRes += tmp.evaluteVal.intVal;
			numbersicCount++;
			break;
		}
		case FCMarks::FCValueCategory::String:
		{
			sumStringRes.append(tmp.evaluteVal.charVal);
			stringCount++;
			break;
		}
		case FCMarks::FCValueCategory::Dangle:
		{
			return res;//非数字不求值
			break;
		}
		}
	}
	if (stringCount != 0)
	{
		res.type = FCMarks::FCValueCategory::String;
		memset(res.evaluteVal.charVal, 0, 1024);
		memcpy(res.evaluteVal.charVal, sumStringRes.c_str(), sumStringRes.size());
		return res;
	}
	if (hasDouble)
	{
		res.type = FCMarks::FCValueCategory::Floating;
		res.evaluteVal.doubleVal = sumDoubleRes + sumIntRes;
		return res;
	}
	res.type = FCMarks::FCValueCategory::Integer;
	res.evaluteVal.intVal = sumIntRes;
	return res;
}