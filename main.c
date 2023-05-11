#include <stdio.h>
#include "main.h"
#include "menu.c"

int datosfichero(FILE*fp) {//Aquí lo que sí hay que pasar como parametro es la estructura de la lista de usuarios
    User_data *user_search;
    fp = fopen("C:\\Users\\senyo\\CLionProjects\\EDA2\\Usuarios", "w");
    if (fp == NULL) {
        printf("Error al abrir el archivo.\n");
        return NO_FILE_FOUND;


    }
}

User_list* ficherodatos() { //Esto me tengo que mirar bien como hacerlo
    FILE *fp;
    fp = fopen("C:\\Users\\senyo\\CLionProjects\\EDA2\\Usuarios", "r");
    if (fp == NULL) {
        printf("Error al abrir el archivo.\n");
    }
    User_list *lista = (User_list*) malloc(sizeof(User_list));
    lista->first = NULL;
    lista->last = NULL;
    lista->size = 0;
    char nombre_usuario[MAX_USERNAME_LENGTH];
    char correo[MAX_EMAIL_LENGTH];
    char contraseña[MAX_PASSWORD_LENGTH];
    char ciudad[MAX_CITY_NAME];
    int año;
    int num_usuario;
    char gusto1[MAX_LIKE_LENGTH];
    char gusto2[MAX_LIKE_LENGTH];
    char gusto3[MAX_LIKE_LENGTH];
    char gusto4[MAX_LIKE_LENGTH];
    char gusto5[MAX_LIKE_LENGTH];
    int i = 0;
    while (fscanf(fp, "%s %s %s %s %d %d %s %s %s %s %s", nombre_usuario, correo, contraseña, ciudad, &año, &num_usuario, gusto1, gusto2, gusto3, gusto4, gusto5) == 11) {//Nombre de usuario, email, contraseña, ciudad, año, num usuario, gustos
        User_data *usuario = (User_data*) malloc(sizeof(User_data));
        strcpy(usuario->username, nombre_usuario);
        strcpy(usuario->email, correo);
        strcpy(usuario->password, contraseña);
        strcpy(usuario->city, ciudad);
        usuario->birth = año;
        usuario->user_number = num_usuario;
        strcpy(usuario->likes[1], gusto1);
        strcpy(usuario->likes[2], gusto2);
        strcpy(usuario->likes[3], gusto3);
        strcpy(usuario->likes[4], gusto4);
        strcpy(usuario->likes[5], gusto5);//Falta por hacer el prev y el next que no sé como hacerlo
    }
}

int main() {
    menu();//Antes del menú hay que cargar las cosas
}






