//
// Created by senyo on 29/5/2023.
//

#include "publicacion.h"
#include <string.h>
#include <stdlib.h>

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