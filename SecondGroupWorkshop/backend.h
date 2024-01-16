#include <stdio.h>
#include <stdlib.h>

void createFile(char *fileName)
{
    FILE *file = fopen(fileName, "w+");
    if (file == NULL)
    {
        printf("Error creating file!\n");
        exit(1);
    }
    fclose(file);
}

void deleteFile(char *fileName)
{
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