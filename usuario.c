//
// Created by senyo on 29/5/2023.
//

#include "usuario.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
//Función que inserta un usuario en la lista de usuario. Prácticamente obsoleta desde que mejoramos push, pero push daba problemas en el lugar donde está implementada esta así que decidimos mantenerla
void insert_user(User_data* miembro, char nombre_usuario[], char correo[], char contraseña[], char ciudad[], int año, int num_usuario, char gusto1[], char gusto2[], char gusto3[], char gusto4[], char gusto5[], float nota, float nota_max, float nota_min, int valoraciones){
    strcpy(miembro->username, nombre_usuario);
    strcpy(miembro->email, correo);
    strcpy(miembro->password, contraseña);
    strcpy(miembro->city, ciudad);
    miembro->birth = año;
    miembro->user_number = num_usuario;
    strcpy(miembro->likes[0], gusto1);
    strcpy(miembro->likes[1], gusto2);
    strcpy(miembro->likes[2], gusto3);
    strcpy(miembro->likes[3], gusto4);
    strcpy(miembro->likes[4], gusto5);
    miembro->nota = nota;
    miembro->nota_max = nota_max;
    miembro->nota_min = nota_min;
    miembro->num_valoraciones = valoraciones;
    miembro->next = NULL;
}

//Función que inserta un usuario al final de la lista de usuarios.
void push(User_list* lista, char nombre_usuario[], char correo[], char contraseña[], char ciudad[], int año, int num_usuario, char gusto1[], char gusto2[], char gusto3[], char gusto4[], char gusto5[], float nota, float nota_max, float nota_min, int valoraciones) {
    User_data *nuevo_usuario = (User_data*) malloc(sizeof(User_data));  //Crear un nuevo usuario
    strcpy(nuevo_usuario->username, nombre_usuario);
    strcpy(nuevo_usuario->email, correo);
    strcpy(nuevo_usuario->password, contraseña);
    strcpy(nuevo_usuario->city, ciudad);
    nuevo_usuario->birth = año;
    nuevo_usuario->user_number = num_usuario;
    strcpy(nuevo_usuario->likes[0], gusto1);
    strcpy(nuevo_usuario->likes[1], gusto2);
    strcpy(nuevo_usuario->likes[2], gusto3);
    strcpy(nuevo_usuario->likes[3], gusto4);
    strcpy(nuevo_usuario->likes[4], gusto5);
    nuevo_usuario->nota = nota;
    nuevo_usuario->nota_max = nota_max;
    nuevo_usuario->nota_min = nota_min;
    nuevo_usuario->num_valoraciones = valoraciones;
    nuevo_usuario->solicitudes = NULL;
    nuevo_usuario->next = NULL;
    nuevo_usuario->prev = NULL;
    if (lista->first == NULL) {
        lista->first = nuevo_usuario;
        lista->last = nuevo_usuario;
    } else {
        nuevo_usuario->prev = lista->last;
        lista->last->next = nuevo_usuario;
        lista->last = nuevo_usuario;
    }
    lista->size++;  // Incrementar el tamaño de la lista
}
//Función que se usaría para liberar la memoria de un usuario
void limpiar_User_data(User_data* guardar) {
    if (guardar == NULL) {
        return;
    }

    free(guardar->email);
    free(guardar->password);
    free(guardar->username);
    free(guardar->city);

    for (int i = 0; i < MAX_LIKE_LENGTH; i++) {
        free(guardar->likes[i]);

    }

    guardar->user_number = 0;
    guardar->birth = 0;

    free(guardar);
}

//Función que inicializa una cola
void initQueue(Queue* queue) {
    queue->front = NULL;
    queue->rear = NULL;
}
//Devuelve TRUE (1) sí la cola está vacía y FALSE (0) si no.
int isQueueEmpty(Queue* queue) {
    return (queue->front == NULL);
}

//Añade un elemento a la cola
void enqueueRequest(Queue* queue, const char* sender, const char* receiver) {
    Friend_request* newRequest = (Friend_request*)malloc(sizeof(Friend_request));
    strcpy(newRequest->sender, sender);
    strcpy(newRequest->receiver, receiver);
    newRequest->next = NULL;

    if (isQueueEmpty(queue)) {
        queue->front = newRequest;
        queue->rear = newRequest;
    } else {
        queue->rear->next = newRequest;
        queue->rear = newRequest;
    }
}

//Elimina un elemento de la cola
Friend_request* dequeueRequest(Queue* queue) {
    if (isQueueEmpty(queue)) {
        return NULL;
    }

    Friend_request* dequeuedRequest = queue->front;
    queue->front = queue->front->next;

    if (queue->front == NULL) {
        queue->rear = NULL;
    }

    dequeuedRequest->next = NULL;
    return dequeuedRequest;
}

//Función que gestiona el envío de una solicitud de amistad
void enviarSolicitudAmistad(User_list* lista, const char* nombre, const char* otro) {
    User_data* usuarioActual = NULL;
    User_data* usuarioDestino = NULL;

    User_data* current = lista->first;
    while (current != NULL) {
        if (strcmp(nombre, current->username) == 0) {
            usuarioActual = current;
        }
        if (strcmp(otro, current->username) == 0) {
            usuarioDestino = current;
        }
        current = current->next;
    }

    if (usuarioActual != NULL && usuarioDestino != NULL) {
        FILE* file = fopen("/Users/senyo/CLionProjects/EDA2/amistad.txt", "a");
        if (file == NULL) {
            printf("Error al abrir el archivo de solicitudes.\n");
            return;
        }

        fprintf(file, "%s %s\n", nombre, otro);
        fclose(file);

        printf("Solicitud de amistad enviada a %s y guardada en el archivo.\n", otro);
    }
}

//Función que imprime la lista de amigos
void imprimir_lista_amigos(User_data *usuario){
    int i = 0;
    while (strcmp(usuario->amigos[i], " ") != 0){
        printf("%s\n", usuario->amigos[i]);
        i++;
    }
}

//Función que gestiona las valoraciones de un usuario
void valoracion(User_data* user, float nota_dada){
    if(nota_dada < user->nota_min) user->nota_min = nota_dada;
    if (nota_dada > user->nota_max ) user->nota_max = nota_dada;
    user->nota = (user->nota * user->num_valoraciones + nota_dada) / (user->num_valoraciones+1);
    user->num_valoraciones++;
}
//Función que inicializa la pila
void initializeStack(Stack* stack) {
    stack->top = NULL;
}
//Función que empuja un nuevo elemetno en la pila
void push_2(Stack* stack, const Rating* rating) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->rating = *rating;
    newNode->next = stack->top;
    stack->top = newNode;
}
//Función que saca un elementode la pila
void pop(Stack* stack) {
    if (stack->top == NULL) {
        printf("La pila está vacía.\n");
        return;
    }

    Node* temp = stack->top;
    stack->top = stack->top->next;
    free(temp);
}
