// Simplified version of MS sample code provided here: https://learn.microsoft.com/en-us/windows/win32/fileio/listing-the-files-in-a-directory

#include <windows.h>
#include <wchar.h>
#include <tchar.h>
#include <stdio.h>
#include <strsafe.h>
#include <iostream>
#include <vector>


void removeHiddenFiles(std::vector<std::wstring> *inputNames, std::vector<std::wstring>* outputNames)
{
    size_t index = 0;

    for (auto it = inputNames->begin(); it != inputNames->end(); it++)
    {
        if (it->substr(0,1) != L".")
        {
            outputNames->push_back(*it);
            continue;
        }
    }
}

int _tmain(int argc, TCHAR* argv[])
{
    WIN32_FIND_DATA ffd;
    LARGE_INTEGER filesize;
    TCHAR szDir[MAX_PATH];
    size_t length_of_arg;
    HANDLE hFind = INVALID_HANDLE_VALUE;
    DWORD dwError = 0;

    std::vector<std::wstring> fileNames;
    std::vector<std::wstring> outputNames;

    StringCchCopy(szDir, MAX_PATH, TEXT("."));
    StringCchCat(szDir, MAX_PATH, TEXT("\\*"));

    hFind = FindFirstFile(szDir, &ffd);

    do
    {
        if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
        {
            continue;
        }
        else
        {
            filesize.LowPart = ffd.nFileSizeLow;
            filesize.HighPart = ffd.nFileSizeHigh;
            fileNames.push_back(std::wstring(ffd.cFileName));
        }
    } while (FindNextFile(hFind, &ffd) != 0);

    FindClose(hFind);
    removeHiddenFiles(&fileNames, &outputNames);

    for (auto it = outputNames.begin(); it != outputNames.end(); it++)
    {
        wprintf(TEXT("%s\n"), it->c_str());
    }

    return 0;
}
