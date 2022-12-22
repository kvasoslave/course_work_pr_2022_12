#define _CRT_SECURE_NO_WARNINGS
#ifndef TEXT_TOOLS_INCLUDED
#define TEXT_TOOLS_INCLUDED
#include <stdlib.h>
#include <stdio.h>
#include <wchar.h>
#include <wctype.h>
#include <string.h>


#define BUFF_STR 100
#define BUFF_ELEM 10

typedef struct _Sentence
{
	wchar_t** words;
	unsigned length;
} Sentence;

typedef struct _Text
{
	Sentence** sentences;
	unsigned length;
} Text;

void init_Text(Text* text);

int init_Sentence(Sentence* sentence, wchar_t* str);

void read_Text(Text* text);

void print_sentence(Sentence* sentence);

void print_Text(Text* text);

void print_enum_Text(Text* text);

void free_Sentence(Sentence* sentence);

void remove_Sentence(Text* text, int index);

void free_Text(Text* text);
#endif