#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <libgen.h>

void createFile()
{
    char fileName[100];
    printf("Enter the name of the file you want to create: ");
    scanf("%s", fileName);
    FILE *file = fopen(fileName, "w+");
    if (file == NULL)
    {
        printf("Error creating file!\n");
        exit(1);
    }
    fclose(file);
}

void deleteFile()
{
    char fileName[100];
    printf("Enter the name of the file you want to delete: ");
    scanf("%s", fileName);
    char userResponse;
    FILE *file = fopen(fileName, "r");
    if (file == NULL)
    {
        printf("File not Found!\n");
        exit(1);
    }
    fclose(file);
    printf("Are you sure you want to delete the file %s? (y/n): ", fileName);
    scanf(" %c", &userResponse);

    if (userResponse == 'y' || userResponse == 'Y')
    {
        if(remove(fileName) == 0)
            printf("Deleted successfully\n");
        else
            printf("Unable to delete the file\n");
    }
    else
    {
        printf("File deletion cancelled.\n");
    }
}

void listFiles()
{
    struct dirent *de;
    char script_dir[1024];
    strncpy(script_dir, __FILE__, sizeof(script_dir));
    dirname(script_dir);

    DIR *dr = opendir(script_dir);
    if (dr == NULL)
    {
        printf("Could not open current directory");
        return;
    }
    while ((de = readdir(dr)) != NULL)
        printf("%s\n", de->d_name);
    closedir(dr);
}

void searchFile()
{
    char fileName[100];
    char script_dir[1024];
    strncpy(script_dir, __FILE__, sizeof(script_dir));
    dirname(script_dir);

    printf("Enter the name of the file you want to search: ");
    scanf("%s", fileName);

    DIR *dr = opendir(script_dir);
    if (dr == NULL)
    {
        printf("Could not open current directory");
        return;
    }
    struct dirent *de;
    char filePath[1024];
    while ((de = readdir(dr)) != NULL)
    {
        if (strcmp(de->d_name, fileName) == 0)
        {
            snprintf(filePath, sizeof(filePath), "%s/%s", script_dir, de->d_name);
            printf("File found at path: %s\n", filePath);
            closedir(dr);
            return;
        }
    }
    printf("File not found!\n");
    closedir(dr);
}

