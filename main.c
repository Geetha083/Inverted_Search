/*
NAME:GEETHA RANI M
DATE:
PROJECT NAME:INVERTED SEARCH
PROJECT DESCRIPTION:In this project, we will implement an inverted search database using a hash table.
                    The database will store words and their occurrences in different files. 
					The program will allow users to create the database, display it, save it to a file, 
					search for words, and update the database from a backup file.
					
*/
#include "inverted.h"

int main(int argc, char *argv[])
{

    F_node *head = NULL;
    hash HT[27] = {0};
	int db_created = 0;

    // Validate_files
	if(validate_files(argc,argv,&head)==FAILURE)
	{
		printf("Error: Failed to validate files\n");
		return FAILURE;
	}
    printf("INFO : Files validated successfully\n");
	printf("Valid files are : ");
	print_filenames(head);

    int option;
    do
    {
	printf("\nSelect your choice among following operations:\n1. Create Database\n2. Display Database\n3. Save Database\n4. Search\n5. Update Database\n6. Exit\n\nEnter your choice : ");

	scanf("%d", &option);

	switch (option)
    { 
    case 1:
    if(create_database(HT, head) == SUCCESS)
    {
        db_created = 1;
    }
    break;
    case 2:
    if (db_created == 0)
    {
        printf("ERROR : Database is not created\n");
        break;
    }

    display_database(HT);
    break;

case 3:
    if (db_created == 0)
    {
        printf("ERROR : Database is not created\n");
        break;
    }

    save_database(HT);
    break;

case 4:
    if (db_created == 0)
    {
        printf("ERROR : Database is not created\n");
        break;
    }

    search_database(HT);
    break;
case 5:
{
    char backup_file[50];

    printf("Enter the backup file name: ");
    scanf("%49s", backup_file);

    if (validate_backup_file(backup_file) == FAILURE)
    {
        printf("ERROR : Invalid backup file\n");
        break;
    }

    if (update_database(HT, &head, backup_file) == SUCCESS)
    {
        db_created = 1;
    }

    break;
}

case 6:
    break;

default:
    printf("INFO : Please enter the valid option\n");
}
    }while( option != 6 );

    return 0;
}
