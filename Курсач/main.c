#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <wchar.h>
#include <wctype.h>
#include <string.h>
#include <locale.h>

#define BUFF_STR 100
#define BUFF_WORD 10
#define LOCALE "ru-RU.cp1251"

typedef struct _Sentence
{
	struct _Sentence* prev;
	struct _Sentence* next;
	wchar_t** words;
	unsigned length;
} Sentence;

typedef struct 
{
	Sentence* head;
	Sentence* tail;
	unsigned length;
} Text;

void init_Text(Text* text)
{
	text->head = NULL;
	text->tail = NULL;
	text->length = 0;
}

void init_Sentence(Sentence* sentence, wchar_t* str)
{
	sentence->next = NULL;
	sentence->prev = NULL;
	sentence->words = NULL;
	sentence->length = 0;
	wchar_t* word;
	wchar_t* wcstok_ptr;
	word = wcstok(str, L", ", &wcstok_ptr);
	while (word != NULL)
	{
		if (!(sentence->length % 5))
		{
			sentence->words = realloc(sentence->words, sizeof(wchar_t*) * (sentence->length + BUFF_WORD));
		}
		sentence->words[sentence->length] = malloc(sizeof(wchar_t) * (wcslen(word) + 1));
		wcscpy(sentence->words[sentence->length], word);
		sentence->length++;
		word = wcstok(NULL, L", ", &wcstok_ptr);
	}
}

void read_Text(Text* text)
{
	wchar_t* buffer = calloc(1, sizeof(wchar_t));
	unsigned buffer_size = BUFF_STR;
	do
	{
		buffer = realloc(buffer, sizeof(wchar_t) * (buffer_size));
		buffer_size += BUFF_STR;
		fgetws(buffer + wcslen(buffer), BUFF_STR, stdin);
	} while (*(buffer + wcslen(buffer) - 1) != '\n');
	wchar_t* sentence;
	wchar_t* wcstok_ptr;
	sentence = wcstok(buffer, L".", &wcstok_ptr);
	while (sentence != NULL)
	{
		Sentence* newsentence = malloc(sizeof(Sentence));
		init_Sentence(newsentence, sentence);
		if (text->head != NULL)
		{
			text->tail->next = newsentence;
			newsentence->prev = text->tail;
			
		}
		else
		{
			text->head = newsentence;
		}
		text->tail = newsentence;
		sentence = wcstok(NULL, L".", &wcstok_ptr);
	} 
	free(buffer);
}

void print_Text(Text* text)
{
	Sentence* current = text->head;
	while (current != NULL)
	{
		for (int i = 0; i < current->length - 1; i++)
		{
			printf("%ls ", *(current->words + i));
		}
		printf("%ls\n", *(current->words + current->length - 1));
		current = current->next;
	}
}

int main()
{
	setlocale(LC_CTYPE, LOCALE);
	Text data;
	init_Text(&data);
	read_Text(&data);
	print_Text(&data);
}