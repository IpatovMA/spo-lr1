#include <iostream>
#include <windows.h>
#include <inttypes.h>
#define MAX_DATA_LENGTH 16383

using namespace std;

int main()
{
    LARGE_INTEGER t_start;
    LARGE_INTEGER t_fin;
    LARGE_INTEGER frec;

    QueryPerformanceCounter(&t_start);

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
        cout << "\nSuccsess open HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Run" << endl;
        while (1) {
            long enumR = RegEnumValue(phkResult, dwIndex, lpValueName, &lpcchValueName, NULL, NULL, (unsigned char*)lpData, &lpDataLength);
            if (enumR == ERROR_SUCCESS)
            {
                cout << "The value and data is: \n" << lpValueName << ": " << lpData << endl;
                dwIndex++;
            }
            else{
                if (enumR == ERROR_NO_MORE_ITEMS)
                {
                    cout << "There are no more values available \n" << endl;
                }
                else cout <<"\nRegEnumValue error:" <<enumR <<endl;

                break;

            }
        }
    }
    else cout <<"\nRegOpenKeyEx error:" <<openR<<endl;
    RegCloseKey(phkResult);


    QueryPerformanceCounter(&t_fin);
    QueryPerformanceFrequency(&frec);
    printf("Performance Frequency = %i sec^-1\n",  frec);

    double ticks = t_fin.QuadPart - t_start.QuadPart;
    double ticks_per_sec = frec.QuadPart;;
    double usec = 1e6 * ticks / ticks_per_sec;
    printf("Program duration = %f usec\n",  usec);


    return 0;
}
