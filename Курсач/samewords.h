#define _CRT_SECURE_NO_WARNINGS
#ifndef SAME_WORDS_INCLUDED
#define SAME_WORDS_INCLUDED
#include <stdlib.h>
#include <stdio.h>
#include <wchar.h>
#include <wctype.h>
#include <string.h>
#include "texttools.h"

int same_words_count(Sentence* sentence);

void print_same_words_count(Text* text);
#endif