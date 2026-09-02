#ifndef INVERTED_H
#define INVERTED_H

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define SUCCESS		1
#define FAILURE		0
#define DATA_NOT_FOUND 2

typedef struct file
{
    char f_name[20];
    struct file *link;
}F_node;

typedef struct Sub
{
    int word_count;
    char filename[20];
    struct Sub *sub_link;
}S_node;

typedef struct Main
{
    char word[25];
    int file_count;
    S_node *sub_link;
    struct Main *main_link;
}M_node;

typedef struct Hashtable
{
    int index;
    M_node *H_link;
}hash;

int create_database(hash *HT, F_node *head);
void display_database(hash *HT);
int search_database(hash *HT);
int save_database(hash *HT);
int update_database(hash *HT,F_node **head, const char *backup_file);
int validate_backup_file(const char *backup_file);
void free_database(hash *HT);

int validate_files(int argc, char *argv[], F_node **head);
int insert_last(F_node **head, char *f_name);
int check_duplicates(F_node *head, char *f_name);
int print_filenames(F_node *head);
int get_index(char *word);

#endif
