#include "inverted.h"

void display_database(hash *HT)
{
    int index;
    int found = 0;

    printf("\n");
    printf("=====================================================================\n");
    printf("\t\t\tINVERTED SEARCH DATABASE\n");
    printf("=====================================================================\n");

    printf("Index\tWord\t\tFile Count\tFile Name\tWord Count\n");
    printf("---------------------------------------------------------------------\n");

    for (index = 0; index < 27; index++)
    {
        M_node *main_node = HT[index].H_link;

        while (main_node != NULL)
        {
            found = 1;

            S_node *sub_node = main_node->sub_link;

            /* Print first file along with main node */
            if (sub_node != NULL)
            {
                printf("%d\t%-15s\t%d\t\t%-15s\t%d\n",
                       index,
                       main_node->word,
                       main_node->file_count,
                       sub_node->filename,
                       sub_node->word_count);

                sub_node = sub_node->sub_link;
            }
            else
            {
                printf("%d\t%-15s\t%d\n",
                       index,
                       main_node->word,
                       main_node->file_count);
            }

            /* Print remaining files */
            while (sub_node != NULL)
            {
                printf("\t\t\t\t\t%-15s\t%d\n",
                       sub_node->filename,
                       sub_node->word_count);

                sub_node = sub_node->sub_link;
            }

            printf("---------------------------------------------------------------------\n");

            main_node = main_node->main_link;
        }
    }

    if (found == 0)
    {
        printf("Database is empty\n");
    }

    printf("=====================================================================\n");
}