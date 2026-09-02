#include "inverted.h"

int create_database(hash *HT, F_node *head)
{
    if(HT == NULL || head == NULL)
    {
        printf("Error: Invalid parameters for creating database\n");
        return FAILURE;
    }
    F_node *file_node = head;

    while (file_node != NULL)
    {
        FILE *file_pointer = fopen(file_node->f_name, "r");

        if (file_pointer == NULL)
        {
            printf("Error: Unable to open file %s\n", file_node->f_name);
            file_node = file_node->link;
            continue;
        }

        char word[25];

        while (fscanf(file_pointer, "%24s", word) == 1)
        {
            int index = get_index(word);
            M_node *main_node = HT[index].H_link;
            M_node *prev_main = NULL;

            while (main_node != NULL &&
                   strcmp(main_node->word, word) < 0)
            {
                prev_main = main_node;
                main_node = main_node->main_link;
            }

            if (main_node == NULL || strcmp(main_node->word, word) != 0)
            {
                main_node = malloc(sizeof(M_node));

                if (main_node == NULL)
                {
                    printf("Memory allocation failed\n");
                    fclose(file_pointer);
                    return FAILURE;
                }

                strcpy(main_node->word, word);
                main_node->file_count = 1;
                main_node->main_link = NULL;

                S_node *sub_node = malloc(sizeof(S_node));

                if (sub_node == NULL)
                {
                    printf("Memory allocation failed\n");
                    free(main_node);
                    fclose(file_pointer);
                    return FAILURE;
                }

                strcpy(sub_node->filename, file_node->f_name);
                sub_node->word_count = 1;
                sub_node->sub_link = NULL;

                main_node->sub_link = sub_node;

                if (prev_main == NULL)
                {
                    main_node->main_link = HT[index].H_link;
                    HT[index].H_link = main_node;
                }
                else
                {
                    main_node->main_link = prev_main->main_link;
                    prev_main->main_link = main_node;
                }
            }
            else
            {
                S_node *sub_node = main_node->sub_link;
                S_node *prev_sub = NULL;

                while (sub_node != NULL &&
                       strcmp(sub_node->filename,
                              file_node->f_name) != 0)
                {
                    prev_sub = sub_node;
                    sub_node = sub_node->sub_link;
                }

                if (sub_node != NULL)
                {
                    sub_node->word_count++;
                }
                else
                {
                    sub_node = malloc(sizeof(S_node));

                    if (sub_node == NULL)
                    {
                        printf("Memory allocation failed\n");
                        fclose(file_pointer);
                        return FAILURE;
                    }

                    strcpy(sub_node->filename, file_node->f_name);
                    sub_node->word_count = 1;
                    sub_node->sub_link = NULL;

                    if (prev_sub == NULL)
                        main_node->sub_link = sub_node;
                    else
                        prev_sub->sub_link = sub_node;

                    main_node->file_count++;
                }
            }
        }

        fclose(file_pointer);
        file_node = file_node->link;
        
    }
    printf("\nSuccessful: Creation of DATABASE for file: ");

    F_node *temp = head;

    while (temp != NULL)
    {
        printf("%s", temp->f_name);

        if (temp->link != NULL)
            printf("  ");

        temp = temp->link;
    }

    printf("\n");
    return SUCCESS;

}
