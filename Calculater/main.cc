#include "calculater.h"
#include <QApplication>
#include "scanner.h"
#include "preimpifunc.h"

nfunc_table_type* funcManager;
sfunc_table_type* specailFunc;
var_table_type* varTableInFunc;

int main(int argc, char* argv[])
{
	QApplication* app = new QApplication(argc, argv);

	funcManager = new nfunc_table_type;
	specailFunc = new sfunc_table_type;
	varTableInFunc = new var_table_type;

	funcManager->registerFunc("sum", testSum);
	funcManager->registerFunc("avg", testAverage);
	funcManager->registerFunc("power", testPower);

	FCCalculater c(funcManager);
	c.show();

	app->exec();
	return 0;
}