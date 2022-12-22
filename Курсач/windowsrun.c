#include "windowsrun.h"


void set_environment()
{
	system("chcp 1251");
	system("cls");
	setlocale(LC_CTYPE, LOCALE);
}