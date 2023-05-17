//
// Created by senyo on 26/4/2023.
//

#ifndef EDA2_MENU_H
#define EDA2_MENU_H
#include "main.h"

#define MAX_USERNAME_LENGTH 16
#define MIN_USERNAME_LENGTH 4
#define MAX_PASSWORD_LENGTH 40
#define MIN_PASSWORD_LENGTH 8
#define MAX_CITY_NAME 58
#define MAX_EMAIL_LENGTH 60
#define MAX_LIKE_LENGTH 50
#define TRUE 1
#define FALSE 0
#define USERNAME_ALREADY_EXISTS -1
#define USER_ALREADY_EXISTS -2
#define USER_DOES_NOT_EXIST -3
#define NO_FILE_FOUND 500
#define MAX_POST_LENGHT 250

typedef struct _data{
    char username[MAX_USERNAME_LENGTH];
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    char city[MAX_CITY_NAME];
    int birth;
    int user_number;
    char likes[5][MAX_LIKE_LENGTH];
    float nota;
    struct _data* next;
    struct _data* prev;
}User_data;

typedef struct{
    User_data* first;
    User_data* last;
    int size;
}User_list;

int print_gustos(User_list* lista ,char username[MAX_USERNAME_LENGTH]);
void guardar_gustos(User_list* lista,char username[MAX_USERNAME_LENGTH],char gustos[MAX_LIKE_LENGTH],int numero);
int buscar_usuario(User_list* lista, char algo[MAX_USERNAME_LENGTH], char otro[MAX_PASSWORD_LENGTH]);// Tengo que mirar como estan declaradas las cosas en el otro proyecto
void create_user(); //Esto no va a ser void porque va a tener que devolver una estructura pero hasta que la creemos se queda así
void bubblesort(char arr[], int n);



void menu();

#endif //EDA2_MENU_H
