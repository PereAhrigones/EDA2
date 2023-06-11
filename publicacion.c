//
// Created by senyo on 29/5/2023.
//

#include "publicacion.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
/*
void enqueue(char mensaje[], notificaciones* lista){
    if ((lista->rear == MAX_NOTIFICACIONES-1 && (lista->front == -1 || lista->front == 0)) || (lista->rear == lista->front-1)){
        printf("Overflow \n");
    } else{
        if (lista->front == -1) lista->front = 0;
        lista->rear++;
        if(lista->rear == MAX_NOTIFICACIONES) lista->rear = 0;
        strcpy(lista->notif[lista->rear], mensaje);
    }
}

void dequeue(notificaciones* lista){//Falta esto
    if(lista->front == -1 || lista->front == lista->rear){
        printf("Underflow \n");
        return;
    } else{
        printf("%s\n", lista->notif[lista->front]);
        lista->front++;
    }
}

void show(notificaciones* lista){//Falta el salto del fin del array al inicio
    if(lista->front == -1){
        printf("No hay notificaciones.\n");
    } else{
        printf("Notificaciones:\n");
        for (int i = lista->front; i < lista->rear; ++i) {
            printf("%s\n", lista->notif[i]);
        }
    }
}

int isEmpty(notificaciones* lista){//Falta poner si se ha vaciado
    if(lista->front == -1 && lista->rear == -1) return TRUE;
    else return FALSE;
}

int isFull(notificaciones* lista){//Falta comprobar.
    if (lista->front == lista->rear) return TRUE;
    else return FALSE;
}
*/

//Función que escribe las publicaciones en su archivo
int postsfichero(timeline *tl){
    FILE *fp = fopen("/EDA2/posts.txt", "w");
    if (fp == NULL){
        printf("Error al abrir el archivo.\n");
        return NO_FILE_FOUND;
    }
    publicacion *post = tl->first;
    while (post != NULL){
        fprintf(fp, "%s\n", post->contenido);
        fprintf(fp, "%s\n", post->username);
        post = post->next;
    }
    fclose(fp);
    return TRUE;
}

//Función que añade los datos principales de una publicación.
void insert_post(publicacion* publ, char user[], char post[]){
    strcpy(publ->username, user);
    strcpy(publ->contenido, post);
    publ->next = NULL;
    publ->prev = NULL;
}

//Función que añade una publicación al final de la lista
void push_post(timeline* tl, char user[], char post[]){
    publicacion *publi = (publicacion*) malloc(sizeof(publicacion));
    insert_post(publi, user, post);
    if (tl->first == NULL){
        tl->first = publi;
        tl->last = publi;
    } else{
        publi->prev = tl->last;
        tl->last->next = publi;
        tl->last = publi;
    }
}

//Función que iba a ser para ordenar las palabras más usadas en las publicaciones usando bubblesort.
void bubblesort_dictionary(diccionario* dict[], int n) {
    int i, j;
    diccionario *temp;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (dict[j]->counter > dict[j+1]->counter) {
                // Intercambiar los elementos si están en el orden incorrecto
                temp = dict[j];
                dict[j] = dict[j +1];
                dict[j+1] = temp;
            }
        }
    }
}

//Función que asigna memoria al diccionario
diccionario **dictAlloc() {
    return malloc(sizeof(diccionario));
}

//FUnción que desasigna memoria a un usuario
void dictDealloc(diccionario **dict) {
    free(dict);
}

//Función que devuelve cuantas veces se ha usado ya esa palabra
int getItem(diccionario *dict, char *key) {
    diccionario *ptr;
    for (ptr = dict; ptr != NULL; ptr = ptr->next) {
        if (strcmp(ptr->key, key) == 0) {
            return ptr->counter;
        }
    }

    return ITEM_NOT_FOUND; //Devuelve 0
}

//Función que elimina un elemento del diccionario
void delItem(diccionario **dict, char *key) {
    diccionario *ptr, *prev;
    for (ptr = *dict, prev = NULL; ptr != NULL; prev = ptr, ptr = ptr->next) {
        if (strcmp(ptr->key, key) == 0) {
            if (ptr->next != NULL) {
                if (prev == NULL) {
                    *dict = ptr->next;
                } else {
                    prev->next = ptr->next;
                }
            } else if (prev != NULL) {
                prev->next = NULL;
            } else {
                *dict = NULL;
            }

            free(ptr->key);
            free(ptr);

            return;
        }
    }
}

//Función que añade un elemento al diccionario
void addItem(diccionario **dict, char *key, int value) {
    delItem(dict, key); /* If we already have an item with this key, delete it. */
    diccionario *d = malloc(sizeof(diccionario));
    d->key = malloc(strlen(key)+1);
    strcpy(d->key, key);
    d->counter = value;
    d->next = *dict;
    *dict = d;
}

//Función que debería servir para contar las palabras, pero que aunque funciona durante un rato acaba petando antes de leer todas las publicaciones.
diccionario *contar_palabras(timeline *tl, int *numero_palabras){
    publicacion *actual;
    diccionario **dict = dictAlloc();
    numero_palabras = 0;
    char copia[MAX_POST_LENGHT];
    char delimitador[] = ",.:;()/!¡?¿&·\"\\^*[]{}+-¬@#ºª<>%€'= "; //Si alguien encuentra algún símbolo que falta que lo ponga. NO BORRÉIS NADA DE LO QUE YA ESTÁ
    for(actual=tl->first; actual != NULL; actual = actual->next){
        strcpy(copia, actual->contenido);
        /*char copia_2[MAX_POST_LENGHT];
        strcpy(copia_2,copia);*/
        /*
        for (int i = 0; strlen(copia);i++){
            copia_2[i] = tolower(copia_2[i]);
        }
        strcpy(copia,copia_2);*/
        char *palabra = strtok(copia, delimitador);
        if(palabra != NULL){
            while (palabra != NULL){//Muere aquí después de unas cuantas publicaciones.
                if (strcmp(palabra, "\n") == 0) break;
                if (getItem(*dict, palabra) == 0){
                    numero_palabras++;
                }
                addItem(dict, palabra, getItem(*dict, palabra)+1);
                palabra = strtok(NULL, delimitador);
            }
        }
    }
    return *dict;
}

//Función que se iba a usar para crear un array con los elementos del diccionario
diccionario *create_array_dict(diccionario *dict, int tamaño){
    diccionario *array[tamaño];
    for (int i = 0; i < tamaño; ++i) {
        array[i] = dict;
        dict = dict->next;
    }
    return *array;
}

//Función que muestra la última publicacion de un usuario
void show_last_post_from_user(char user[], timeline* tl) {
    publicacion *post = tl->first;
    publicacion *lastPost = NULL;

    while (post != NULL) {
        if (strcmp(user, post->username) == 0) {
            lastPost = post;
        }
        post = post->next;
    }

    if (lastPost != NULL) {
        printf("%s\n", lastPost->contenido);
        printf("- %s\n\n", lastPost->username);
    }
}


//Función que muestra la primera publicación del usuario
void show_old_posts_from_user(char user[], timeline* tl) {
    publicacion *post = tl->first;
    while (post != NULL) {
        if (strcmp(user, post->username) == 0) {
            if (post->next != NULL) {
                printf("%s\n", post->contenido);
                printf("- %s\n\n", post->username);


            }
        }
        post = post->next;
    }
}
