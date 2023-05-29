//
// Created by senyo on 29/5/2023.
//

#ifndef EDA2_PUBLICACION_H
#define EDA2_PUBLICACION_H
#include "usuario.h"

typedef struct _post{
    char contenido[MAX_POST_LENGHT];
    User_data *usuario;
    struct _post* next;
    struct _post* prev;
}publicacion;

typedef struct{
    publicacion *first;
    publicacion *last;
    int size;
}timeline;

void insert_post(publicacion* publ,User_data* user , char post[]);
void push_post(timeline* tl,User_data* user, char post[]);

#endif //EDA2_PUBLICACION_H
