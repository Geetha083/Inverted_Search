#include "inverted.h"

int search_database(hash *HT)
{
    char word[100];

    printf("Enter the word for search: ");
    scanf("%99s", word);

    int index = get_index(word);

    M_node *main_node = HT[index].H_link;

    while (main_node != NULL)
    {
        if (strcmp(main_node->word, word) == 0)
        {
            printf("\n%s found in database\n", word);
            printf("index:%d\n", index);
            printf("word:%s\n", main_node->word);
            printf("File count:%d\n", main_node->file_count);

            printf("\nfiles:\n");

            S_node *sub_node = main_node->sub_link;

            while (sub_node != NULL)
            {
                printf("file names:%s\n", sub_node->filename);
                printf("word count:%d\n", sub_node->word_count);

                sub_node = sub_node->sub_link;
            }

            return SUCCESS;
        }

        main_node = main_node->main_link;
    }

    printf("\n%s not found in database\n", word);

    return DATA_NOT_FOUND;
}