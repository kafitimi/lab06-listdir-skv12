#include "windows.h"
#include <stdio.h>
#include <locale.h>
#include <conio.h>

#pragma warning( disable : 4996)

static int count;

int zad0() {
	wchar_t s[512];
	GetCurrentDirectory(512, s);
	wprintf(L"Starting in: %s\n", s);
	return 0;
}

int zad1() {
	count = 0;
	int m = 16;
	HANDLE hSearch;
	WIN32_FIND_DATA fileinfo;
	hSearch = FindFirstFile(L"*", &fileinfo);
	do {
		count++;
		if (count > 2) {
			wprintf(TEXT("file #%d is <%s>\n"), count-2, fileinfo.cFileName);
		}
	} while (FindNextFile(hSearch, &fileinfo) != 0);
	FindClose(hSearch);
	return 0;
}

int main() {
	setlocale(LC_ALL, "RU");
	printf("Задание 0\n");
	zad0();
	printf("Задание 1\n");
	zad1();
    return 0;
}

