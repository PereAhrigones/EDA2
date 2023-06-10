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
int postsfichero(timeline *tl){
    FILE *fp = fopen("C:\\Users\\senyo\\CLionProjects\\EDA2\\posts.txt", "w");
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

void insert_post(publicacion* publ, char user[], char post[]){
    strcpy(publ->username, user);
    strcpy(publ->contenido, post);
    publ->next = NULL;
    publ->prev = NULL;
}


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

void pop_post(timeline* tl){
    tl->last->prev->next = NULL;
    tl->size--;
}

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

void show_top(timeline* tl){
    printf("\n%s\n", tl->last->contenido);
    printf("- %s\n\n", tl->last->username);
}

diccionario **dictAlloc() {
    return malloc(sizeof(diccionario));
}

void dictDealloc(diccionario **dict) {
    free(dict);
}

int getItem(diccionario *dict, char *key) {
    diccionario *ptr;
    for (ptr = dict; ptr != NULL; ptr = ptr->next) {
        if (strcmp(ptr->key, key) == 0) {
            return ptr->counter;
        }
    }

    return ITEM_NOT_FOUND; //Devuelve 0
}

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

//Esta función hay que cambiarla un poco para que se ajuste a lo que queremos
void addItem(diccionario **dict, char *key, int value) {
    delItem(dict, key); /* If we already have an item with this key, delete it. */
    diccionario *d = malloc(sizeof(diccionario));
    d->key = malloc(strlen(key)+1);
    strcpy(d->key, key);
    d->counter = value;
    d->next = *dict;
    *dict = d;
}

diccionario *contar_palabras(timeline *tl, int *numero_palabras){
    publicacion *actual;
    printf("Prueba1\n");
    diccionario **dict = dictAlloc();
    printf("Prueba2\n");
    numero_palabras = 0;
    char copia[MAX_POST_LENGHT];
    char delimitador[] = "\n,.:;()/!¡?¿&·\"\\^*[]{}+-¬@#ºª<>%€'= "; //Si alguien encuentra algún símbolo que falta que lo ponga. NO BORRÉIS NADA DE LO QUE YA ESTÁ
    printf("Prueba3\n");
    for(actual=tl->first; actual != NULL; actual = actual->next){
        printf("Prueba I\n");
        strcpy(copia, actual->contenido);
        /*char copia_2[MAX_POST_LENGHT];
        strcpy(copia_2,copia);*/
        printf("Prueba II\n");
        /*
        for (int i = 0; strlen(copia);i++){
            copia_2[i] = tolower(copia_2[i]);
        }
        strcpy(copia,copia_2);*/
        printf("Prueba III\n");
        char *palabra = strtok(copia, delimitador);
        printf("Más pruebas\n");
        if(palabra != NULL){
            printf("Más pruebas 1\n");
            while (palabra != NULL){
                printf("Más pruebas 2\n");
                if (getItem(*dict, palabra) == 0) numero_palabras++;
                printf("Más pruebas 3\n");
                addItem(dict, palabra, getItem(*dict, palabra)+1);
                printf("Más pruebas 4\n");
                palabra = strtok(NULL, delimitador);
                printf("Más pruebas 5\n");
            }
        }
        printf("Prueba\n");
    }
    return *dict;
}

diccionario *create_array_dict(diccionario *dict, int tamaño){
    diccionario *array[tamaño];
    for (int i = 0; i < tamaño; ++i) {
        array[i] = dict;
        dict = dict->next;
    }
    return *array;
}

void show_recent_posts_from_user(char user[], timeline* tl, int n){
    publicacion *post;
    post = tl->last;
    if (n == -1) n = 999;
    int i = 0;
    while (post != NULL && i < n){
        if (strcmp(user, post->username) == 0){
            printf("%s\n", post->contenido);
            printf("- %s\n\n", post->username);
            i++;
        }
        post = post->prev;
    }
}

void show_old_posts_from_user(char user[], timeline* tl, int n){
    publicacion *post;
    post = tl->first;
    if (n == -1) n = 999;
    int i = 0;
    while (post != NULL && i < n){
        if (strcmp(user, post->username) == 0){
            printf("%s\n", post->contenido);
            printf("- %s\n\n", post->username);
            i++;
        }
        post = post->next;
    }
}