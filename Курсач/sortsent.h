#define _CRT_SECURE_NO_WARNINGS
#ifndef SORT_SENT_INCLUDED
#define SORT_SENT_INCLUDED
#include <stdlib.h>
#include <stdio.h>
#include <wchar.h>
#include <wctype.h>
#include <string.h>
#include "texttools.h"


extern const wchar_t vovels[];

int iswvovel(wchar_t symbol);

int vovelcount(void* str_v);

int cmp_words(void** first, void** second);

void sort_sentence(Sentence* sentence);

void sort_selected_sentence(Text* text, int ind);
#endif