#include <iostream>
#include <array>
#include <chrono>

#define WIN32_LEAN_AND_MEAN             // Исключите редко используемые компоненты из заголовков Windows
// Файлы заголовков Windows
#include <windows.h>

typedef void(*MYPROC)(int*, int);

int Start(int* arr, int size)
{
	/*for (int i = 0; i < size; i++)
	{
		arr[i] = 1;
	}*/
	return 0;
}

int main()
{
    std::cout << "Hello World!\n";
	std::array<int, 5> arr{ 0, 0, 0, 0, 0 };
	auto lib = LoadLibraryA("Dll1.dll");
	if (lib != NULL) {
		auto address = reinterpret_cast<MYPROC>(GetProcAddress(lib, "Start"));
		if (address != NULL) {
			address(arr.data(), arr.size());

			auto start = std::chrono::high_resolution_clock::now();
			for (int i = 0; i < 100000000; i++)
				address(arr.data(), arr.size());
			auto stop = std::chrono::high_resolution_clock::now();
			std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count() << std::endl;

			start = std::chrono::high_resolution_clock::now();
			for (int i = 0; i < 100000000; i++)
				Start(arr.data(), arr.size());
			stop = std::chrono::high_resolution_clock::now();
			std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count() << std::endl;
		}
		else {
			std::cout << "GetProcAddress failed!\n";
		}
	}
	else {
		std::cout << "LoadLibrary failed!\n";
	}
	std::cout << "Results array\n";
	for (int i = 0; i < arr.size(); i++)
		std::cout << arr[i] << std::endl;
	system("pause");
}