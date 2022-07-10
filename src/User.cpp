#include "User.hpp"

/**
 * @brief Constroi um novo objeto do tipo User
 * 
 * @param ID ID do usuário
 */
User::User::User(int ID){
    this->ID = ID;
    this->home = new Home();
}

/**
 * @brief Insere um novo email na home do usuário
 * 
 * @param email Ponteiro para o Email que o usuário vai receber
 * 
 * @return User::Email* | ponteiro para o Email
 */
User::Email* User::User::insert(Email *email){
    return nullptr;
}

/**
 * @brief Encontra um determiado Email do usuário
 * 
 * @param ID ID do Email
 * @return User::Email* | ponteiro para o Email
 */
User::Email* User::User::find(int ID){
    return home->find(ID);
}

/**
 * @brief Apaga um Email do usuário
 * 
 * @param ID ID do Email
 * 
 * @return User::Email* | ponteiro para o Email
 */
User::Email* User::User::erase(int ID){
    return home->erase(ID);
}

/**
 * @brief Destroi objeto User
 * 
 */
User::User::~User(){
    ID = -1;
    delete home;
}