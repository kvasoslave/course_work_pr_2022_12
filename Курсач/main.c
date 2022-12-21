#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <wchar.h>
#include <wctype.h>
#include <string.h>
#include <locale.h>
#include "texttools.h"
#include "remove_uncapitalized.h"
#include "maskfinder.h"
#include "sort_sent.h"

#define BUFF_STR 100
#define BUFF_ELEM 10
#define LOCALE ".1251"

int main()
{
	system("chcp 1251");
	setlocale(LC_CTYPE, LOCALE);
	Text* data = malloc(sizeof(Text));
	init_Text(data);
	read_Text(data);
	print_Text(data);
	sort_selected_sentence(data, 0);
	print_Text(data);
	free_Text(data);
}