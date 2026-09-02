#include "inverted.h"

int update_database(hash *HT, F_node **head, const char *backup_file)
{
    FILE *fptr;
    char line[500];

    F_node *backup_head = NULL;
    F_node *new_head=NULL;


    fptr = fopen(backup_file, "r");

    if (fptr == NULL)
    {
        printf("ERROR : Unable to open backup file\n");
        return FAILURE;
    }
    
    free_database(HT);

    while (fgets(line, sizeof(line), fptr) != NULL)
    {
        char *token;

        int index;
        int file_count;

        line[strcspn(line, "\n")] = '\0';


        token = strtok(line, "#;");

        if (token == NULL)
        {
            continue;
        }

        index = atoi(token);
        token = strtok(NULL, ";");

        if (token == NULL)
        {
            continue;
        }

        char word[30];
        strcpy(word, token);

        token = strtok(NULL, ";");

        if (token == NULL)
        {
            continue;
        }

        file_count = atoi(token);

        M_node *new_main = malloc(sizeof(M_node));

        if (new_main == NULL)
        {
            printf("INFO : Memory allocation failed\n");
            fclose(fptr);
            return FAILURE;
        }

        strcpy(new_main->word, word);

        new_main->file_count = file_count;
        new_main->main_link = NULL;
        new_main->sub_link = NULL;

        if (HT[index].H_link == NULL)
        {
            HT[index].H_link = new_main;
        }
        else
        {
            M_node *temp_main = HT[index].H_link;

            while (temp_main->main_link != NULL)
            {
                temp_main = temp_main->main_link;
            }

            temp_main->main_link = new_main;
        }
        S_node *last_sub = NULL;

        for (int i = 0; i < file_count; i++)
        {
            char filename[50];
            int word_count;

            token = strtok(NULL, ";");

            if (token == NULL)
            {
                printf("ERROR : Invalid backup file\n");
                fclose(fptr);
                return FAILURE;
            }

            strcpy(filename, token);

            token = strtok(NULL, ";");

            if (token == NULL)
            {
                printf("ERROR : Invalid backup file\n");
                fclose(fptr);
                return FAILURE;
            }

            word_count = atoi(token);
            S_node *new_sub = malloc(sizeof(S_node));

            if (new_sub == NULL)
            {
                printf("INFO : Memory allocation failed\n");
                fclose(fptr);
                return FAILURE;
            }

            strcpy(new_sub->filename, filename);

            new_sub->word_count = word_count;
            new_sub->sub_link = NULL;

            if (new_main->sub_link == NULL)
            {
                new_main->sub_link = new_sub;
            }
            else
            {
                last_sub->sub_link = new_sub;
            }

            last_sub = new_sub;
             if(check_duplicates(backup_head,filename)==FAILURE)
            {
                insert_last(&backup_head,filename);
            }

        }
    }

    fclose(fptr);

    printf("INFO : Old database loaded successfully\n");

    F_node *temp=*head;
    while(temp!=NULL)
    {
        if(check_duplicates(backup_head,temp->f_name)==SUCCESS)
        {
            printf("ERROR : File %s is already present in database\n",temp->f_name);
        }
        else
        {
            insert_last(&new_head,temp->f_name);
        }
        temp=temp->link;
    }
    if (new_head != NULL)
    {
        if (create_database(HT, new_head) == FAILURE)
        {
            return FAILURE;
        }
    }
    else
    {
        printf("INFO : No new files to update\n");
    }

    printf("INFO : Database updated successfully\n");

    return SUCCESS;
}
