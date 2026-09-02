#include "inverted.h"

int save_database(hash *HT)
{
    char file[30];

    printf("Enter the file name to save database: ");
    scanf("%29s", file);

    /* Validate .txt extension */
    char *extension = strrchr(file, '.');

    if (extension == NULL || strcmp(extension, ".txt") != 0)
    {
        printf("Error: Invalid file extension\n");
        return FAILURE;
    }

    FILE *fptr = fopen(file, "w");

    if (fptr == NULL)
    {
        printf("Error: Unable to open file\n");
        return FAILURE;
    }

    for (int i = 0; i < 27; i++)
    {
        M_node *temp_main = HT[i].H_link;

        while (temp_main != NULL)
        {
            fprintf(fptr, "#%d;%s;%d;",
                    i,
                    temp_main->word,
                    temp_main->file_count);

            S_node *temp_sub = temp_main->sub_link;

            while (temp_sub != NULL)
            {
                fprintf(fptr, "%s;%d;",
                        temp_sub->filename,
                        temp_sub->word_count);

                temp_sub = temp_sub->sub_link;
            }

            fprintf(fptr, "#\n");

            temp_main = temp_main->main_link;
        }
    }

    fclose(fptr);

    printf("Database saved successfully.\n");

    return SUCCESS;
}