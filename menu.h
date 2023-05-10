//
// Created by senyo on 26/4/2023.
//

#ifndef EDA2_MENU_H
#define EDA2_MENU_H

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


typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    char city[MAX_CITY_NAME];
    int birth;
    int user_number;
    char likes[5][MAX_LIKE_LENGTH];

}User_data;

int buscar_usuario(char algo[MAX_USERNAME_LENGTH], char otro[MAX_PASSWORD_LENGTH]);// Tengo que mirar como estan declaradas las cosas en el otro proyecto
void create_user(); //Esto no va a ser void porque va a tener que devolver una estructura pero hasta que la creemos se queda así

void menu();

#endif //EDA2_MENU_H
