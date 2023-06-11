//
// Created by senyo on 29/5/2023.
//

#include "usuario.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
//insert_user igual se puede borrar
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


void initQueue(Queue* queue) {
    queue->front = NULL;
    queue->rear = NULL;
}

int isQueueEmpty(Queue* queue) {
    return (queue->front == NULL);
}

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
        FILE* file = fopen("/Users/naiara/CLionProjects/EDA2/amistad.txt", "a");
        if (file == NULL) {
            printf("Error al abrir el archivo de solicitudes.\n");
            return;
        }

        fprintf(file, "%s %s\n", nombre, otro);
        fclose(file);

        printf("Solicitud de amistad enviada a %s y guardada en el archivo.\n", otro);
    }
}


void imprimir_lista_amigos(User_data *usuario){
    int i = 0;
    while (strcmp(usuario->amigos[i], " ") != 0){
        printf("%s\n", usuario->amigos[i]);
        i++;
    }
}

void valoracion(User_data* user, float nota_dada){
    if(nota_dada < user->nota_min) user->nota_min = nota_dada;
    if (nota_dada > user->nota_max ) user->nota_max = nota_dada;
    user->nota = (user->nota * user->num_valoraciones + nota_dada) / (user->num_valoraciones+1);
    user->num_valoraciones++;

    guardarValoracionesUsuario(user); // Guardar las valoraciones en el archivo
}

void guardarValoracionesUsuario(const User_data* user) {
    FILE* archivo;
    archivo = fopen("/Users/naiara/CLionProjects/EDA2/Usuarios.txt", "a");

    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    fprintf(archivo, "%s\n", user->username);
    fprintf(archivo, "%.2f\n", user->nota);
    fprintf(archivo, "%.2f\n", user->nota_min);
    fprintf(archivo, "%.2f\n", user->nota_max);
    fprintf(archivo, "%d\n", user->num_valoraciones);
    fprintf(archivo, "\n");

    fclose(archivo);
    printf("Las valoraciones del usuario se han guardado en el archivo.\n");
}

void initializeStack(Stack* stack) {
    stack->top = NULL;
}
void push_2(Stack* stack, const Rating* rating) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->rating = *rating;
    newNode->next = stack->top;
    stack->top = newNode;
}

void pop(Stack* stack) {
    if (stack->top == NULL) {
        printf("La pila está vacía.\n");
        return;
    }

    Node* temp = stack->top;
    stack->top = stack->top->next;
    free(temp);
}

void guardarValoracionesUsuarios(User_list* lista) {
    FILE *archivo;
    archivo = fopen("/Users/naiara/CLionProjects/EDA2/Usuarios.txt", "w");
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }
}