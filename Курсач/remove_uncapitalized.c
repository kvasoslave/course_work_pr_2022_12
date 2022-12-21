#include "remove_uncapitalized.h"

int check_for_capitals(Sentence* sentence)
{
	for (int i = 0; i < sentence->length; i++)
	{
		if (!iswupper(sentence->words[i][0]))
		{
			return 1;
		}
	}
	return 0;
}


void remove_uncapitalized_sentences(Text* text)
{
	for (int i = 0; i < text->length; i++)
	{
		if (check_for_capitals(text->sentences[i]))
		{
			remove_Sentence(text, i);
			i--;
		}
	}
}