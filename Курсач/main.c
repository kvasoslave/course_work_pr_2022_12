#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "texttools.h"
#include "removeuncapitalized.h"
#include "maskfinder.h"
#include "sortsent.h"
#include "windowsrun.h"

#define BUFF_STR 100
#define BUFF_ELEM 10

void print_menu()
{
	puts(L"Выберите функцию");
	puts(L"1: Вывести строку образец для каждого предложения");
	puts(L"2: Удалить все предложения, в которых нет заглавных букв в начале слов");
	puts(L"3: Отсортировать слова в предложении по количеству гласных букв в слове");
	puts(L"4: Для каждого предложения вывести количество одинаковых слов в строке");
	puts(L"Для выхода из программы введите 0");
}

int main()
{
	set_environment();
	Text* data = malloc(sizeof(Text));
	init_Text(data);
	read_Text(data);
	print_Text(data);
	print_same_words_count(data);
	print_Text(data);
	free_Text(data);
}