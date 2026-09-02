#include "inverted.h"

/* Function definitions */

int validate_files(int argc, char *argv[], F_node **head)
{
    int index;

    if (argc > 1)
    {
        for (index = 1; index < argc; index++)
        {
            char *extension = strrchr(argv[index], '.');
            FILE *file_pointer;

            if (extension == NULL ||
                strcmp(extension, ".txt") != 0)
            {
                printf("Error: %s is not a .txt file\n", argv[index]);
                continue;
            }

            file_pointer = fopen(argv[index], "r");

            if (file_pointer == NULL)
            {
                printf("Error: Cannot open %s\n", argv[index]);
                continue;
            }

            if (fgetc(file_pointer) == EOF)
            {
                printf("Error: %s is empty\n", argv[index]);
                fclose(file_pointer);
                continue;
            }

            fclose(file_pointer);

            if (check_duplicates(*head, argv[index]) == SUCCESS)
            {
                printf("Error: %s is a duplicate file\n", argv[index]);
                continue;
            }

            if (insert_last(head, argv[index]) == FAILURE)
            {
                printf("Error: Unable to store %s\n", argv[index]);
                return FAILURE;
            }
        }
        if(*head==NULL)
        {
            printf("Error: No valid files provided\n");
            return FAILURE;
        }

        return SUCCESS;
    }
    else
    {
        printf("Error: Invalid arguments\n");
        return FAILURE;
    }
}
int get_index(char *word)
{
    if(word[0] >= 'A' && word[0] <= 'Z')
        return word[0] - 'A';
    else if(word[0] >= 'a' && word[0] <= 'z')
        return word[0] - 'a';
    else
        return 26;
}
int insert_last(F_node **head, char *f_name)
{
    F_node *new_node =malloc(sizeof(F_node));
    if(new_node==NULL)
    return FAILURE;

    strcpy(new_node->f_name,f_name);
    new_node->link=NULL;
    if(*head ==NULL)
    {
        *head =new_node;
        return SUCCESS;
    }
    F_node *temp=*head;
    while(temp->link!=NULL)
       temp=temp->link;
    temp->link=new_node;

    return SUCCESS;
}
int check_duplicates(F_node *head, char *f_name)
{
    while(head!=NULL)
    {
        if(strcmp(head->f_name,f_name)==0)
        return SUCCESS;

        head=head->link;
    }
    return FAILURE;
}
int print_filenames(F_node *head)
{
    if(head==NULL)
    {
        printf("No file available\n");
        return FAILURE;
    }
    else
    {
        while(head)
        {
            printf("%s->",head->f_name);
            head=head->link;
        }
        printf("NULL\n");
    }
    return SUCCESS;
}
int validate_backup_file(const char *backup_file)
{
    char *extension = strrchr(backup_file, '.');

    if (extension == NULL || strcmp(extension, ".txt") != 0)
    {
        printf("Error: Backup file must have .txt extension\n");
        return FAILURE;
    }

    FILE *fptr = fopen(backup_file, "r");

    if (fptr == NULL)
    {
        printf("Error: Backup file '%s' not found\n", backup_file);
        return FAILURE;
    }

    fseek(fptr, 0, SEEK_END);

    if (ftell(fptr) == 0)
    {
        printf("Error: Backup file '%s' is empty\n", backup_file);
        fclose(fptr);
        return FAILURE;
    }

    rewind(fptr);

    char first_char = fgetc(fptr);

    if (first_char != '#')
    {
        printf("Error: Invalid backup database format\n");
        fclose(fptr);
        return FAILURE;
    }

    fclose(fptr);

    return SUCCESS;
}
void free_database(hash *HT)
{
    for (int i = 0; i < 27; i++)
    {
        M_node *main_node = HT[i].H_link;

        while (main_node != NULL)
        {
            S_node *sub_node = main_node->sub_link;

            while (sub_node != NULL)
            {
                S_node *temp_sub = sub_node;
                sub_node = sub_node->sub_link;
                free(temp_sub);
            }

            M_node *temp_main = main_node;
            main_node = main_node->main_link;
            free(temp_main);
        }

        HT[i].H_link = NULL;
    }
}