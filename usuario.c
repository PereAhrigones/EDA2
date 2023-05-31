//
// Created by senyo on 29/5/2023.
//

#include "usuario.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void insert_user(User_data* miembro, char nombre_usuario[], char correo[], char contraseña[], char ciudad[], int año, int num_usuario, char gusto1[], char gusto2[], char gusto3[], char gusto4[], char gusto5[], float nota){
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

void push(User_list* lista, char nombre_usuario[], char correo[], char contraseña[], char ciudad[], int año, int num_usuario, char gusto1[], char gusto2[], char gusto3[], char gusto4[], char gusto5[], float nota) {
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

void guardar_gustos(User_list* lista,char username[MAX_USERNAME_LENGTH],char gustos[MAX_LIKE_LENGTH],int numero){ //No está revisado si esta función tiene sentido o.
    User_data *user_likes = lista->first;
    while (user_likes->next != NULL) {
        if (strcmp(user_likes->username, username) == 0) { //Creo, no estoy seguro, pero  a esto creo que le falta cosa.
            strcpy(user_likes -> likes[numero] ,gustos);
            return;
        }
    }
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

    while(actual!= NULL){
        limpiar_User_data(actual);
        actual = actual->next;

    }
    lista->first = NULL;
    lista->last = NULL;
    lista->size = 0 ;
}

void enviarSolicitudAmistad(User_data* usuario, User_data* amigo, PilaSolicitudes* pila) {
    User_data usuario;
    User_data amigo;
    PilaSolicitudes pilaSolicitudes;
    pilaSolicitudes.top = -1;

    printf("Ingrese su nombre: ");
    scanf("%s", usuario->username);

    printf("Ingrese su edad: ");
    scanf("%d", &usuario->username);

    printf("Ingrese el nombre del usuario al que desea enviar una solicitud de amistad: ");
    scanf("%s", amigo->username);

    printf("Ingrese la edad del usuario: ");
    scanf("%d", &amigo->birth);

    printf("Enviando solicitud de amistad a %s...\n", amigo->username);
    // Lógica para enviar la solicitud de amistad

    if (pila->top == MAX_SOLICITUDES - 1) {
        printf("No se pueden almacenar más solicitudes de amistad\n");
        return;
    }
    pila->top++;
    pila->solicitudes[pila->top] = *amigo;
    printf("Solicitud de amistad enviada a %s y almacenada\n", amigo->username);
}


