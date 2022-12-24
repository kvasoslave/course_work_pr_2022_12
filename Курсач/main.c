#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "texttools.h"
#include "removeuncapitalized.h"
#include "maskfinder.h"
#include "sortsent.h"
#include "linuxrun.h"
#include "samewords.h"

void print_menu()
{
	fputws(L"Выберите функцию\n", stdout);
	fputws(L"1: Вывести строку образец для каждого предложения\n", stdout);
	fputws(L"2: Удалить все предложения, в которых нет заглавных букв в начале слов\n", stdout);
	fputws(L"3: Отсортировать слова в предложении по количеству гласных букв в слове\n", stdout);
	fputws(L"4: Для каждого предложения вывести количество одинаковых слов в строке\n", stdout);
	fputws(L"5: Вывести текст на экран\n", stdout);
	fputws(L"Для выхода из программы введите 0\n", stdout);
}


void welcome()
{
	fputws(L"Курсовая работа по программированию. Вариант 3\n", stdout);
	fputws(L"(С) Жихарев Виктор\n", stdout);
	fputws(L"Добро Пожаловать!\n", stdout);
	fputws(L"Для продолжения нажмите Enter...\n", stdout);
	getwchar();
	system(CLEAR_SCREEN);
	fputws(L"Введите обрабатываемый текст. Ввод текста завершается по нажатию клавиши Enter\n", stdout);
}

int main()
{
	set_environment();
	Text* txtdata = malloc(sizeof(Text));
	welcome();
	init_Text(txtdata);
	read_Text(txtdata);
	system(CLEAR_SCREEN);
	fputws(L"Текст успешно прочитан.\n", stdout);
	int exit = 1;
	wchar_t mode;
	do
	{
		print_menu();
		do
			mode = getwchar();
		while (iswspace(mode));
		getwchar();
		switch (mode)
		{
		case L'1':
			system(CLEAR_SCREEN);
			print_text_masks(txtdata);
			fputws(L"Для продолжения нажмите Enter...\n", stdout);
			getwchar();
			system(CLEAR_SCREEN);
			break;
		case L'2':
			remove_uncapitalized_sentences(txtdata);
			system(CLEAR_SCREEN);
			fputws(L"Предложения удалены. Вывести текст? (Д/Н), по умолчанию Д\n", stdout);
			wchar_t danet = getwchar();
			if (danet != 10)
				getwchar();
			if (danet != L'Н' && danet != L'N')
			{
				system(CLEAR_SCREEN);
				print_Text(txtdata);
				fputws(L"Для продолжения нажмите Enter...\n", stdout);
				getwchar();
				system(CLEAR_SCREEN);
			}
			else
			{
				system(CLEAR_SCREEN);
			}
			break;
		case L'3':
			system(CLEAR_SCREEN);
			fputws(L"Выберите предложение (введите его номер):\n", stdout);
			print_enum_Text(txtdata);
			int sent_number;
			wscanf(L"%d", &sent_number);
			getwchar();
			if (sent_number < 0 || sent_number >= txtdata->length)
			{
				fputws(L"Ошибка: Нет предложения с таким номером\n", stdout);
				fputws(L"Для продолжения нажмите Enter...\n", stdout);
				getwchar();
				system(CLEAR_SCREEN);
			}
			else
			{
				sort_selected_sentence(txtdata, sent_number);
				system(CLEAR_SCREEN);
				fputws(L"Предложение отсортировано. Вывести его? (Д/Н/Т[вывести весь текст]), по умолчанию Д\n", stdout);
				wchar_t danet = getwchar();
				if (danet != 10)
					getwchar();
				if (danet == L'Т' || danet == L'T')
				{
					system(CLEAR_SCREEN);
					print_Text(txtdata);
					fputws(L"Для продолжения нажмите Enter...\n", stdout);
					getwchar();
					system(CLEAR_SCREEN);
				}
				else if (danet != L'Н' && danet != L'N')
				{
					system(CLEAR_SCREEN);
					print_sentence(txtdata->sentences[sent_number]);
					fputws(L"Для продолжения нажмите Enter...\n", stdout);
					getwchar();
					system(CLEAR_SCREEN);
				}
				else
				{
					system(CLEAR_SCREEN);
				}
			}
			break;
		case L'4':
			system(CLEAR_SCREEN);
			print_same_words_count(txtdata);
			fputws(L"Для продолжения нажмите Enter...\n", stdout);
			getwchar();
			system(CLEAR_SCREEN);
			break;
		case L'5':
			system(CLEAR_SCREEN);
			print_Text(txtdata);
			fputws(L"Для продолжения нажмите Enter...\n", stdout);
			getwchar();
			system(CLEAR_SCREEN);
			break;
		case L'0':
			exit = 0;
			break;
		default:
			system(CLEAR_SCREEN);
			fputws(L"Неверная команда\n", stdout);
			fputws(L"Для продолжения нажмите Enter...\n", stdout);
			getwchar();
			system(CLEAR_SCREEN);
			break;
		}
	} while (exit);
	free_Text(txtdata);
	return exit;
}
