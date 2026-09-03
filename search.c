#include "inverted.h"

int search_database(hash *HT)
{
    char word[100];

    printf("\n\n");
    printf("============================================================\n");
    printf("                    SEARCH DATABASE\n");
    printf("============================================================\n");
    printf(" Enter word: ");
    scanf("%99s", word);

    int index = get_index(word);
    M_node *main_node = HT[index].H_link;

    while (main_node != NULL)
    {
        if (strcmp(main_node->word, word) == 0)
        {
            printf("\n============================================================\n");
            printf("                    SEARCH RESULT\n");
            printf("============================================================\n");
            printf(" Word       : %-42s\n", main_node->word);
            printf(" Hash index : %-42d\n", index);
            printf(" File count : %-42d\n", main_node->file_count);
            printf("------------------------------------------------------------\n");
            printf(" %-4s %-35s %12s\n", "No.", "File Name", "Occurrences");
            printf("------------------------------------------------------------\n");

            S_node *sub_node = main_node->sub_link;
            int count = 1;

            while (sub_node != NULL)
            {
                printf(" %-4d %-35s %12d\n",
                       count,
                       sub_node->filename,
                       sub_node->word_count);

                sub_node = sub_node->sub_link;
                count++;
            }

            printf("------------------------------------------------------------\n");
            printf(" Search completed successfully.\n");
            printf("============================================================\n");

            return SUCCESS;
        }

        main_node = main_node->main_link;
    }

    printf("\n============================================================\n");
    printf("                    SEARCH RESULT\n");
    printf("============================================================\n");
    printf(" Word '%s' was not found in the database.\n", word);
    printf("============================================================\n");

    return DATA_NOT_FOUND;
}