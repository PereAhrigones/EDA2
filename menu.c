//
// Created by senyo on 26/4/2023.
//
#include "main.c"
#include "menu.h"
#include <string.h>



void create_user(){
    char usuario[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    printf("Introduzca un nombre de usuario (máximo 16 caracteres).\n");
    scanf("%s", usuario);
    printf("Introduzca una contraseña.\n");
    scanf("%s", password);
    if (buscar_usuario(usuario,password) == USER_DOES_NOT_EXIST){
        FILE* fp;
        fp = fopen("C:\\Users\\senyo\\CLionProjects\\EDA2\\Usuarios", "a"); //Yo lo abriría en modo append para no sobreescribir lo que ya hay.
        fprintf(fp, "%s,%s\n", usuario, password); //Esto hay que retocarlo porque está medio meh.

        fclose(fp);
        printf("Enorabuena, ya has creado tu cuenta,¡Disfruta!\n");
    }
    if (buscar_usuario(usuario,password) == USERNAME_ALREADY_EXISTS){
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

        if (buscar_usuario(nombre, contraseña)) {
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
                printf("1. Editar (1)\n");
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
