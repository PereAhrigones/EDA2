//
// Created by senyo on 26/4/2023.
//

#ifndef EDA2_MAIN_H
#define EDA2_MAIN_H
#include "menu.h"



void insert(User_data* miembro, char nombre_usuario[MAX_USERNAME_LENGTH], char correo[MAX_EMAIL_LENGTH], char contraseña[MAX_PASSWORD_LENGTH], char ciudad[MAX_CITY_NAME], int año, int num_usuario, char gusto1[MAX_LIKE_LENGTH], char gusto2[MAX_LIKE_LENGTH], char gusto3[MAX_LIKE_LENGTH], char gusto4[MAX_LIKE_LENGTH], char gusto5[MAX_LIKE_LENGTH], float nota);

void push(User_list* lista, char nombre_usuario[MAX_USERNAME_LENGTH], char correo[MAX_EMAIL_LENGTH], char contraseña[MAX_PASSWORD_LENGTH], char ciudad[MAX_CITY_NAME], int año, int num_usuario, char gusto1[MAX_LIKE_LENGTH], char gusto2[MAX_LIKE_LENGTH], char gusto3[MAX_LIKE_LENGTH], char gusto4[MAX_LIKE_LENGTH], char gusto5[MAX_LIKE_LENGTH], float nota);

User_list* ficherodatos();

#endif //EDA2_MAIN_H
