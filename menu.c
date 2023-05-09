//
// Created by senyo on 26/4/2023.
//
#include "main.c"
#include "menu.h"


void buscar_usuario(int algo, int otro){
    User_data* user_search;
    FILE* fp;
    fp = fopen("C:\\Users\\senyo\\CLionProjects\\EDA2\\Usuarios", "r"); //Si queréis escribir en el archivo no lo podéis abriren modo lectura
    while (fp != EOF){


    }

    fscanf(fp, "%s,%s\n", user_search->username, user_search->password); //Esto hay que retocarlo porque está medio meh.
    fclose(fp);
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



    if(login == 2){

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
