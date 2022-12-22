#define _CRT_SECURE_NO_WARNINGS
#ifndef REM_UNCAP_INCLUDED
#define REM_UNCAP_INCLUDED
#include <wchar.h>
#include <wctype.h>
#include "texttools.h"


int check_for_capitals(Sentence* sentence);

void remove_uncapitalized_sentences(Text* text);

#endif