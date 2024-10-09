#include<windows.h>
#include<stdio.h>

void* fluid_alloc(size_t len)
{
	void* ptr = malloc(len);
	return ptr;
}


int main(int argc, char* argv[])
{
	int result = -1;
		int i;

#ifdef _WIN32
	// console output will be utf-8
	SetConsoleOutputCP(CP_UTF8);
	// console input, too
	SetConsoleCP(CP_UTF8);

	// update argc and argv: utf-16 command line string to utf-8 arguments
	{
		LPWSTR* argv_w;

		// parses a unicode command line string and get an array of pointers to the command line arguments.
		// allocates a new argv array.
		if (
			(NULL == (argv_w = CommandLineToArgvW(GetCommandLineW(), &argc))) ||
			(1 > argc) ||
			(NULL == (argv = (char**)malloc(sizeof(char*)*(size_t)(1 + argc))))
		) return(result);

		// utf-16 to utf-8
		for (i = 0; argc > i; i++) {
			int buffer_size;
			if (
				(1 > (buffer_size = WideCharToMultiByte(CP_UTF8, 0, argv_w[i], -1, NULL, 0, NULL, NULL))) ||
				(NULL == (argv[i] = (char*)malloc((size_t)buffer_size))) ||
				(buffer_size != WideCharToMultiByte(CP_UTF8, 0, argv_w[i], -1, argv[i], buffer_size, NULL, NULL))
			) return(result);
		}

		argv[argc] = NULL;

		// release argv_w
		LocalFree(argv_w);
	}
#endif

	for (int i = 0; argc > i; i++)
	{
		printf("%s\n", argv[i]);

		if(0 == lstrcmpA("-P",argv[i]))
			printf("Hit\n");
	}

	return(0);
}
