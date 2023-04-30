//
// Created by senyo on 26/4/2023.
//
#include "main.c"
#include "menu.h"



void  menu() {

    int login = -1;
    printf("Hola, Buenos días!\n");
    printf("¿Eres un nuevo usuario(1) o ya tienes cuenta(2)?\n");
    while (login != 1 && login != 2) {
        scanf("%d", login);
        printf("\nPor favor seleccione 1 si es un nuevo usuario o 2 si ya tiene una cuenta.\n");
    }

    if (login == 1) create_user();

    }

    if(login == 2){

        User_data user_search;
        printf("Ingresa el nombre de usuario\n");
        scanf("%s", user_search.username);
        printf("Ingresa la contraseña:\n");
        scanf("%s", user_search.password);
        buscar_usuario(user_search.username,user_search.password);

    }

}

void buscar_usuario(){
    User_data* user_search;
    FILE* fp;
    fp = fopen("C:\\Users\\senyo\\CLionProjects\\EDA2\\Usuarios", "r"); //Si queréis escribir en el archivo no lo podéis abriren modo lectura
    while (fp != EOF){


    }

    fscanf(fp, "%s,%s\n", user_search->username, user_search->password); //Esto hay que retocarlo porque está medio meh.
    fclose(fp);
}

void create_user(){
    
    FILE* fp;
    fp = fopen("C:\\Users\\senyo\\CLionProjects\\EDA2\\Usuarios", "w"); //Si queréis escribir en el archivo no lo podéis abriren modo lectura
    while (fp != EOF){


    }

    fscanf(fp, "%s,%s\n", user_search->username, user_search->password); //Esto hay que retocarlo porque está medio meh.
    fclose(fp);
}


}



