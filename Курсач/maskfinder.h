#define _CRT_SECURE_NO_WARNINGS
#ifndef MASK_FINDER_INCLUDED
#define MASK_FINDER_INCLUDED
#include <stdio.h>
#include <wchar.h>
#include <wctype.h>
#include <string.h>
#include "texttools.h"


int find_best_pos(wchar_t** first_ptr, wchar_t** second_ptr);

wchar_t* find_mask(wchar_t** first_ptr, wchar_t** second_ptr);

void print_sentence_mask(Sentence* sentence);

void print_text_masks(Text* text);
#endif