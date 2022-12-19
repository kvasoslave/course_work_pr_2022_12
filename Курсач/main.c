#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <wchar.h>
#include <wctype.h>
#include <string.h>
#include <locale.h>

#define BUFF_STR 100
#define BUFF_ELEM 10
#define LOCALE "ru-RU.cp1251"

typedef struct _Sentence
{
	wchar_t** words;
	unsigned length;
} Sentence;

typedef struct
{
	Sentence** sentences;
	unsigned length;
} Text;

void init_Text(Text* text)
{
	text->sentences = NULL;
	text->length = 0;
}

void init_Sentence(Sentence* sentence, wchar_t* str)
{
	sentence->words = NULL;
	sentence->length = 0;
	wchar_t* word;
	wchar_t* wcstok_ptr;
	word = wcstok(str, L", ", &wcstok_ptr);
	while (word != NULL)
	{
		if (!(sentence->length % 5))
		{
			sentence->words = realloc(sentence->words, sizeof(wchar_t*) * (sentence->length + BUFF_ELEM));
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
	sentence = wcstok(buffer, L".\n", &wcstok_ptr);
	while (sentence != NULL)
	{
		Sentence* newsentence = malloc(sizeof(Sentence));
		init_Sentence(newsentence, sentence);
		if (!(text->length % 5))
		{
			text->sentences = realloc(text->sentences, sizeof(Sentence*) * (BUFF_ELEM + text->length));
		}
		*(text->sentences + text->length) = newsentence;
		text->length++;
		sentence = wcstok(NULL, L".\n", &wcstok_ptr);
	}
	free(buffer);
}

void print_Text(Text* text)
{
	Sentence* current = NULL;
	for (int i = 0; i < text->length; i++)
	{
		current = text->sentences[i];
		for (int i = 0; i < current->length - 1; i++)
		{
			printf("%ls ", *(current->words + i));
		}
		printf("%ls.\n", *(current->words + current->length - 1));
	}
}

void free_Sentence(Sentence* sentence)
{
	for (int i = 0; i < sentence->length; i++)
	{
		free(sentence->words[i]);
	}
	free(sentence->words);
	free(sentence);
}

void remove_Sentence(Text* text, int index)
{
	free_Sentence(text->sentences[index]);
	memmove(text->sentences + index, text->sentences + index + 1, sizeof(Sentence*) * (text->length - index - 1));
	text->length--;
}

void free_Text(Text* text)
{
	for (int i = 0; i < text->length; i++)
	{
		free_Sentence(text->sentences[i]);
	}
	free(text->sentences);
	free(text);
}

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