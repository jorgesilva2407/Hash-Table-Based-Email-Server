#include "User.hpp"

/**
 * @brief Constroi um novo objeto do tipo User
 * 
 * @param ID ID do usuário
 */
User::User::User(int ID){
    // inicializa o ID do usuário e seu caixa de entrada de emails
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
    // insere o email na caixa de entrada e retorna um ponteiro para o email inserido
    return home->insert(email);
}

/**
 * @brief Encontra um determiado Email do usuário
 * 
 * @param ID ID do Email
 * @return User::Email* | ponteiro para o Email
 */
User::Email* User::User::find(int ID){
    // realiza a pesquisa na caixa de entrada e rotorna o valor que foi retornado por ela, sendo nullptr caso o email não tenha sido encontrado
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
    // apaga o email da caixa de entrada e retorna seu valor para cao queira consultá-lo
    return home->erase(ID);
}

/**
 * @brief Destroi objeto User
 * 
 */
User::User::~User(){
    // define o id para um valor inválido e deleta a caixa de entrada
    ID = -1;
    delete home;
}