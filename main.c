#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

User_data* encontrar_usuario(char username[], User_list* lista) {
    User_data* elemento = lista->first;
    while (elemento != NULL) {
        if (strcmp(username, elemento->username) == 0) {
            return elemento;
        }
        elemento = elemento->next;
    }
    return NULL;
}

timeline* leer_posts(User_list* lista){
    FILE* fd = fopen("/Users/naiara/CLionProjects/EDA2/posts.txt", "r");//Esto tendría que poner posts, pero si pongo posts no se inicia el programa.
    if (fd == NULL){
        printf("\nError al abrir el archivo de posts.\n");
        return NULL;
    }
    char user[MAX_USERNAME_LENGTH];
    char post[MAX_POST_LENGHT];
    timeline* tl = (timeline *) malloc(sizeof(timeline));
    tl->first = (publicacion *) malloc(sizeof(publicacion));
    if(fscanf(fd, " %[^\n]", post) != 0){
        //En el archivo hay un enter depués del post y la siguiente línea es el usuario
        fscanf(fd, "%s", user);
        insert_post(tl->first, user, post);
        tl->first->prev = NULL;
        tl->last = tl->first;
        tl->size = 1;
    }
    //Usar fgets
    while (!feof(fd)){
        fscanf(fd, " %[^\n]", post);
        fscanf(fd, "%s", user);
        push_post(tl, user, post);
    }
    fclose(fd);
    return tl;
}

void cargar_solicitudes_amistad(User_list* lista) {
    FILE* fp = fopen("/Users/naiara/CLionProjects/EDA2/amistad.txt", "r");
    if (fp == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    char solicitante[MAX_USERNAME_LENGTH];
    char solicitado[MAX_USERNAME_LENGTH];

    while (fscanf(fp, "%s %s", solicitante, solicitado) == 2) {
        // Agregar la solicitud de amistad a la estructura de datos
        User_data* usuarioActual = encontrar_usuario(solicitante, lista);
        User_data* usuarioDestino = encontrar_usuario(solicitado, lista);

        if (usuarioActual != NULL && usuarioDestino != NULL) {
            if (usuarioDestino->solicitudes == NULL) {
                usuarioDestino->solicitudes = (Queue*)malloc(sizeof(Queue));
                initQueue(usuarioDestino->solicitudes);
            }

            enqueueRequest(usuarioDestino->solicitudes, solicitante, solicitado);
        }
    }

    fclose(fp);
}



void init_amigos(User_list *lista){
    User_data *actual = lista->first;
    while (actual != NULL){
        for (int i = 0; i < MAX_AMIGOS; ++i) {
            strcpy(actual->amigos[i], " ");
        }
        actual = actual->next;
    }
}

void cargar_amigos(User_list *lista){
    FILE *fp = fopen("C:\\Users\\senyo\\CLionProjects\\EDA2\\amigos.txt", "r");
    if (fp == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }
    User_data *bueno;
    char fila[MAX_USERNAME_LENGTH*MAX_AMIGOS+MAX_AMIGOS+1];
    char delimitador[] = " ";
    while (!feof(fp)){
        int i = 0;
        fgets(fila, MAX_USERNAME_LENGTH*MAX_AMIGOS+MAX_AMIGOS+1, fp);
        char *palabra = strtok(fila, delimitador);
        if (palabra != NULL){
            bueno = encontrar_usuario(palabra, lista);
            palabra = strtok(NULL, delimitador);
            while (palabra != NULL){
                strcpy(bueno->amigos[i], palabra);
                i++;
                palabra = strtok(NULL, delimitador);
            }
        }
    }
}
/*
notificaciones *init_queue(){
    notificaciones *cola = (notificaciones *) malloc(sizeof(notificaciones));
    cola->front = -1;
    cola->rear = -1;
    for (int i = 0; i < MAX_NOTIFICACIONES; ++i) {
        strcpy(cola->notif[i], " ");
    }
    return cola;
}*/

int main() {
    User_list* lista = ficherodatos();//Cargamos lo que está en el fichero de usuarios al empezar
    timeline* tl = leer_posts(lista);//Cargamos todos los posts
    cargar_solicitudes_amistad(lista);
    init_amigos(lista);
    cargar_amigos(lista);
    // notificaciones *cola = init_queue();
    menu(lista, tl);//Antes del menú hay que cargar las cosas
}