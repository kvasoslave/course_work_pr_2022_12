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
#define LOCALE ".1251"

int check_for_capitals(Sentence* sentence)
{
	for (int i = 0; i < sentence->length; i++)
	{
		if (!iswupper(sentence->words[i][0]))
		{
			return 1;
		}
	}
	return 0;
}


void remove_uncapitalized_sentences(Text* text)
{
	for (int i = 0; i < text->length; i++)
	{
		if (check_for_capitals(text->sentences[i]))
		{
			remove_Sentence(text, i);
			i--;
		}
	}
}

int main()
{
	system("chcp 1251");
	setlocale(LC_CTYPE, LOCALE);
	Text* data = malloc(sizeof(Text));
	init_Text(data);
	read_Text(data);
	print_Text(data);
	remove_uncapitalized_sentences(data);
	puts("\\------------------------\\");
	print_Text(data);
	free_Text(data);
}