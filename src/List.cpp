#include "List.hpp"

/**
 * @brief Constroi uma nova célula que contém o usuário em uma lista encadeada
 * 
 * @param user Usuário
 * @param next Próxima Célula
 */
Server::Cell::Cell(User::User* user, Server::Cell* next){
    this->user = user;
    this->next = next;
}

/**
 * @brief Destroi a célula
 * 
 */
Server::Cell::~Cell(){
    delete user;
}

/**
 * @brief Constoi um novo objeto do tipo UserList
 * 
 */
Server::UserList::UserList(){
    head = new Cell(new User::User(-1), nullptr);
}

/**
 * @brief Insere um novo usuário no começo da lista
 * 
 * @param user Ponteiro para o usuário
 * @return User::User* | ponteiro para o usuário que foi inserido
 */
User::User* Server::UserList::insert(User::User* user){
    head->next = new Cell(user, head->next);
    return user;
}

/**
 * @brief Encontra o usuário com um determinado ID
 * 
 * @param ID ID do usuário
 * @return User::User* | ponteiro para o usuário
 */
User::User* Server::UserList::find(int ID){
    Server::Cell* current = head->next;
    
    while(current != nullptr){
        if(current->user->getId()== ID){
            return current->user;
        }
        current = current->next;
    }

    return nullptr;
}

/**
 * @brief Destroi objeto UserList
 * 
 */
Server::UserList::~UserList(){
    Server::Cell* aux = nullptr;

    while(head->next != nullptr){
        aux = head->next;
        head->next = aux->next;
        delete aux;
    }

    delete head;
}