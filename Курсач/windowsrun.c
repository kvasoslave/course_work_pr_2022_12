#include "windowsrun.h"


void set_environment()
{
	system("chcp 1251");
	system(CLEAR_SCREEN);
	setlocale(LC_CTYPE, LOCALE);
}
