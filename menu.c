
//
// Created by senyo on 26/4/2023.
//
#include "main.c"
#include "menu.h"
#include <string.h>
#include <stdlib.h>

char* cambiar_ciudad(){
    char ciudad[MAX_CITY_NAME];
    while(strlen(ciudad) <= 1) {
        printf("Introduce tu ciudad de residencia \n");
        scanf("%s", ciudad);
    }
    return ciudad;
}

char** cambiar_gustos(){

    char ** gustos = malloc(5 *sizeof (char*));
    for (int i = 0; i < 5; i++) {
        printf("Introduce el gusto numero %d\n", i+1);
        scanf("%s", gustos[i] = malloc(MAX_LIKE_LENGTH * sizeof (char))); // Se tiene que repetir 5 veces.
    }
    return gustos;
}

void guardar_en_struct(User_data* guardar, const char* email, const char* password, const char* usuario, const char* ciudad , int año, const char* gustos[]){ // Función guarda en la estructura de datos User_data los valores de usuario,pasword,email....
    strncpy(guardar->email, email, MAX_EMAIL_LENGTH);
    strncpy(guardar->password, password, MAX_PASSWORD_LENGTH);
    strncpy(guardar->username, usuario, MAX_USERNAME_LENGTH);
    strncpy(guardar->city, ciudad, MAX_CITY_NAME);
    guardar->birth = año;

    for (int i = 0; i < MAX_LIKE_LENGTH; i++) {
        strncpy(guardar->likes[i], gustos[i], MAX_LIKE_LENGTH);
    }

}
void limpiar_User_data(User_data* guardar, const char* email, const char* password, const char* usuario, const char* ciudad , int año, const char* gustos[]){
    free(guardar->email);
    free(guardar->password);
    free(guardar->username);
    free(guardar->city);
    guardar->birth = 0;
    for (int i = 0; i < MAX_LIKE_LENGTH; i++) {
        strncpy(guardar->likes[i], NULL, MAX_LIKE_LENGTH);
    }


}

void create_user(){
    char usuario[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    char email[MAX_EMAIL_LENGTH];
    int año;
    int flag = FALSE;
    User_data guardar;
    while (flag == FALSE){
        printf("Introduzca un nombre de usuario (máximo", MAX_USERNAME_LENGTH, "caracteres y mínimo", MIN_USERNAME_LENGTH, ").\n");
        scanf("%s", usuario);
        if(strlen(usuario) > MIN_USERNAME_LENGTH && strlen(usuario) < MAX_USERNAME_LENGTH) flag = TRUE;
    }
    flag = FALSE;
    while(flag == FALSE){
        printf("\nIntroduzca una contraseña.\n");
        scanf("%s", password);
        if(strlen(password) > MIN_PASSWORD_LENGTH && strlen(password) < MAX_PASSWORD_LENGTH) flag = TRUE;
    }
    if (buscar_usuario(usuario,password) == USER_DOES_NOT_EXIST){
        FILE* fp;
        fp = fopen("C:\\Users\\senyo\\CLionProjects\\EDA2\\Usuarios", "a");

        while(strlen(email) <= 1) {
            printf("Introduce tu email\n");
            scanf("%s", email);
        }
        char *ciudad = cambiar_ciudad();

        while( año <= 1920) {
            printf("Introduce tu año de nacimiento\n");
            scanf("%s", año);
        }
        char** gustos = cambiar_gustos();
        guardar_en_struct (&guardar, email, password, usuario, ciudad,año ,gustos);
    }

    if (buscar_usuario(usuario,password) == USERNAME_ALREADY_EXISTS || buscar_usuario(usuario, password) == USER_ALREADY_EXISTS){
        printf("Lo sentimos, esté usuario ya existe\n");
        return;
    }

}



int buscar_usuario(char username[MAX_USERNAME_LENGTH], char otro[MAX_PASSWORD_LENGTH]) {
    User_data *user_search;
    FILE *fp;
    fp = fopen("C:\\Users\\senyo\\CLionProjects\\EDA2\\Usuarios", "r");
    if (fp == NULL) {
        printf("Error al abrir el archivo.\n");
        return NO_FILE_FOUND;
    }
    int usuarioEncontrado = FALSE;
    int contraseñaEncontrada = FALSE;
    while (fscanf(fp, "%s,%s\n", user_search->username, user_search->password) == 2) { //Seguramente el archivo tenga más cosas así que scanf habrá que cambiarlo
        if (strcmp(user_search->username, username) == 0) {
            usuarioEncontrado = TRUE;
            if(strcmp(user_search->password, otro) == 0){
                contraseñaEncontrada = TRUE;
            }
            break;
        }
    }
        fclose(fp);
        if (usuarioEncontrado == TRUE) {
            if (contraseñaEncontrada == TRUE){
                printf("El usuario y la contraseña coinciden. Usuario encontrado.\n");
                return USER_ALREADY_EXISTS;
            } else {
                printf("Contraseña incorrecta.\n");
                return USERNAME_ALREADY_EXISTS;
            }
        } else {
            printf("El usuario y/o la contraseña no coinciden. Usuario no encontrado.\n");
            return USER_DOES_NOT_EXIST;
        }
    }


void  menu() {

    int login = -1;
    printf("Hola, Buenos días!\n");
    printf("¿Eres un nuevo usuario(1) o ya tienes cuenta(2)?\n");
    while (login != 1 && login != 2) {
        scanf("%d", &login);
        printf("\nPor favor seleccione 1 si es un nuevo usuario o 2 si ya tiene una cuenta.\n");
    }

    if (login == 1) create_user();


    if (login == 2) {

        char nombre[MAX_PASSWORD_LENGTH];
        char contraseña[MAX_PASSWORD_LENGTH];
        printf("Ingresa el nombre de usuario\n");
        scanf("%s", nombre);
        printf("Ingresa la contraseña:\n");
        scanf("%s", contraseña);
        buscar_usuario(nombre, contraseña);//Hay que juntar esto con lo de abajo y hacer un while por si se equivoca al iniciar sesión pueda volver a intentarlo

        if (buscar_usuario(nombre, contraseña) == USER_ALREADY_EXISTS ) {
            printf("Inicio de sesión exitoso. ¡Bienvenido!\n");

            // Menú con opciones
            int opcion;
            int opcion2;
            int edad;
            char nombre_usuario;
            char ubicacion;
            char descripcion;

            printf("\n----- Menú -----\n");
            printf("1. Perfil (1)\n");
            printf("2. Página principal (2)\n");
            printf("0. Salir (0) \n");
            printf("Ingresa la opción deseada: ");
            scanf("%d", &opcion);

            if (opcion == 0) {

            }
            if (opcion == 1) {
                printf("\n----- Perfil -----\n");
                printf("1. Editar (1)\n"); // En está parte tendremos que hacer una función que elimine la cuenta si no ve necesario.
                printf("2. Ver valoraciones\n");
                printf("0. Atrás (0) \n");
                printf("Ingresa la opción deseada: ");
                scanf("%d", &opcion2);

                if (opcion2 == 0) {

                }
                if (opcion2 == 1) {
                    printf("Introduce tu nombre de usuario: \n");
                    scanf("%d", &nombre_usuario);
                    printf("Introduce tu Edad: \n");
                    scanf("%d", &edad);
                    printf("Introduce tu ubicación: \n");
                    scanf("%d", &ubicacion);
                    printf("Introduce una descripción:\n");
                    printf("\n");
                    scanf("%d", &descripcion);

                }
                if (opcion2 == 2) {

                }

            }

            if (opcion == 2) {
            }


        }
    }
}
