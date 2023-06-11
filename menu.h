//
// Created by senyo on 26/4/2023.
//

#ifndef EDA2_MENU_H
#define EDA2_MENU_H
#include "usuario.h"
#include "publicacion.h"
#include "main.h"

void submenu_publicaciones_usuarios(User_data *other_user, timeline *tl);
int datosfichero(User_list* lista);
User_list* ficherodatos();

void print_gustos(User_data* usuario);
void guardar_gustos(User_list* lista,char username[MAX_USERNAME_LENGTH],char gustos[MAX_LIKE_LENGTH],int numero);
void create_user(User_list* lista); //Esto no va a ser void porque va a tener que devolver una estructura pero hasta que la creemos se queda así
char** bubblesort(char arr[], int n);



void menu(User_list* lista, timeline* tl);

#endif //EDA2_MENU_H
