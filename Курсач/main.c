#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "texttools.h"
#include "removeuncapitalized.h"
#include "maskfinder.h"
#include "sortsent.h"
#include "windowsrun.h"
#include "samewords.h"

#define BUFF_STR 100
#define BUFF_ELEM 10

void print_menu()
{
	fputws(L"�������� �������\n", stdout);
	fputws(L"1: ������� ������ ������� ��� ������� �����������\n", stdout);
	fputws(L"2: ������� ��� �����������, � ������� ��� ��������� ���� � ������ ����\n", stdout);
	fputws(L"3: ������������� ����� � ����������� �� ���������� ������� ���� � �����\n", stdout);
	fputws(L"4: ��� ������� ����������� ������� ���������� ���������� ���� � ������\n", stdout);
	fputws(L"5: ������� ����� �� �����\n", stdout);
	fputws(L"��� ������ �� ��������� ������� 0\n", stdout);
}


void welcome()
{
	fputws(L"�������� ������ �� ����������������. ������� 3\n", stdout);
	fputws(L"(�) ������� ������\n", stdout);
	fputws(L"����� ����������!\n", stdout);
	fputws(L"��� ����������� ������� Enter...\n", stdout);
	getwchar();
	system(CLEAR_SCREEN);
	fputws(L"������� �������������� �����. ���� ������ ����������� �� ������� ������� Enter\n", stdout);
}

int main()
{
	set_environment();
	Text* txtdata = malloc(sizeof(Text));
	welcome();
	init_Text(txtdata);
	read_Text(txtdata);
	system(CLEAR_SCREEN);
	fputws(L"����� ������� ��������.\n", stdout);
	fputws(L"��� ����������� ������� Enter...\n", stdout);
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
			fputws(L"��� ����������� ������� Enter...\n", stdout);
			getwchar();
			system(CLEAR_SCREEN);
			break;
		case L'2':
			remove_uncapitalized_sentences(txtdata);
			system(CLEAR_SCREEN);
			fputws(L"����������� �������. ������� �����? (�/�), �� ��������� �\n", stdout);
			wchar_t danet = getwchar();
			if (danet != 10)
				getwchar();
			if (danet != L'�' && danet != L'N')
			{
			//	system(CLEAR_SCREEN);
				print_Text(txtdata);
				fputws(L"��� ����������� ������� Enter...\n", stdout);
				getwchar();
			//	system(CLEAR_SCREEN);
			}
			else
			{
			//	system(CLEAR_SCREEN);
			}
			break;
		case L'3':
			system(CLEAR_SCREEN);
			fputws(L"�������� ����������� (������� ��� �����):\n", stdout);
			print_enum_Text(txtdata);
			int sent_number;
			wscanf(L"%d", &sent_number);
			getwchar();
			if (sent_number < 0 || sent_number >= txtdata->length)
			{
				fputws(L"������: ��� ����������� � ����� �������\n", stdout);
				fputws(L"��� ����������� ������� Enter...\n", stdout);
				getwchar();
				system(CLEAR_SCREEN);
			}
			else
			{
				sort_selected_sentence(txtdata, sent_number);
				system(CLEAR_SCREEN);
				fputws(L"����������� �������������. ������� ���? (�/�/�[������� ���� �����]), �� ��������� �\n", stdout);
				wchar_t danet = getwchar();
				if (danet != 10)
					getwchar();
				if (danet == L'�' || danet == L'T')
				{
					system(CLEAR_SCREEN);
					print_Text(txtdata);
					fputws(L"��� ����������� ������� Enter...\n", stdout);
					getwchar();
					system(CLEAR_SCREEN);
				}
				else if (danet != L'�' && danet != L'N')
				{
					system(CLEAR_SCREEN);
					print_sentence(txtdata->sentences[sent_number]);
					fputws(L"��� ����������� ������� Enter...\n", stdout);
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
			fputws(L"��� ����������� ������� Enter...\n", stdout);
			getwchar();
			system(CLEAR_SCREEN);
			break;
		case L'5':
			system(CLEAR_SCREEN);
			print_Text(txtdata);
			fputws(L"��� ����������� ������� Enter...\n", stdout);
			getwchar();
			system(CLEAR_SCREEN);
			break;
		case L'0':
			exit = 0;
			break;
		default:
			system(CLEAR_SCREEN);
			fputws(L"�������� �������\n", stdout);
			fputws(L"��� ����������� ������� Enter...\n", stdout);
			getwchar();
			system(CLEAR_SCREEN);
			break;
		}
	} while (exit);
	free_Text(txtdata);
	return exit;
}
