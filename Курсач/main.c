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
	puts(L"�������� �������");
	puts(L"1: ������� ������ ������� ��� ������� �����������");
	puts(L"2: ������� ��� �����������, � ������� ��� ��������� ���� � ������ ����");
	puts(L"3: ������������� ����� � ����������� �� ���������� ������� ���� � �����");
	puts(L"4: ��� ������� ����������� ������� ���������� ���������� ���� � ������");
	puts(L"��� ������ �� ��������� ������� 0");
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