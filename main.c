#include <stdio.h>
#include "main.h"
#include "menu.c"

void insert(User_data* miembro, char nombre_usuario[MAX_USERNAME_LENGTH], char correo[MAX_EMAIL_LENGTH], char contraseña[MAX_PASSWORD_LENGTH], char ciudad[MAX_CITY_NAME], int año, int num_usuario, char gusto1[MAX_LIKE_LENGTH], char gusto2[MAX_LIKE_LENGTH], char gusto3[MAX_LIKE_LENGTH], char gusto4[MAX_LIKE_LENGTH], char gusto5[MAX_LIKE_LENGTH]){
    strcpy(miembro->username, nombre_usuario);
    strcpy(miembro->email, correo);
    strcpy(miembro->password, contraseña);
    strcpy(miembro->city, ciudad);
    miembro->birth = año;
    miembro->user_number = num_usuario;
    strcpy(miembro->likes[1], gusto1);
    strcpy(miembro->likes[2], gusto2);
    strcpy(miembro->likes[3], gusto3);
    strcpy(miembro->likes[4], gusto4);
    strcpy(miembro->likes[5], gusto5);
    miembro->next = NULL;
}

void push(User_list* lista, char nombre_usuario[MAX_USERNAME_LENGTH], char correo[MAX_EMAIL_LENGTH], char contraseña[MAX_PASSWORD_LENGTH], char ciudad[MAX_CITY_NAME], int año, int num_usuario, char gusto1[MAX_LIKE_LENGTH], char gusto2[MAX_LIKE_LENGTH], char gusto3[MAX_LIKE_LENGTH], char gusto4[MAX_LIKE_LENGTH], char gusto5[MAX_LIKE_LENGTH]) {
    User_data *usuario = lista->first;
    while (usuario->next != NULL) {
        usuario = usuario->next;
    }

    usuario->next = (User_data *) malloc(sizeof(User_data));
    //Aquí van todos los datos
    insert(usuario->next, nombre_usuario, correo, contraseña, ciudad, año, num_usuario, gusto1, gusto2, gusto3, gusto4, gusto5);
    lista->last = usuario->next;
    usuario->next->prev = usuario;
    lista->size++;
}

int datosfichero(User_list* lista) {//Aquí lo que sí hay que pasar como parametro es la estructura de la lista de usuarios
    User_data *user_search;
    FILE * fp = fopen("C:\\Users\\senyo\\CLionProjects\\EDA2\\Usuarios", "w");
    if (fp == NULL) {
        printf("Error al abrir el archivo.\n");
        return NO_FILE_FOUND;


    }
}

User_list* ficherodatos() { //Esto me tengo que mirar bien como hacerlo
    FILE *fp;
    fp = fopen("C:\\Users\\senyo\\CLionProjects\\EDA2\\Usuarios", "r");//Esto habría que cambiarlo para que se pudiera abrir en cualquier ordenador
    if (fp == NULL) {
        printf("Error al abrir el archivo.\n");
    }
    User_list *lista = (User_list*) malloc(sizeof(User_list));
    lista->first = (User_data *) malloc(sizeof(User_data));
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
    if(fscanf(fp, "%s %s %s %s %d %d %s %s %s %s %s", nombre_usuario, correo, contraseña, ciudad, &año, &num_usuario, gusto1, gusto2, gusto3, gusto4, gusto5) == 11){
        insert(lista->first, nombre_usuario, correo, contraseña, ciudad, año, num_usuario, gusto1, gusto2, gusto3, gusto4, gusto5);
        lista->last = lista->first;
        lista->first->prev = NULL;
        lista->size = 1;//Esto es para el primer elemento de la lista
    } else{
        printf("\nSe ha producido un error al intentar leer el archivo.\n");
    }
    //El while es para el resto de elementos de la lista
    while (fscanf(fp, "%s %s %s %s %d %d %s %s %s %s %s", nombre_usuario, correo, contraseña, ciudad, &año, &num_usuario, gusto1, gusto2, gusto3, gusto4, gusto5) == 11) {//Nombre de usuario, email, contraseña, ciudad, año, num usuario, gustos
        push(lista, nombre_usuario, correo, contraseña, ciudad, año, num_usuario, gusto1, gusto2, gusto3, gusto4, gusto5);
    }
    return lista;
}

int main() {
    User_list* lista = ficherodatos();//Cargamos lo que está en el fichero al empezar
    menu(lista);//Antes del menú hay que cargar las cosas
}






