//
// Created by senyo on 26/4/2023.
//

#ifndef EDA2_MENU_H
#define EDA2_MENU_H

#define MAX_USENAME_LENGTH 40
#define MIN_USERNAME_LENGTH 4
#define MAX_PASSWORD_LENGTH 20
#define MIN_PASSWORD_LENGTH 8
#define MAX_EMAIL_LENGTH 20

typedef struct {
    char username[MAX_USENAME_LENGTH];
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    int user_number;

}User_data;

User_data* user_declaration();

void registrar_usuario();
void buscar_usuario(int algo, int otro);// Tengo que mirar como estan declaradas las cosas en el otro proyecto
void create_user(); //Esto no va a ser void porque va a tener que devolver una estructura pero hasta que la creemos se queda así

void menu();

#endif //EDA2_MENU_H
