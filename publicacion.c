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

int Contar_Palabras(publicacion* publi){
    if(publi->contenido[MAX_POST_LENGHT] == NULL)return 0;

    int counter = sizeof (publi->contenido[MAX_POST_LENGHT]);
    for (int i = 0;i < counter;i++){
        if(strcmp(&publi->contenido[i],NULL) == 0){
            counter ++;
        }

    }
    return counter;
}

void show_top(timeline* tl){
    printf("\n%s\n", tl->last->contenido);
    printf("- %s\n\n", tl->last->usuario->username);
}