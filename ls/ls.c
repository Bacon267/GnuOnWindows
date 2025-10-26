#include <windows.h>
#include <shellapi.h>
#include <stdio.h>
#include <string.h>

#define global_variable static

global_variable WORD Year, Month, Day, Hour, Minute;

void Win32FormatTime(FILETIME FileTime, SYSTEMTIME *TimeFormatted)
{
    FileTimeToSystemTime(&FileTime, TimeFormatted);

    Year = TimeFormatted->wYear;
    Month = TimeFormatted->wMonth;
    Day = TimeFormatted->wDay;
    Hour = TimeFormatted->wHour;
    Minute = TimeFormatted->wMinute;
}

void Win32FindFile(int argc, char *argv[])
{
   WIN32_FIND_DATAA FileData = {0};
   CONSOLE_SCREEN_BUFFER_INFO ConsoleInfo = {0};
   SYSTEMTIME TimeFormatted = {0};//Maybe needs to be a LP

   //Formats the String in case there's no arguments
   TCHAR Buffer[MAX_PATH];
   DWORD BufferSize = GetCurrentDirectory(MAX_PATH, Buffer);
   Buffer[BufferSize] = '\\';
   Buffer[BufferSize + 1] = '*';
   HANDLE FileHandle = FindFirstFile(Buffer, &FileData);//FileHandle
   HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);//Console Handle

   //This if/else statement checks wether there's a path or not on argv[1]
   if(!argv[1]){
       while(FindNextFileA(FileHandle, &FileData) != 0){
           if(strcmp(FileData.cFileName, ".") == 0 || strcmp(FileData.cFileName, "..") == 0) continue;
           else{
               printf("%s\t", FileData.cFileName);
           }
       }
   }
   else if(strcmp(argv[1], "-l") == 0){
       while(FindNextFileA(FileHandle, &FileData) != 0){
           //Gets the default color
           GetConsoleScreenBufferInfo(ConsoleHandle, &ConsoleInfo);
           WORD DefaultColor = ConsoleInfo.wAttributes;
           Win32FormatTime(FileData.ftLastWriteTime, &TimeFormatted);

           if(FileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY){
               printf("%02d/%02d/%02d\t%02d:%02d   <DIR>", Month, Day, Year, Hour, Minute);
               SetConsoleTextAttribute(ConsoleHandle, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
               printf("\t%s\n", FileData.cFileName);
               SetConsoleTextAttribute(ConsoleHandle, DefaultColor);
           }
           else {
               printf("%02d/%02d/%02d\t%02d:%02d   <FILE>", Month, Day, Year, Hour, Minute);
               printf("\t%s\n", FileData.cFileName);
           }
       }
   }
}

int main(int argc, TCHAR *argv[])
{
    Win32FindFile(argc, argv);
	return 0;
}
