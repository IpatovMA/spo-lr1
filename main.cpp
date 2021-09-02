#include <iostream>
#include <windows.h>
#include <inttypes.h>
#define MAX_DATA_LENGTH 16383

using namespace std;

int main()
{
    printf("OS version: %i\n",GetVersion());

    char system_dir[MAX_PATH];
    GetSystemDirectory(system_dir, MAX_PATH);
    printf("System directory: %s\n", system_dir);

    DWORD return_len=256;

    char comp_name[MAX_PATH];
    GetComputerName(comp_name, &return_len);
    printf("Computer name: %s\n", comp_name);

    char user_name[MAX_PATH];
    GetUserName(user_name, &return_len);
    printf("User name: %s\n", user_name);

    char name_buffer[MAX_PATH];
    char path_buffer[MAX_PATH];

    HANDLE search = FindFirstVolume(name_buffer, sizeof(name_buffer));
    do {
        ULARGE_INTEGER free_space, total_sapce;
        GetVolumePathNamesForVolumeName(name_buffer,path_buffer,MAX_PATH,&return_len);
        bool f = GetDiskFreeSpaceEx(path_buffer,&free_space,&total_sapce,NULL);
            printf("Find new volume\n\tname: %s\n\tpath: %s\n", name_buffer,path_buffer);
        if (f){
            printf("\tsapce: %I64u / %I64u bytes\n",free_space.QuadPart,total_sapce.QuadPart);
        }else{
            printf("\tsapce: no data\n");
        }
    }
    while (FindNextVolume(search, name_buffer, sizeof(name_buffer)));

    FindVolumeClose(search);


    TCHAR lpValueName[MAX_DATA_LENGTH];
    DWORD lpcchValueName = MAX_DATA_LENGTH;
    HKEY phkResult;
    DWORD dwIndex = 0;
    char* lpData = new char[MAX_DATA_LENGTH];
    DWORD lpDataLength = MAX_DATA_LENGTH;

    long openR = RegOpenKeyEx(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Run",0, KEY_READ, &phkResult);
    if (openR == ERROR_SUCCESS)
    {
        long enumR = RegEnumValue(phkResult, dwIndex, lpValueName, &lpcchValueName, NULL, NULL, (unsigned char*)lpData, &lpDataLength);
        if (enumR == ERROR_SUCCESS)
        {
            cout << "The value and data is: \n" << lpValueName << ": " << lpData << endl;
           // printf("%s %s\n", lpValueName,lpData);
        }
        else cout <<"\nRegEnumValue error:" <<enumR <<endl;

    }
    else cout <<"\nRegOpenKeyEx error:" <<openR<<endl;
    RegCloseKey(phkResult);





    return 0;
}
