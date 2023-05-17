
//
// Created by senyo on 26/4/2023.
//
#include "main.c"
#include "menu.h"
#include <string.h>
#include <stdlib.h>

int print_gustos(User_list* lista ,char username[MAX_USERNAME_LENGTH]){
    User_data *user_likes = lista->first;
    while (user_likes->next != NULL) {
        if (strcmp(user_likes->username, username) == 0) {
            for(int i =0; i < 5; i++){
                printf("%d",i,user_likes->likes[i]);
            }
        }
        break;
    }
}

//Con esta función también lo haría con la estructura y no con el archivo
void guardar_gustos(User_list* lista,char username[MAX_USERNAME_LENGTH],char gustos[MAX_LIKE_LENGTH],int numero){ //No está revisado si esta función tiene sentido o.
    User_data *user_likes = lista->first;
    while (user_likes->next != NULL) { //Yo esto no lo haría buscando en el fichero si no mejor buscando en la lista
        if (strcmp(user_likes->username, username) == 0) { //Creo, no estoy seguro, pero  a esto creo que le falta cosa.
            strncpy(user_likes -> likes[numero] ,gustos,MAX_LIKE_LENGTH);
            user_likes = user_likes->next;
            return;
        }
    }
}

char* cambiar_ciudad(){
    char ciudad[MAX_CITY_NAME];
    while(strlen(ciudad) <= 1) {
        printf("Introduce tu ciudad de residencia \n");
        scanf("%s", ciudad);
    }
    return ciudad;
}
//Esto ahora mismo no sirve para nada
/*char** cambiar_gustos(char nombre_usuario[MAX_USERNAME_LENGTH],int num_gustos){

    char ** gustos = malloc(num_gustos *sizeof (char*));
    for (int i = 0; i <  num_gustos; i++) {
        printf("Introduce el gusto numero %d\n", i+1);
        scanf("%s", gustos[i] = malloc(MAX_LIKE_LENGTH * sizeof (char))); // Se tiene que repetir de 1 a 5 veces.
        if ((&nombre_usuario,&gustos[i]) == TRUE) guardar_gustos(&nombre_usuario,&gustos[i]);
    }
}*/

char* cambiar_nombre_de_usuario(){
    char usuario[MAX_USERNAME_LENGTH];
    while(strlen(usuario) <= 1) {
    printf("Introduce tu ciudad de residencia \n");//What
    scanf("%s", usuario);
    }
    return usuario;
}


void limpiar_User_data(User_data* guardar){

    if(guardar == NULL){
        return;
    }
    free(guardar->email);
    free(guardar->password);
    free(guardar->username);
    free(guardar->city);
    guardar->user_number = 0 ;
    guardar->birth = 0;
    for (int i = 0; i < MAX_LIKE_LENGTH; i++) {
       free(guardar->likes[i]);
    }

    free(guardar);
}
void borrar_lista_de_usuarios(User_list* lista) {

    if (lista == NULL) {
        return;
    }
    User_data* actual = lista->first;
    User_data* siguiente = NULL;

    while(actual!= NULL){
        limpiar_User_data(actual);
        actual = actual->next;

    }
    lista->first = NULL;
    lista->last = NULL;
    lista->size = 0 ;
}


void create_user(User_list* lista){
    char usuario[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    char email[MAX_EMAIL_LENGTH];
    int año = 0;
    int num_usuario = lista->size;//Esto hay que hacerlo, solo he dejado la variable aquí para poder hacer el código
    char gusto1[MAX_LIKE_LENGTH];
    char gusto2[MAX_LIKE_LENGTH];
    char gusto3[MAX_LIKE_LENGTH];
    char gusto4[MAX_LIKE_LENGTH];
    char gusto5[MAX_LIKE_LENGTH];
    int flag = FALSE;
    float nota = 0.0;
    while (flag == FALSE){
        printf("Introduzca un nombre de usuario (máximo", MAX_USERNAME_LENGTH, "caracteres y mínimo", MIN_USERNAME_LENGTH, ").\n");
        scanf("%s", usuario);
        if(strlen(usuario) > MIN_USERNAME_LENGTH && strlen(usuario) < MAX_USERNAME_LENGTH) flag = TRUE;
    }
    flag = FALSE;
    while(flag == FALSE){
        printf("\nIntroduzca una contraseña (máximo", MAX_PASSWORD_LENGTH, "caracteres y mínimo", MIN_PASSWORD_LENGTH, ").\n");
        scanf("%s", password);
        if(strlen(password) > MIN_PASSWORD_LENGTH && strlen(password) < MAX_PASSWORD_LENGTH) flag = TRUE;
    }
    if (buscar_usuario(lista, usuario,password) == USER_DOES_NOT_EXIST){


        while(strlen(email) <= 1) {
            printf("Introduce tu email\n");
            scanf("%s", email);
        }
        char *ciudad = cambiar_ciudad();

        while( año <= 1920 || año > 2023) {
            printf("Introduce tu año de nacimiento\n");
            scanf("%d", &año);
        }

        while(strlen(gusto1) <= 1) {
            printf("Dinos algo que te guste:\n");
            scanf("%s", gusto1);
        }
        while(strlen(gusto2) <= 1) {
            printf("Dinos algo que te guste:\n");
            scanf("%s", gusto2);
        }
        while(strlen(gusto3) <= 1) {
            printf("Dinos algo que te guste:\n");
            scanf("%s", gusto3);
        }
        while(strlen(gusto4) <= 1) {
            printf("Dinos algo que te guste:\n");
            scanf("%s", gusto4);
        }
        while(strlen(gusto5) <= 1) {
            printf("Dinos algo que te guste:\n");
            scanf("%s", gusto5);
        }

        push(lista, usuario, email, password, ciudad, año, num_usuario, gusto1, gusto2, gusto3, gusto4, gusto5, nota);
        datosfichero(lista);
        return;
    }

    if (buscar_usuario(lista, usuario,password) == USERNAME_ALREADY_EXISTS || buscar_usuario(lista, usuario, password) == USER_ALREADY_EXISTS){
        printf("Lo sentimos, este usuario ya existe\n");
        return;
    }

}



int buscar_usuario(User_list *lista, char username[MAX_USERNAME_LENGTH], char otro[MAX_PASSWORD_LENGTH]) {

    int usuarioEncontrado = FALSE;
    int contraseñaEncontrada = FALSE;
    User_data *current = lista->first;
    if (strcmp(username, current->username) == 0) {
        usuarioEncontrado = TRUE;
        if (strcmp(otro, current->password) == 0) {
            contraseñaEncontrada = TRUE;
        }
    }
    if (usuarioEncontrado == FALSE){
        while (current->next != NULL){
            if (strcmp(username, current->next->username) == 0){
                usuarioEncontrado = TRUE;
                if (strcmp(otro, current->next->password) == 0){
                    contraseñaEncontrada = TRUE;
                }
                break;
            }
            current = current->next;
        }
    }


        if (usuarioEncontrado == TRUE) {
            if (contraseñaEncontrada == TRUE){
                printf("El usuario y la contraseña coinciden. Usuario encontrado.\n");
                return USER_ALREADY_EXISTS;
            } else {
                printf("Contraseña incorrecta.\n");
                return USERNAME_ALREADY_EXISTS;
            }
        } else {
            printf("El usuario no coincide. Usuario no encontrado.\n");
            return USER_DOES_NOT_EXIST;
        }
}

void bubblesort(char arr[], int n){

}

void  menu(User_list* lista) {

    int login = -1;
    printf("Hola, Buenos días!\n");
    printf("¿Eres un nuevo usuario(1) o ya tienes cuenta(2)?\n");
    while (login != 1 && login != 2) {
        scanf("%d", &login);
        printf("\nPor favor seleccione 1 si es un nuevo usuario o 2 si ya tiene una cuenta.\n");
    }

    if (login == 1) create_user(lista);


    if (login == 2) {

        char nombre[MAX_PASSWORD_LENGTH];
        char contraseña[MAX_PASSWORD_LENGTH];
        printf("Ingresa el nombre de usuario\n");
        scanf("%s", nombre);
        printf("Ingresa la contraseña:\n");
        scanf("%s", contraseña);
        buscar_usuario(lista, nombre, contraseña);//Hay que juntar esto con lo de abajo y hacer un while por si se equivoca al iniciar sesión pueda volver a intentarlo

        if (buscar_usuario(lista, nombre, contraseña) == USER_ALREADY_EXISTS) {
            printf("Inicio de sesión exitoso. ¡Bienvenido!\n");

            // Menú con opciones
            int opcion;
            int opcion2;
            int opcion3;
            int num_gustos;
            int gustos_cambio;
            char nombre_usuario;
            char ubicacion;
            char descripcion;
            char gustos[MAX_LIKE_LENGTH];
//TODA ESTA MIERDA SEGURAMENTE TENGA QUE ESTAR DENTRO DE UN WHILE

            printf("\n----- Menú -----\n");
            printf("1. Perfil (1)\n");
            printf("2. Página principal (2)\n");
            printf("3. Mostrar lista de usuarios (3)\n");
            printf("0. Salir (0) \n");
            printf("Ingresa la opción deseada: ");
            scanf("%d", &opcion);

            if (opcion == 0) {

            }
            if (opcion == 1) {//Entrar al perfil
                printf("\n----- Perfil -----\n");
                printf("1. Editar (1)\n"); // En está parte tendremos que hacer una función que elimine la cuenta si no ve necesario.
                printf("2. Ver valoraciones\n");
                printf("0. Atrás (0) \n");
                printf("Ingresa la opción deseada: ");
                scanf("%d", &opcion2);

                if (opcion2 == 0) {

                }
                if (opcion2 == 1) {
                    printf("Introduce que dato quieres editar\n");
                    printf("1. nombre del usuario: \n");
                    printf("2. ubicación del usuario: \n");
                    printf("3. descripción del usuario: \n");
                    printf("4. gustos del usuario: \n");

                    scanf("%d", &opcion3);// pregunta que quiere cambiar
                    if (opcion3 == 1) {
                        cambiar_nombre_de_usuario();
                    } else if (opcion3 == 2) {
                        cambiar_ciudad();
                    } else if (opcion3 == 3) {
                        printf("Introduce una descripción:\n");
                        scanf("%d", &descripcion);
                    } else if (opcion3 == 4) {
                        print_gustos(lista,&nombre_usuario);
                        printf("Intoduzca cuantos gustos desea cambiar (1-5)");
                        scanf("%d", num_gustos);
                        for (int i = 0;i < num_gustos;i ++){
                            print_gustos(lista,&nombre_usuario);
                            printf("Intoduzca que gusto desea cambiar (1-5)");
                            scanf("%d",gustos_cambio);
                            printf("Intoduzca su nuevo gusto %d",i);
                            scanf("%s", gustos[gustos_cambio]);
                            guardar_gustos(lista,&nombre_usuario, &gustos[gustos_cambio],gustos_cambio);
                        }
                        if (opcion2 == 2) {

                        }

                    }

                    if (opcion == 2) { //Menú principal
                        int elegir_post = 0;
                        printf("Introduzca que quiere hacer, ver los post de los demas (1) o hacer un post (2)");
                        scanf("%d",elegir_post);
                        if (elegir_post == 1){
                            //Para los posts no se usara scanf, sino fgets("post",MAX_POST_LENGHT,stdi);
                            char post[MAX_POST_LENGHT];
                            FILE* fd;
                            fscanf("%s",&post[MAX_POST_LENGHT],"r");

                        }
                        if (elegir_post == 2){

                        }



                    }

                    if (opcion == 3){//Mostrar la lista de usuarios
                        char lista_username[lista->size][MAX_USERNAME_LENGTH];
                        User_data* actual = lista->first;
                        int i = 0;
                        while (actual != NULL){
                            strcpy(lista_username[i], actual->username);
                            actual = actual->next;
                            i++;
                        }
                    }
                }
            }
        }
    }
}