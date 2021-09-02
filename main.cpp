#include <iostream>
#include <windows.h>

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
            printf("\tsapce: %i / %i bytes\n",free_space.QuadPart,total_sapce.QuadPart);
        }else{
            printf("\tsapce: no data\n");
        }
    }
    while (FindNextVolume(search, name_buffer, sizeof(name_buffer)));

    if (GetLastError() != ERROR_NO_MORE_FILES) {
        // произошла ошибка, а не штатное оокнчание перебора
    }

    FindVolumeClose(search);

    return 0;
}
