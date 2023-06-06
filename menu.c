
//
// Created by senyo on 26/4/2023.
//

#include "menu.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>



int datosfichero(User_list* lista) {//Aquí lo que sí hay que pasar como parametro es la estructura de la lista de usuario

    FILE* fp = fopen("C:\\Users\\senyo\\CLionProjects\\EDA2\\Usuarios.txt", "w");
    if (fp == NULL) {
        printf("Error al abrir el archivo.\n");
        return NO_FILE_FOUND;
    }
    User_data *usuario = lista->first;
    while (usuario != NULL) {
        fprintf(fp, "%s %s %s %s %d %d %s %s %s %s %s %f %f %f %d\n", usuario->username, usuario->email, usuario->password, usuario->city, usuario->birth, usuario->user_number, usuario->likes[0],usuario->likes[1], usuario->likes[2], usuario->likes[3], usuario->likes[4], usuario->nota, usuario->nota_max, usuario->nota_min, usuario->num_valoraciones);
        usuario = usuario->next;
    }
    fclose(fp);
    return TRUE;
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
    float nota_maxima, nota_minima;
    int valoraciones;
    if(fscanf(fp, "%s %s %s %s %d %d %s %s %s %s %s %f %f %f %d", nombre_usuario, correo, contraseña, ciudad, &año, &num_usuario, gusto1, gusto2, gusto3, gusto4, gusto5, &nota, &nota_maxima, &nota_minima, &valoraciones) == 15){
        insert_user(lista->first, nombre_usuario, correo, contraseña, ciudad, año, num_usuario, gusto1, gusto2, gusto3, gusto4, gusto5, nota, nota_maxima, nota_minima, valoraciones);
        lista->first->prev = NULL;
        lista->last = lista->first;
        lista->size = 1;//Esto es para el primer elemento de la lista
    } else{
        printf("\nSe ha producido un error al intentar leer el archivo.\n");
    }
    //El while es para el resto de elementos de la lista
    while (fscanf(fp, "%s %s %s %s %d %d %s %s %s %s %s", nombre_usuario, correo, contraseña, ciudad, &año, &num_usuario, gusto1, gusto2, gusto3, gusto4, gusto5, nota) == 12) {//Nombre de usuario, email, contraseña, ciudad, año, num usuario, gustos
        push(lista, nombre_usuario, correo, contraseña, ciudad, año, num_usuario, gusto1, gusto2, gusto3, gusto4, gusto5, nota, nota_maxima, nota_minima, valoraciones);
    }
    fclose(fp);
    return lista;
}

void print_gustos(User_list* lista ,char username[MAX_USERNAME_LENGTH]){
    User_data *user_likes = lista->first;
    while (user_likes->next != NULL) {
        if (strcmp(user_likes->username, username) == 0) {
            for(int i =0; i < 5; i++){
                printf("%d", i, user_likes->likes[i]);
            }
        }
        break;
    }
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
/*
char* cambiar_ciudad(){
    char ciudad[MAX_CITY_NAME];
    while(strlen(ciudad) <= 1) {
        printf("Introduce tu ciudad de residencia \n");
        scanf("%s", ciudad);
    }
    return ciudad;//Aquí hay un warning de que devuelve la dirección de una variable local
}
*/
char* cambiar_nombre_de_usuario(){ // Esta función se va eliminar por nuestra salud mental.
    char usuario[MAX_USERNAME_LENGTH];
    while(strlen(usuario) <= 1) {
        printf("Introduce tu ciudad de residencia \n");//What
        scanf("%s", usuario);
    }
    return usuario;//Aquí hay un warning de que devuelve la dirección de una variable local
}

void create_user(User_list* lista){
    char usuario[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    char email[MAX_EMAIL_LENGTH];
    char ciudad[MAX_CITY_NAME];
    int año = 0;
    int num_usuario = lista->size;//Esto hay que hacerlo, solo he dejado la variable aquí para poder hacer el código
    char gusto1[MAX_LIKE_LENGTH];
    char gusto2[MAX_LIKE_LENGTH];
    char gusto3[MAX_LIKE_LENGTH];
    char gusto4[MAX_LIKE_LENGTH];
    char gusto5[MAX_LIKE_LENGTH];
    int flag = FALSE;
    float nota = 0.0;
    float nota_max = 0.0;
    float nota_min = 5.0;
    int valoraciones = 0;
    while (flag == FALSE){
        printf("Introduzca un nombre de usuario (máximo %d caracteres y mínimo %d).\n",MAX_USERNAME_LENGTH,MIN_USERNAME_LENGTH);
        scanf("%s", usuario);
        if(strlen(usuario) > MIN_USERNAME_LENGTH && strlen(usuario) < MAX_USERNAME_LENGTH) flag = TRUE;
    }
    flag = FALSE;
    while(flag == FALSE){
        printf("\nIntroduzca una contraseña (máximo %d caracteres y mínimo %d).\n",MAX_PASSWORD_LENGTH,MIN_PASSWORD_LENGTH);
        scanf("%s", password);
        if(strlen(password) > MIN_PASSWORD_LENGTH && strlen(password) < MAX_PASSWORD_LENGTH) flag = TRUE;
    }
    if (buscar_usuario(lista, usuario,password) == USER_DOES_NOT_EXIST){


        while(strlen(email) <= 1) {
            printf("Introduce tu email\n");
            scanf("%s", email);
        }
        while (strlen(ciudad) <= 1){
            printf("Introduce tu ciudad de residencia \n");
            scanf("%s", ciudad);
        }

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
        push(lista, usuario, email, password, ciudad, año, num_usuario, gusto1, gusto2, gusto3, gusto4, gusto5, nota, nota_max, nota_min, valoraciones);

        datosfichero(lista);
        return;
    }

    if (buscar_usuario(lista, usuario,password) == USERNAME_ALREADY_EXISTS || buscar_usuario(lista, usuario, password) == USER_ALREADY_EXISTS){
        printf("Lo sentimos, este usuario ya existe\n");
        return;
    }

}



int buscar_usuario(User_list *lista, char username[], char otro[]) {

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
                //printf("El usuario y la contraseña coinciden. Usuario encontrado.\n");
                return USER_ALREADY_EXISTS;
            } else {
                //printf("Contraseña incorrecta.\n");
                return USERNAME_ALREADY_EXISTS;
            }
        } else {
            //printf("El usuario no coincide. Usuario no encontrado.\n");//Quitar los prints de aquí y ponerlos en otro lado porque como usamos esta función en varios sitios se printea cuando no toca
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
    return &arr; //Warning de que el tipo de retorno es disatinto al esperado. Actual: char* Esperado: char**
}



void menu(User_list* lista, timeline* tl) {

    int login, flag = FALSE, nota = -1;
    printf("Hola, Buenos días!\n");
    printf("¿Eres un nuevo usuario(1) o ya tienes cuenta(2)?\n");
    scanf("%d", &login);
    char nombre[MAX_USERNAME_LENGTH], otro[MAX_USERNAME_LENGTH];
    char contraseña[MAX_PASSWORD_LENGTH];
    char ubicacion[MAX_CITY_NAME];
    char sol[2*MAX_POST_LENGHT];
    User_data *other_user;
    while (flag == FALSE) {
        switch (login) {
            case 1:
                create_user(lista);
                strcpy(nombre, lista->last->username);
                break;
            case 2:
                while (flag == FALSE) {
                    printf("Ingresa el nombre de usuario\n");
                    scanf("%s", nombre);
                    printf("Ingresa la contraseña:\n");
                    scanf("%s", contraseña);
                    if (buscar_usuario(lista, nombre, contraseña) == USER_ALREADY_EXISTS) {
                        printf("Inicio de sesión exitoso. ¡Bienvenido!\n");
                        flag = TRUE;
                    } else {
                        printf("El usuario o la contraseña no son correctos. Por favor inténtelo de nuevo.\n");
                    }
                }
                flag = FALSE;
                break;
            default:
                printf("Si eres un nuevo usuario elige (1) y si eres un usuario existente elige (2)\n");
                scanf("%d", &login);
        }
        flag = TRUE;
    }
    char lista_username[lista->size][MAX_USERNAME_LENGTH];
    User_data *actual = lista->first;
    int i = 0;
    flag = FALSE;
    printf("\n----- Menú -----\n");
    printf("1. Perfil (1)\n");
    printf("2. Página principal (2)\n");
    printf("3. Mostrar lista de usuarios (3)\n");
    printf("0. Salir (0) \n");
    printf("Ingresa la opción deseada: \n");

    scanf("%d", &login);
    while (flag == FALSE) {
        switch (login) {
            case 1: //Hay que hacer la parte de las solicitudes de amistad
                printf("\n----- Perfil -----\n");
                printf("1. Editar (1)\n"); // En está parte tendremos que hacer una función que elimine la cuenta si no ve necesario.
                printf("2. Ver valoraciones\n");
                printf("0. Atrás (0) \n");
                printf("Ingresa la opción deseada:\n");
                int opcion;
                scanf("%d", &opcion);
                while (flag == FALSE) {
                    switch (opcion) {
                        case 1:
                            printf("Introduce que dato quieres editar\n");
                            printf("1. Ubicación del usuario (1) \n");
                            printf("2. Cambiar contraseña (2) \n");
                            printf("3. Gustos del usuario (3) \n");
                            printf("0. Volver al menú principal (0) \n");
                            int perfil;
                            scanf("%d", &perfil);
                            while (flag == FALSE) {
                                switch (perfil) {
                                    case 1:
                                        printf("Introduzca la nueva ubicación:\n");
                                        scanf("%s", ubicacion);
                                        strcpy(encontrar_usuario(nombre, lista)->city, ubicacion);
                                        int check = datosfichero(lista);
                                        if (check == NO_FILE_FOUND) {
                                            printf("No se ha podido cambiar la ubicación :(\n");
                                        } else {
                                            printf("Se ha cambiado la ubicación correctamente.\n");
                                        }
                                        break;
                                    case 2:
                                        printf("Introduzca la contraseña actual:\n");
                                        char cont_actual[MAX_PASSWORD_LENGTH];
                                        scanf("%s", cont_actual);
                                        if (strcmp(contraseña, cont_actual) == 0) {
                                            printf("Introduzca la nueva contraseña:\n");
                                            int marcador = FALSE;
                                            while (marcador == FALSE) {
                                                printf("\nIntroduzca una contraseña (máximo %d caracteres y mínimo %d).\n",
                                                       MAX_PASSWORD_LENGTH, MIN_PASSWORD_LENGTH);
                                                scanf("%s", contraseña);
                                                if (strlen(contraseña) > MIN_PASSWORD_LENGTH &&
                                                    strlen(contraseña) < MAX_PASSWORD_LENGTH)
                                                    marcador = TRUE;
                                            }
                                            check = datosfichero(lista);
                                            if (check == NO_FILE_FOUND) {
                                                printf("No se ha podido cambiar la contraseña :(\n");
                                            } else {
                                                printf("Se ha cambiado la contraseña correctamente.\n");
                                            }
                                        } else {
                                            printf("Contraseña incorrecta.\n");
                                        }
                                        break;
                                    case 3:
                                        print_gustos(lista, nombre);
                                        int gustos_cambio;
                                        char gusto[MAX_LIKE_LENGTH];
                                        print_gustos(lista, &nombre);
                                        printf("Intoduzca que gusto desea cambiar (1-5):\n");
                                        scanf("%d", &gustos_cambio);
                                        printf("Intoduzca su nuevo gusto:\n");
                                        scanf("%s", gusto);
                                        strcpy(encontrar_usuario(nombre, lista)->likes[gustos_cambio], gusto);
                                        check = datosfichero(lista);
                                        if (check == NO_FILE_FOUND) {
                                            printf("No se ha podido cambiar el gusto :(\n");
                                        } else {
                                            printf("Se ha cambiado el gusto correctamente.\n");
                                        }
                                        break;
                                    case 0:
                                        flag = TRUE;
                                        break;
                                    default:
                                        printf("Por favor elija una de las opciones disponibles.\n");
                                        scanf("%d", &perfil);
                                }
                            }
                            flag = FALSE;
                            break;
                        case 2:
                            if (encontrar_usuario(nombre, lista)->num_valoraciones == 0){
                                printf("Aún no tienes valoraciones.\n");
                            } else{
                                printf("El resto de usuarios te han valorado con una nota media de: %f\n",
                                       encontrar_usuario(nombre, lista)->nota);
                                printf("La nota más alta que te han dado ha sido un astronómico: %f\n",
                                       encontrar_usuario(nombre, lista)->nota_max);
                                printf("La nota más baja que te han dado ha sido un triste: %f\n",
                                       encontrar_usuario(nombre, lista)->nota_min);
                            }
                            break;
                        case 0:
                            flag = TRUE;
                            break;
                        default:
                            printf("Por favor elija una de las opciones disponibles.\n");
                            scanf("%d", &opcion);
                    }
                }
                flag = FALSE;
                break;
            case 2:
                while(flag == FALSE){
                    int menu;
                    printf("\n----- Menú Principal -----\n");
                    printf("1. Crear una publicación (1)\n");
                    printf("2. Ver publicaciones (2)\n");
                    printf("3. Acceder al perfil de un usuario (3)\n");
                    printf("0. Salir (0) \n");
                    scanf("%d", &menu);
                    switch (menu) {
                        case 1:
                            printf("\nEscribe tu mensaje (tamaño máximo %d caracteres):\n", MAX_POST_LENGHT);
                            fgets(sol, 2*MAX_POST_LENGHT, stdin);
                            while (strlen(sol) > MAX_POST_LENGHT){
                                printf("\nTu mensaje es demasiado largo. Redúcelo en %d caracteres.\n", strlen(sol)-MAX_POST_LENGHT);
                                fgets(sol, 2*MAX_POST_LENGHT, stdin);
                            }
                            push_post(tl, encontrar_usuario(nombre, lista), sol);
                            FILE* f = fopen("C:\\Users\\senyo\\CLionProjects\\EDA2\\posts.txt", "a");
                            fprintf(f, "%s\n", sol);
                            fprintf(f, "%s\n", nombre);
                            fclose(f);
                            break;
                        case 2:
                            printf("Hay que hacerlo");
                            break;
                        case 3:
                            while (flag == FALSE) {
                                printf("Escribe el nombre del usuario que quieras ver.\nSi quieres ver una lista con todos los usarios registrados escribe \"lis\".\n");
                                scanf("%s", otro);
                                if (strcmp(otro, "lis") == 0) {
                                    i = 0;
                                    while (actual != NULL) {
                                        strcpy(lista_username[i], actual->username);
                                        actual = actual->next;
                                        i++;
                                    }
                                    char **lista_ordenada = bubblesort(*lista_username,
                                                                       lista->size); //Warning de que lista_username es un tipo de puntero incompatible
                                    for (int j = 0; j < lista->size; ++j) {
                                        printf("%s\n", lista_ordenada[j]);
                                    }
                                    i = 0;
                                    actual = lista->first;
                                } else {
                                    other_user = encontrar_usuario(otro, lista);
                                    if (other_user == NULL) {
                                        printf("El usuario no existe. Asegúrate que has escrito su nombre de usuario correctamente.\n");
                                    } else {
                                        while (flag == FALSE) {
                                            int usuario;
                                            printf("\n----- Menú Usuario -----\n");
                                            printf("1. Ver datos del usuario (1)\n");
                                            printf("2. Enviar una solicitud de amistad(2)\n");
                                            printf("3. Valorar usuario (3)\n");
                                            printf("4. Ver las publicaciones de este usuario (4)\n");
                                            printf("0. Volver (0)\n");
                                            scanf("%d", &usuario);

                                            switch (usuario) {
                                                case 1:
                                                    printf("\nNombre de usuario: %s\n", other_user->username);
                                                    printf("Email: %s\n", other_user->email);
                                                    printf("Ciudad de residencia: %s\n", other_user->city);
                                                    printf("Año de nacimiento: \n", other_user->birth);
                                                    printf("Gustos: %s\t%s\t%s\t%s\t%s\n", other_user->likes[0], other_user->likes[1], other_user->likes[2], other_user->likes[3], other_user->likes[4]);
                                                    printf("Valoración media: %f\n", other_user->nota);
                                                    break;
                                                case 2:
                                                    printf("Luego la hago\n");
                                                    break;
                                                case 3:
                                                    while (nota < 0 || nota > 5){
                                                        printf("¿Que valoración le das a este usuario?\n");
                                                        scanf("%f", &nota);
                                                    }
                                                    valoracion(other_user, nota);
                                                    break;
                                                case 4:
                                                    while (flag == FALSE){
                                                        int submenu;
                                                        int num_public;
                                                        printf("1. Ver las publicaciones más recientes (1)\n");
                                                        printf("2. Ver las publicaciones más antiguas (2)\n");
                                                        printf("0. Volver (0)\n");
                                                        scanf("%d", &submenu);

                                                        switch (submenu) {
                                                            case 1:
                                                                printf("Selecciona cuantas publicaciones quieres ver (si quieres ver todas escribe \"-1\":\n");
                                                                scanf("%d", &num_public);
                                                                show_recent_posts_from_user(other_user, tl, num_public);
                                                                break;
                                                            case 2:
                                                                printf("Selecciona cuantas publicaciones quieres ver (si quieres ver todas escribe \"-1\":\n");
                                                                scanf("%d", &num_public);
                                                                show_old_posts_from_user(other_user, tl, num_public);
                                                                break;
                                                            case 0:
                                                                flag = TRUE;
                                                                break;
                                                            default:
                                                                printf("Por favor elija una de las opciones disponibles.\n");
                                                        }
                                                    }
                                                    flag = FALSE;
                                                    break;
                                                case 0:
                                                    flag = TRUE;
                                                    break;
                                                default:
                                                    printf("Por favor elija una de las opciones disponibles.\n");
                                            }

                                        }
                                    }
                                }
                            }
                            flag = FALSE;
                            break;
                        case 0:
                            flag = TRUE;
                            break;
                        default:
                            printf("Por favor elija una de las opciones disponibles.\n");

                    }
                }
                flag = FALSE;
                break;
            case 3: //Esto da error
                i = 0;
                while (actual != NULL) {
                    strcpy(lista_username[i], actual->username);
                    actual = actual->next;
                    i++;
                }
                char **lista_ordenada = bubblesort(*lista_username,lista->size); //Warning de que lista_username es un tipo de puntero incompatible
                for (int j = 0; j < lista->size; ++j) {
                    printf("%s\n", &lista_ordenada[j]);
                }
                i = 0;
                actual = lista->first;
                break;
            case 0:
                flag = TRUE;
                break;
            default:
                printf("Por favor elija una de las opciones disponibles.\n");

                printf("\n----- Menú -----\n");
                printf("1. Perfil (1)\n");
                printf("2. Página principal (2)\n");
                printf("3. Mostrar lista de usuarios (3)\n");
                printf("0. Salir (0) \n");
                printf("Ingresa la opción deseada: \n");

                scanf("%d", &login);
        }
    }
}

            /*// Menú con opciones
            int opcion;
            int opcion2;
            int opcion3;
            int num_gustos;
            int gustos_cambio;
            char nombre_usuario;//Esto no es una string
            //Esto tampoco
            char descripcion;//Ni esto
            char gustos[MAX_LIKE_LENGTH];//Esto sí pero probablemente tendría que ser un array de strings
//TODA ESTA MIERDA SEGURAMENTE TENGA QUE ESTAR DENTRO DE UN WHILE
*/
/*
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


                    scanf("%d", &opcion3);// pregunta que quiere cambiar
                    if (opcion3 == 1) {
                        cambiar_nombre_de_usuario();
                    } else if (opcion3 == 2) {
                       // cambiar_ciudad();
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
                        printf("Introduzca que quiere hacer, ver los post de los demas (1) o hacer un post (2):\n");
                        scanf("%d", &elegir_post);
                        if (elegir_post == 1){ //Ver posts
                            show_top(tl);//NO ESTÁ ACABADO
                        }
                        if (elegir_post == 2){ //Escribir un post
                            char sol[2*MAX_POST_LENGHT];
                            printf("\nEscribe tu mensaje (tamaño máximo %d caracteres):\n", MAX_POST_LENGHT);
                            fgets(sol, 2*MAX_POST_LENGHT, stdin);
                            while (strlen(sol) > MAX_POST_LENGHT){
                                printf("\nTu mensaje es demasiado largo. Redúcelo en %d caracteres.\n", strlen(sol)-MAX_POST_LENGHT);
                                fgets(sol, 2*MAX_POST_LENGHT, stdin);
                            }
                            push_post(tl, encontrar_usuario(nombre, lista), sol);
                            FILE* f = fopen("C:\\Users\\senyo\\CLionProjects\\EDA2\\posts.txt", "a");
                            fprintf(f, "%s\n", sol);
                            fprintf(f, "%s\n", nombre);
                        }
                        if (elegir_post == 3){//Ver palabras más usadas.
                            diccionario *total_palabras = contar_palabras(tl);

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

*/