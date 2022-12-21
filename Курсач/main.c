#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <wchar.h>
#include <wctype.h>
#include <string.h>
#include <locale.h>
#include "texttools.h"
#include "remove_uncapitalized.h"

#define BUFF_STR 100
#define BUFF_ELEM 10
#define LOCALE ".1251"

int find_best_pos(wchar_t** first_ptr, wchar_t** second_ptr)
{
	int firstlen = wcslen(*first_ptr);
	int secondlen = wcslen(*second_ptr);
	*first_ptr = realloc(*first_ptr, sizeof(wchar_t) * (firstlen + 2 * (secondlen - 1) + 1));
	wchar_t* first = *first_ptr;
	wchar_t* second = *second_ptr;
	memmove(first + secondlen - 1, first, sizeof(wchar_t) * firstlen);
	wmemset(first, L' ', secondlen - 1);
	wmemset(first + firstlen + secondlen - 1, L' ', secondlen - 1);
	*(first + firstlen + 2 * (secondlen - 1)) = 0;
	int d, pos = 0, maxd = 0;
	for (int i = 0; i < firstlen + secondlen - 1; i++)
	{
		d = 0;
		for (int j = 0; j < secondlen; j++)
		{
			if (first[i + j] == second[j])
				d++;
		}
		if (d > maxd)
		{
			pos = i;
			maxd = d;
		}
	}
	memmove(first, first + secondlen - 1, sizeof(wchar_t) * firstlen);
	*first_ptr = realloc(*first_ptr, sizeof(wchar_t) * (firstlen + 1));
	*(*first_ptr + firstlen) = 0;
	return pos - secondlen + 1;
}

wchar_t* find_mask(wchar_t** first_ptr, wchar_t** second_ptr)
{
	char begins_with_asterisk = (*first_ptr)[0] == L'*', ends_with_asterisk = L'*' == (*first_ptr)[wcslen(*first_ptr) - 1];
	if (begins_with_asterisk)
		memmove(*first_ptr, *first_ptr + 1, sizeof(wchar_t) * wcslen(*first_ptr));
	if (ends_with_asterisk)
		(*first_ptr)[wcslen(*first_ptr) - 1] = 0;
	int cpos = 0, pos = find_best_pos(first_ptr, second_ptr);
	wchar_t* first = *first_ptr;
	wchar_t* second = *second_ptr;
	wchar_t* mask = malloc(sizeof(wchar_t) * (max(wcslen(first), wcslen(second)) + 2));
	wchar_t* second_cut;
	if (pos < 0)
	{
		second_cut = second - pos;
		pos = 0;
		mask[0] = L'*';
		cpos++;
	}
	else
	{
		second_cut = second;
		if (pos)
		{
			mask[0] = L'*';
			cpos++;
		}
		else if (begins_with_asterisk)
		{
			mask[0] = L'*';
			cpos++;
		}
	}
	for (int i = 0; i < min(wcslen(first) - pos, wcslen(second_cut)); i++)
	{
		if (first[pos + i] == second_cut[i])
		{
			mask[cpos] = second_cut[i];
			cpos++;
		}
		else
		{
			mask[cpos] = L'?';
			cpos++;
		}
	}
	if (wcslen(first) != wcslen(second_cut) + pos || ends_with_asterisk)
	{
		mask[cpos] = L'*';
		cpos++;
	}
	mask[cpos] = 0;
	return mask;
}

void print_sentence_mask(Sentence* sentence)
{
	if (sentence->length == 1)
		printf(sentence->words[0]);
	else if (sentence->length == 2)
	{
		wchar_t* mask = find_mask(&sentence->words[0], &sentence->words[1]);
		printf("%ls\n", mask);
		free(mask);
	}
	else
	{
		wchar_t* mask = NULL;
		wchar_t* oldmask = find_mask(&sentence->words[0], &sentence->words[1]);
		for (int i = 2; i < sentence->length; i++)
		{
			mask = find_mask(&oldmask, &sentence->words[i]);
			free(oldmask);
			oldmask = mask;
		}
		printf("%ls\n", mask);
		free(mask);
		printf("hello");
	}
}

void print_text_masks(Text* text)
{
	for (int i = 0; i < text->length; i++)
	{
		print_sentence_mask(text->sentences[i]);
	}
}


int main()
{
	setlocale(LC_CTYPE, LOCALE);
	Text* data = malloc(sizeof(Text));
	init_Text(data);
	read_Text(data);
	print_Text(data);
	print_text_masks(data);
	print_Text(data);
	free_Text(data);
}