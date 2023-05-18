
//
// Created by senyo on 26/4/2023.
//

#include "menu.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void insert_user(User_data* miembro, char nombre_usuario[MAX_USERNAME_LENGTH], char correo[MAX_EMAIL_LENGTH], char contraseña[MAX_PASSWORD_LENGTH], char ciudad[MAX_CITY_NAME], int año, int num_usuario, char gusto1[MAX_LIKE_LENGTH], char gusto2[MAX_LIKE_LENGTH], char gusto3[MAX_LIKE_LENGTH], char gusto4[MAX_LIKE_LENGTH], char gusto5[MAX_LIKE_LENGTH], float nota){
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
    miembro->nota = nota;
    miembro->next = NULL;
}

void push(User_list* lista, char nombre_usuario[MAX_USERNAME_LENGTH], char correo[MAX_EMAIL_LENGTH], char contraseña[MAX_PASSWORD_LENGTH], char ciudad[MAX_CITY_NAME], int año, int num_usuario, char gusto1[MAX_LIKE_LENGTH], char gusto2[MAX_LIKE_LENGTH], char gusto3[MAX_LIKE_LENGTH], char gusto4[MAX_LIKE_LENGTH], char gusto5[MAX_LIKE_LENGTH], float nota) {
    User_data *usuario = lista->first;
    while (usuario->next != NULL) {
        usuario = usuario->next;
    }

    usuario->next = (User_data *) malloc(sizeof(User_data));
    //Aquí van todos los datos
    insert_user(usuario->next, nombre_usuario, correo, contraseña, ciudad, año, num_usuario, gusto1, gusto2, gusto3, gusto4, gusto5, nota);
    lista->last = usuario->next;
    usuario->next->prev = usuario;
    lista->size++;
}

int datosfichero(User_list* lista) {//Aquí lo que sí hay que pasar como parametro es la estructura de la lista de usuario


    FILE * fp = fopen("C:\\Users\\senyo\\CLionProjects\\EDA2\\Usuarios", "w");
    if (fp == NULL) {
        printf("Error al abrir el archivo.\n");
        return NO_FILE_FOUND;

    }
    User_data *usuario = lista->first;
    while (usuario->next != NULL) {
        usuario = usuario->next;
        fprintf(fp, "%s %s %s %s %d %d %s %s %s %s %s %f\n", usuario->username, usuario->email, usuario->password, usuario->city, usuario->birth, usuario->user_number, usuario->likes[0],usuario->likes[1], usuario->likes[2], usuario->likes[3], usuario->likes[4], usuario->nota);
    }
    fclose(fp);
}

User_list* ficherodatos() { //A la que hay algo en el archivo esto se muere (YA NO)
    FILE *fp;
    fp = fopen("C:\\Users\\senyo\\CLionProjects\\EDA2\\Usuarios.txt", "r");//Esto habría que cambiarlo para que se pudiera abrir en cualquier ordenador
    if (fp == NULL) {
        printf("Error al abrir el archivo.\n");
        return  NULL;
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
    float nota;
    if(fscanf(fp, "%s %s %s %s %d %d %s %s %s %s %s %f", nombre_usuario, correo, contraseña, ciudad, &año, &num_usuario, gusto1, gusto2, gusto3, gusto4, gusto5, &nota) == 12){
        insert_user(lista->first, nombre_usuario, correo, contraseña, ciudad, año, num_usuario, gusto1, gusto2, gusto3, gusto4, gusto5, nota);
        lista->last = lista->first;
        lista->first->prev = NULL;
        lista->size = 1;//Esto es para el primer elemento de la lista
    } else{
        printf("\nSe ha producido un error al intentar leer el archivo.\n");
    }
    //El while es para el resto de elementos de la lista
    while (fscanf(fp, "%s %s %s %s %d %d %s %s %s %s %s", nombre_usuario, correo, contraseña, ciudad, &año, &num_usuario, gusto1, gusto2, gusto3, gusto4, gusto5, nota) == 12) {//Nombre de usuario, email, contraseña, ciudad, año, num usuario, gustos
        push(lista, nombre_usuario, correo, contraseña, ciudad, año, num_usuario, gusto1, gusto2, gusto3, gusto4, gusto5, nota);
    }
    return lista;
}

void print_gustos(User_list* lista ,char username[MAX_USERNAME_LENGTH]){
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
    return ciudad;//Aquí hay un warning de que devuelve la dirección de una variable local
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
    return usuario;//Aquí hay un warning de que devuelve la dirección de una variable local
}


void limpiar_User_data(User_data* guardar){

    if(guardar == NULL){
        return;
    }
    free(guardar->email);//Warnings en todos los free por algo del offset
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
        printf("Introduzca un nombre de usuario (máximo MAX_USERNAME_LENGTH caracteres y mínimo MIN_USERNAME_LENGTH).\n");
        scanf("%s", usuario);
        if(strlen(usuario) > MIN_USERNAME_LENGTH && strlen(usuario) < MAX_USERNAME_LENGTH) flag = TRUE;
    }
    flag = FALSE;
    while(flag == FALSE){
        printf("\nIntroduzca una contraseña (máximo MAX_PASSWORD_LENGTH caracteres y mínimo MIN_PASSWORD_LENGTH).\n");
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

char** bubblesort(char arr[], int n){
    int i, j;
    char string[MAX_USERNAME_LENGTH];
    for(i=0;i<n;i++){
        for(j=i+1;j<n;j++){
            if(strcmp(&arr[i], &arr[j])>0){
                strcpy(string,&arr[i]);
                strcpy(&arr[i],&arr[j]);
                strcpy(&arr[j],string);
            }
        }
    }
    return arr; //Warning de que el tipo de retorno es disatinto al esperado. Actual: cahr* Esperado: char**
}

void  menu(User_list* lista) {

    int login = -1;
    printf("Hola, Buenos días!\n");
    printf("¿Eres un nuevo usuario(1) o ya tienes cuenta(2)?\n");
    scanf("%d", &login);
    while (login != 1 && login != 2) {
        printf("\nPor favor seleccione 1 si es un nuevo usuario o 2 si ya tiene una cuenta.\n");
        scanf("%d", &login);
    }

    if (login == 1) create_user(lista);


    if (login == 2) {

        char nombre[MAX_PASSWORD_LENGTH];
        char contraseña[MAX_PASSWORD_LENGTH];
        printf("Ingresa el nombre de usuario\n");
        scanf("%s", nombre);
        printf("Ingresa la contraseña:\n");
        scanf("%s", contraseña);
        //buscar_usuario(lista, nombre, contraseña);//Hay que juntar esto con lo de abajo y hacer un while por si se equivoca al iniciar sesión pueda volver a intentarlo

        if (buscar_usuario(lista, nombre, contraseña) == USER_ALREADY_EXISTS) {
            printf("Inicio de sesión exitoso. ¡Bienvenido!\n");

            // Menú con opciones
            int opcion;
            int opcion2;
            int opcion3;
            int num_gustos;
            int gustos_cambio;
            char nombre_usuario;//Esto no es una string
            char ubicacion;//Esto tampoco
            char descripcion;//Ni esto
            char gustos[MAX_LIKE_LENGTH];//Esto sí pero probablemente tendría que ser un array de strings
//TODA ESTA MIERDA SEGURAMENTE TENGA QUE ESTAR DENTRO DE UN WHILE

            printf("\n----- Menú -----\n");
            printf("1. Perfil (1)\n");
            printf("2. Página principal (2)\n");
            printf("3. Mostrar lista de usuarios (3)\n");
            printf("0. Salir (0) \n");
            printf("Ingresa la opción deseada: \n");
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
                        print_gustos(lista, &nombre_usuario);
                        printf("Intoduzca cuantos gustos desea cambiar (1-5)");
                        scanf("%d", num_gustos);
                        for (int i = 0; i < num_gustos; i++) {
                            print_gustos(lista, &nombre_usuario);
                            printf("Intoduzca que gusto desea cambiar (1-5)");
                            scanf("%d", gustos_cambio);
                            printf("Intoduzca su nuevo gusto %d", i);
                            scanf("%s", gustos[gustos_cambio]);
                            guardar_gustos(lista, &nombre_usuario, &gustos[gustos_cambio], gustos_cambio);
                        }
                        if (opcion2 == 2) {

                        }

                    }
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
                            fscanf("%s",&post[MAX_POST_LENGHT],"r"); //Aquí hay un warning de que el fscanf está mal
                            //Este fscanf está haciendo que hay un warning también la libreria de stdio.h
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
                        char** lista_ordenada = bubblesort(lista_username, lista->size); //Warning de que lista_username es un tipo de puntero incompatible
                        for (int j = 0; j < lista->size; ++j) {
                            printf("%s\n", &lista_ordenada[j]);
                        }
                    }
                }
            }
        }

