//
// Created by senyo on 29/5/2023.
//

#include "publicacion.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

int postsfichero(timeline *tl){
    FILE *fp = fopen("C:\\Users\\senyo\\CLionProjects\\EDA2\\posts.txt", "w");
    if (fp == NULL){
        printf("Error al abrir el archivo.\n");
        return NO_FILE_FOUND;
    }
    publicacion *post = tl->first;
    while (post != NULL){
        fprintf("%s\n", post->contenido);
        fprintf("%s\n", post->usuario->username);
        post = post->next;
    }
    fclose(fp);
    return TRUE;
}

void insert_post(publicacion* publ, User_data *user, char post[]){
    publ->usuario = user;
    strcpy(publ->contenido, post);
    publ->next = NULL;
}

//ESTA FUNCIÓN SEGURAMENTE ESTÉ MAL PORQUE ESTA BASADA EN LA ANTIGUA FUNCIÓN PUSH DE LOS USUARIOS QUE TAMBIÉN ESTABA MAL
void push_post(timeline* tl, User_data *user, char post[]){
    publicacion* actual = tl->first;
    while (actual->next != NULL){
        actual = actual->next;
    }
    actual->next = (publicacion *) malloc(sizeof(publicacion));
    insert_post(actual->next, user, post);
    tl->last = actual->next;
    actual->next->prev = actual;
    tl->size++;
}

void pop_post(timeline* tl){
    tl->last->prev->next = NULL;
    tl->size--;
}

char** bubblesort_dictionary(char arr[], int n){
    int i, j;
    char string[n];
    for(i=0;i<n;i++){
        for(j=i+1;j<n;j++){
            if(strcmp(&arr[i], &arr[j])>0){
                strcpy(string,&arr[i]);
                strcpy(&arr[i],&arr[j]);
                strcpy(&arr[j],string);
            }
        }
    }
    return arr; //Warning de que el tipo de retorno es distinto al esperado. Actual: char* Esperado: char**
}

void show_top(timeline* tl){
    printf("\n%s\n", tl->last->contenido);
    printf("- %s\n\n", tl->last->usuario->username);
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
    diccionario **dict = dictAlloc();
    numero_palabras = 0;
    char *copia;
    char delimitador[] = ",.:;()/!¡?¿&·\"\\^*[]{}+-¬@#ºª<>%€'= "; //Si alguien encuentra algún símbolo que falta que lo ponga. NO BORRÉIS NADA DE LO QUE YA ESTÁ
    for(actual=tl->first; actual != NULL; actual = actual->next){
        strcpy(copia, actual->contenido);
        char copia_2[MAX_POST_LENGHT];
        strcpy(copia_2,copia);
        for (int i = 0; strlen(copia);i++){
            copia_2[i] = tolower(copia_2[i]);
        }
        strcpy(copia,copia_2);
        char *palabra = strtok(copia_2, delimitador);
        if(palabra != NULL){
            while (palabra != NULL){
                if (getItem(*dict, palabra) == 0) numero_palabras++;
                addItem(dict, palabra, getItem(*dict, palabra)+1);
                palabra = strtok(NULL, delimitador);
            }
        }
    }
    return *dict;
}

void show_recent_posts_from_user(User_data* user, timeline* tl, int n){//Hacer lo del -1
    publicacion *post;
    post = tl->last;
    if (n == -1) n = 999;
    int i = 0;
    while (post != NULL && i < n){
        if (strcmp(user->username, post->usuario->username) == 0){
            printf("%s\n", post->contenido);
            printf("- %s\n\n", post->usuario->username);
            i++;
        }
        post = post->prev;
    }
}

void show_old_posts_from_user(User_data* user, timeline* tl, int n){//Hacer lo del -1
    publicacion *post;
    post = tl->first;
    if (n == -1) n = 999;
    int i = 0;
    while (post != NULL && i < n){
        if (strcmp(user->username, post->usuario->username) == 0){
            printf("%s\n", post->contenido);
            printf("- %s\n\n", post->usuario->username);
            i++;
        }
        post = post->next;
    }
}