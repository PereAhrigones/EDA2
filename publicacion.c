//
// Created by senyo on 29/5/2023.
//

#include "publicacion.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void insert_post(publicacion* publ, User_data *user, char post[]){
    publ->usuario = user;
    strcpy(publ->contenido, post);
    publ->next = NULL;
}

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

    return ITEM_NOT_FOUND;
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

diccionario *contar_palabras(timeline *tl){
    publicacion *actual;
    diccionario **dict = dictAlloc();
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
        char *palabra = strtok(copia, delimitador);
        if(palabra != NULL){
            while (palabra != NULL){
                addItem(dict, palabra, getItem(*dict, palabra)+1);
                palabra = strtok(NULL, delimitador);
            }
        }
    }
    return *dict;
}