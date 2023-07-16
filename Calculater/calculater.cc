#include <QFileDialog>
#include <windows.h>
#include <QListWidgetItem>
#include <QLibrary>
#include <string>
#include <QDebug>


#include "calculater.h"

FCCalculater::FCCalculater(FCMyFunctional* f, QMainWindow* parent) :QMainWindow(parent), mp_funcInfo(f)
{
	mp_mw = new Ui::MainWindow;
	mp_mw->setupUi(this);
	mp_mw->m_resultLable->setText("Result");
	//只能输入中文符号
	mp_mw->m_expr->setAttribute(Qt::WA_InputMethodEnabled, false);

	//检测配置文件
	QFile configFile("config");
	if (configFile.exists() == true)
	{
		//读取dll路径
		readConfig(&configFile);
	}

	mp_scanner = new FCScanner(mp_funcInfo);

	updateFuncLits();

	connect(mp_mw->m_loadDll, &QPushButton::clicked, this, &FCCalculater::loadDllClicked);
	connect(mp_mw->m_registFunc, &QPushButton::clicked, this, &FCCalculater::regFunc);
	connect(mp_mw->m_executeExpr, &QPushButton::clicked, this, &FCCalculater::exeExpr);
}

void FCCalculater::readConfig(QFile* file)
{
	if (file->open(QIODevice::ReadOnly) == false)
	{
		return;
	}
	//获取dll路径
	QString pathInfo = file->readAll();
	//释放资源
	file->close();
	auto s = pathInfo.toStdString();
	//搜索dll
	findDll(&pathInfo);
}

int FCCalculater::findDll(QString* pathInfo)
{
	QDir path(*pathInfo);
	if (path.exists() == false)
		return -1;
	//过滤选项
	path.setFilter(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot);
	path.setSorting(QDir::DirsFirst);

	QFileInfoList list = path.entryInfoList();
	if (list.size() < 1)
		return -1;

	int i = 0;
	do
	{
		QFileInfo fileInfo = list.at(i);
		if (fileInfo.isDir())
		{
			//递归式遍历所有子文件夹
			auto newPath = fileInfo.filePath();
			findDll(&newPath);
		}
		else
		{
			//找到后缀为dll的文件
			if (fileInfo.suffix() == "dll")
				loadDll(fileInfo.absoluteFilePath());
		}
		i++;
	} while (i < list.size());
	return 0;
}

void FCCalculater::updateFuncLits()
{
	mp_mw->m_funcList->clear();
	auto func_list = funcManager->getRegistedFuncs();

	for (auto& i : func_list)
	{
		auto* tmp = new QListWidgetItem;
		tmp->setText(QString::fromStdString(i));
		mp_mw->m_funcList->addItem(tmp);
	}
}

void FCCalculater::loadDllClicked()
{
	typedef void(*f)(char*);
	typedef FCMarks::FCValue(*fun)(::std::vector<std::unique_ptr<FCExprClass::FCExprAST>>*);

	QString filename;
	filename = QFileDialog::getOpenFileName(this, QStringLiteral("Choose Dll"),
		"   ", tr("Dll (*.dll)"));
	if (filename == nullptr)
		return;
	loadDll(filename);
	qDebug() << filename;
}

//外部DLL注册的函数，普通注册
void FCCalculater::loadDll(QString dllPath)
{
	typedef void(*f)(void*);
	typedef FCMarks::FCValue(*fun)(::std::vector<std::unique_ptr<FCExprClass::FCExprAST>>*);

	//转换为宽字符集读取
	auto dllPathStdString = dllPath.toStdString();
	auto pRes = LoadLibrary(dllPathStdString.c_str());
	if (pRes == 0)
		return;
	//获取待注册函数名字
	f pDll = (f)GetProcAddress(pRes, "giveName");
	::std::vector<::std::string> allFuncsInDll;
	pDll((void*)&allFuncsInDll);

	//注册所有函数
	for (auto& i : allFuncsInDll)
	{
		fun regFunc = (fun)GetProcAddress(pRes, i.c_str());
		if (regFunc != nullptr)
			funcManager->registerFunc(i, *regFunc);
	}
	updateFuncLits();
}

//内部def注册的函数，特殊注册
void FCCalculater::regFunc()
{
	::std::string tmpStdString = mp_mw->m_expr->toPlainText().toStdString();
	if (tmpStdString.empty())//过滤
		return;

	auto analysisResult = mp_scanner->analysis(tmpStdString);
	if (analysisResult == nullptr)
	{
		mp_scanner->resetState();
		mp_mw->m_result->setText(QStringLiteral("Expression Error"));
		return;
	}
	//得到定义的函数对象
	auto funcRemainToReg = dynamic_cast<FCExprClass::FCFunctionAST*>(analysisResult.release());

	//空函数体，适配函数管理器
	auto callable = [](::std::vector<::std::unique_ptr<FCExprClass::FCExprAST>>* args)->FCMarks::FCValue {
		return {};
	};
	specailFunc->push_back(funcRemainToReg);
	funcManager->registerFunc(funcRemainToReg->getProtoName(), callable);

	updateFuncLits();
	mp_scanner->resetState();
	qDebug() << __func__;
}
void FCCalculater::exeExpr()
{
	mp_mw->m_result->clear();

	::std::string tmpStdString = mp_mw->m_expr->toPlainText().toStdString();
	if (tmpStdString.empty() || (*tmpStdString.rbegin()) != ';')
		return;//过滤

	auto analysisResult = mp_scanner->analysis(tmpStdString);
	//求值解析结果
	auto exeResult = resolveExprValue(::std::move(analysisResult));


	//整型、浮点型、字符串输出格式不同
	switch (exeResult.type)
	{
	case FCMarks::FCValueCategory::Integer:
		mp_mw->m_result->setText(QString::number(exeResult.evaluteVal.intVal));
		break;
	case FCMarks::FCValueCategory::Floating:
		mp_mw->m_result->setText(QString::number(exeResult.evaluteVal.doubleVal, 'f', 5));
		break;
	case FCMarks::FCValueCategory::String:
		mp_mw->m_result->setText(QString::fromStdString(exeResult.evaluteVal.charVal));
		break;
	case FCMarks::FCValueCategory::Dangle:
		mp_mw->m_result->setText(QStringLiteral("Expression Error"));
		break;
	}
	mp_scanner->resetState();
	qDebug() << __func__;
}

FCMarks::FCValue FCCalculater::resolveExprValue(::std::unique_ptr<FCExprClass::FCExprAST> expression)
{
	//解析出现错误
	if (expression == nullptr)
	{
		FCMarks::FCValue errorRes;
		errorRes.evaluteVal.danglingVal = nullptr;
		errorRes.type = FCMarks::FCValueCategory::Dangle;
		return errorRes;
	}
	return expression->evaluate();
}