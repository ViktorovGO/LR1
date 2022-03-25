// LR1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <windows.h>
using namespace std;

void winver()
{	
	DWORD build = 0;
	DWORD info = GetVersion(); // Получение версии
	DWORD mask = 0x0000ffff; // Определение маски
	DWORD version = info & mask; // Получаем младшеее слово с помощью маскирования
	DWORD platform = info >> 16; // Получение страшего слова сдвигом вправо на 16 бит
	DWORD version_major = 0b000000000'00000000'00000000'11111111 & version; // Получение младшего и старшего байтов 
	DWORD version_minor = version >> 8;
	if ((info & 0x10000000) == 0)
	{
		build = platform >> 8;
	}
	cout << "Windows v " << version_major << "." << version_minor << " build(" << build << ")\n";
}

void GetDirectory()
{
	WCHAR system[MAX_PATH];
	GetSystemDirectory(system, sizeof(system));
	std::wcout << "SystemDirectory " << system << "\n"; // Получение системного каталога

	char cname[100];
	char uname[100];
	DWORD buf = 256;        // длина имени компьютера или пользователя

	if (GetComputerNameA(cname , &buf)) 
	printf("ComputerName: %s", cname);// Имя компьютера
	cout << endl;

	if (GetUserNameA(uname, &buf))
		printf("UserName: %s", uname); // Имя пользователя
		cout << endl;
}
void DiskInf()
{
	wchar_t buffer[MAX_PATH];
	int k = 1;                      
	HANDLE search = FindFirstVolume(buffer, sizeof(buffer));
	do 
	{// операции с томом, техническое имя которого в buffer
		wcout<<"Technical name"<< k<<":" << buffer<<"\n";
		k++;

		wchar_t buf[MAX_PATH * 4];
		DWORD size = MAX_PATH * 4;
		GetVolumePathNamesForVolumeNameW(buffer, buf, size, &size);
		wchar_t* path = buf;
		wcout << "Mount point: " << path << "\n";
		
		LPCSTR LPC_path = (LPCSTR)path;
		ULARGE_INTEGER free_bytes, total_number;
		if (GetDiskFreeSpaceEx(buf, &free_bytes, &total_number, nullptr))
			cout << "Free memory: " << free_bytes.QuadPart << " bytes "<<"Total memory: " << total_number.QuadPart <<" bytes"<<'\n';
		
		else
		{
		int code = GetLastError();
		printf("GetDiskFreeSpaceExA failed with error %d\n", code);
		
		}
		
	} 
	while (FindNextVolume(search, buffer, sizeof(buffer)));

	if (GetLastError() != ERROR_NO_MORE_FILES) {
		// произошла ошибка, а не штатное оокнчание перебора
	}

	FindVolumeClose(search);
}
int main()
{
	winver();
	GetDirectory();
	DiskInf();
	
}

