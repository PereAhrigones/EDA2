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

//Esto hay que revisarlo porque hemos cambiado la estructura
void enviarSolicitudAmistad(char usuarioActual, char* usuarioDestino, Friend_request** solicitudesPendientes) {
    // Verificar si ya hay una solicitud pendiente o si ya son amigos
    Friend_request *solicitudActual = *solicitudesPendientes;
    while (solicitudActual != NULL) {
        if (solicitudActual->sender == usuarioActual && solicitudActual->receiver == usuarioDestino) {
            printf("Ya has enviado una solicitud de amistad a %s\n", usuarioDestino);
            return;
        }
        solicitudActual = solicitudActual->next;
    }

    // Crear una nueva solicitud de amistad
    Friend_request *nuevaSolicitud = (Friend_request *) malloc(sizeof(Friend_request));
    //Esto da error porque he cambiado la estructura. Ahora lo arreglo
    strcpy(nuevaSolicitud->sender, usuarioActual);
    nuevaSolicitud->receiver = usuarioDestino;
    nuevaSolicitud->next = *solicitudesPendientes;
    *solicitudesPendientes = nuevaSolicitud;

    // Enviar solicitud de amistad
    printf("Enviando solicitud de amistad de %s a %s\n", usuarioActual->username, usuarioDestino->username);
}


