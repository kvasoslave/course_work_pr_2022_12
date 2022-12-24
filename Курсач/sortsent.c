#include "sortsent.h"

const wchar_t vovels[] = L"aAeEiIoOuUyYàÀèÈåÅ¸¨îÎóÓûÛıİşŞÿß";

int iswvovel(wchar_t symbol)
{
	for (int i = 0; i < 32; i++)
	{
		if (symbol == vovels[i])
			return 1;
	}
	return 0;
}

int vovelcount(void* str_v)
{
	wchar_t* str = (wchar_t*)str_v;
	int count = 0;
	for (int i = 0; i < wcslen(str); i++)
	{
		if (iswvovel(str[i]))
			count++;
	}
	return count;
}

int cmp_words(const void* first, const void* second)
{
	
	int first_c = vovelcount(*(void**)first), second_c = vovelcount(*(void**)second);
	if (first_c == second_c)
		return 0;
	else if (first_c > second_c)
		return 1;
	else
		return -1;
}

void sort_sentence(Sentence* sentence)
{
	qsort(sentence->words, sentence->length, sizeof(wchar_t*), cmp_words);
}

void sort_selected_sentence(Text* text, int ind)
{
	if (ind < 0 || ind >= text->length)
		fputws(L"Error: Text index out of range\n", stdout);
	else
	{
		sort_sentence(text->sentences[ind]);
	}
}
