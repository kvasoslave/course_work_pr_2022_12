#include "texttools.h"

void init_Text(Text* text)
{
	text->sentences = NULL;
	text->length = 0;
}

int init_Sentence(Sentence* sentence, wchar_t* str)
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
		sentence->words[sentence->length] = wcscpy(sentence->words[sentence->length], word);
		sentence->length++;
		word = wcstok(NULL, L", ", &wcstok_ptr);
	}
	return sentence->length;
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
	char isunique;
	sentence = wcstok(buffer, L".\n", &wcstok_ptr);
	while (sentence != NULL)
	{
		Sentence* newsentence = malloc(sizeof(Sentence));
		if (init_Sentence(newsentence, sentence))
		{
			isunique = 1;
			for (int i = 0; i < text->length; i++)
			{
				int samesent = 1;
				for (int j = 0; j < newsentence->length; j++)
				{
					if (wcscasecmp(text->sentences[i]->words[j], newsentence->words[j]))
					{
						samesent = 0;
						break;
					}
				}
				if (samesent)
				{
					isunique = 0;
					break;
				}
			}
			if (isunique || !text->length)
			{
				if (!(text->length % 5))
				{
					text->sentences = realloc(text->sentences, sizeof(Sentence*) * (BUFF_ELEM + text->length));
				}
				text->sentences[text->length] = newsentence;
				text->length++;
			}
			else
				free_Sentence(newsentence);	

		}
		sentence = wcstok(NULL, L".\n", &wcstok_ptr);
	}
	free(buffer);
}

void print_sentence(Sentence* sentence)
{
	for (int i = 0; i < sentence->length - 1; i++)
	{
		fputws(sentence->words[i], stdout);
		putwchar(L' ');
	}
	fputws(sentence->words[sentence->length - 1], stdout);
	putwchar(L'.');
	putwchar(L'\n');
}

void print_enum_Text(Text* text)
{
	Sentence* current = NULL;
	for (int i = 0; i < text->length; i++)
	{
		wprintf(L"%d: ", i);
		current = text->sentences[i];
		print_sentence(current);
	}
}

void print_Text(Text* text)
{
	Sentence* current = NULL;
	for (int i = 0; i < text->length; i++)
	{
		current = text->sentences[i];
		print_sentence(current);
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
