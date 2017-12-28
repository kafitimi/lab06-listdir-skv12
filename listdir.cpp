#include <windows.h>
#include <stdio.h>
#pragma warning( disable : 4996)

static int count, f, file;
static long long size, sizef;

int dfs() {
	// начинает перебор файлов и папок в текущей папке
	// 1) папки . и .. пропускаем
	// 2) если папка, то заходим в нее и вызываем dfs
	// 3) если файл, то посчитаем его в суммах count и size
	// 4) выходим в родительскую папку
	wchar_t s[512];
	HANDLE hSearch;
	WIN32_FIND_DATA fileinfo;

	hSearch = FindFirstFile(L"*", &fileinfo);   // найти первый файл
	FindNextFile(hSearch, &fileinfo);
	FindNextFile(hSearch, &fileinfo);
	do {
		count++; // некоторые файлы не считаются??	
		wprintf(L"file #%d is <%s> size = %lld\n ", count, fileinfo.cFileName, sizef);
		sizef = 0;
		if (fileinfo.dwFileAttributes == 16 || fileinfo.dwFileAttributes == 18) {
			f++;
			SetCurrentDirectory(fileinfo.cFileName);
			GetCurrentDirectory(512, s);
			dfs();
		}
		else {
			sizef = fileinfo.nFileSizeLow;
			size += sizef;
		}
		// if (...) { // если это подпапка
		// 	здесь будет обход в глубину
		// }
		// else {// это файл
		// size+=res....
		// }
	} while (FindNextFile(hSearch, &fileinfo) != 0);
	FindClose(hSearch);
	SetCurrentDirectory(L"..");
	return 0;
}

int main(int argc, wchar_t* argv[]) {
	wchar_t s[512];               	// текущая папка
	GetCurrentDirectory(512, s);  	// получить текущую папку
	wprintf(L"Starting in: %s\n", s);
	f = 0;
	count = 0;                  	// обнулить счетчик файлов
	size = 0;                   	// обнулить суммарный размер файлов
	dfs();                      	// запустить обход в глубину из текущей папки

	printf("File count = %d, folder = %d, size = %lld\n", count-f, f, size);
	return 0;
}


