#include "samewords.h"

int same_words_count(Sentence* sentence)
{
	wchar_t** unique_words = malloc(sizeof(wchar_t*) * sentence->length);
	unsigned* unique_count = calloc(sentence->length, sizeof(unsigned));
	unsigned unique_words_length = 0;
	int result;
	char newword = 1;
	for (int i = 0; i < sentence->length; i++)
	{
		for (int j = 0; j < unique_words_length; j++)
		{
			if (!wcscmp(sentence->words[i], unique_words[j]))
			{
				unique_count[j]++;
				newword = 0;
				break;
			}
		}
		if (newword)
		{
			unique_words[unique_words_length] = sentence->words[i];
			unique_count[unique_words_length]++;
			unique_words_length++;
		}
		else
		{
			newword = 1;
		}
	}
	result = 0;
	for (int i = 0; i < unique_words_length; i++)
	{
		if (unique_count[i] > 1)
			result += unique_count[i];
	}
	free(unique_words);
	free(unique_count);
	return result;
}

void print_same_words_count(Text* text)
{
	for (int i = 0; i < text->length; i++)
	{
		wprintf(L"%d\n", same_words_count(text->sentences[i]));
	}
}