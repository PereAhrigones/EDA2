//
// Created by senyo on 26/4/2023.
//

#ifndef EDA2_MAIN_H
#define EDA2_MAIN_H

#include "usuario.h"
#include "publicacion.h"

User_data* encontrar_usuario(char username[], User_list *lista);

timeline* leer_posts(User_list* lista);
#include "menu.h"
int main();


#endif //EDA2_MAIN_H
