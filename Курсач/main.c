#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <wchar.h>
#include <wctype.h>
#include <string.h>
#include <locale.h>
#include "texttools.h"

#define BUFF_STR 100
#define BUFF_ELEM 10
#define LOCALE "ru-RU.cp1251"



int main()
{
	setlocale(LC_CTYPE, LOCALE);
	Text* data = malloc(sizeof(Text));
	init_Text(data);
	read_Text(data);
	print_Text(data);
	for (int i = 0; i < data->length; i++)
	{
		for (int j = 0; j < data->sentences[i]->length; j++)
		{
			if (!wcscmp(data->sentences[i]->words[j], L"ass"))
			{
				remove_Sentence(data, i);
				i--;
				break;
			}
		}
	}
	print_Text(data);
	free_Text(data);
}