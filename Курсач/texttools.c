#include "texttools.h"

//non-gcc only

int wcscasecmp(const wchar_t* s1, const wchar_t* s2)
{
	wchar_t c1, c2;

	if (s1 == s2)
		return 0;

	do
	{
		c1 = towlower(*s1++);
		c2 = towlower(*s2++);
		if (c1 == L'\0')
			break;
	} while (c1 == c2);

	return c1 - c2;
}

//remove the above function when using gcc

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
	wchar_t** uniques = NULL;
	char isunique;
	sentence = wcstok(buffer, L".\n", &wcstok_ptr);
	int sentence_len;
	while (sentence != NULL)
	{
		isunique = 1;
		while (iswspace(*sentence))
			sentence++;
		sentence_len = wcslen(sentence);
		for (int i = 0; i < text->length; i++)
		{
			if (!wcscasecmp(uniques[i], sentence))
			{
				isunique = 0;
				break;
			}
		}
		if (isunique)
		{
			Sentence* newsentence = malloc(sizeof(Sentence));
			if (init_Sentence(newsentence, sentence))
			{
				if (!(text->length % 5))
				{
					uniques = realloc(uniques, sizeof(Sentence*) * (BUFF_ELEM + text->length));
					text->sentences = realloc(text->sentences, sizeof(Sentence*) * (BUFF_ELEM + text->length));
				}
				text->sentences[text->length] = newsentence;
				for (int i = 0; i < sentence_len; i++)
				{
					if (!sentence[i])
						sentence[i] = L' ';
				}
				uniques[text->length] = calloc(sentence_len + 1, sizeof(wchar_t*));
				memcpy(uniques[text->length], sentence, sentence_len * sizeof(wchar_t));
				text->length++;
			}
		}
		sentence = wcstok(NULL, L".\n", &wcstok_ptr);
	}
	for (int i = 0; i < text->length; i++)
	{
		free(uniques[i]);
	}
	free(uniques);
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
