#include "List.hpp"

/**
 * @brief Constroi uma nova célula que contém o usuário em uma lista encadeada
 * 
 * @param user Usuário
 * @param next Próxima Célula
 */
Server::Cell::Cell(User::User* user, Server::Cell* next){
    // inicializa o valor armazenado pela célula e o ponteiro para a célula adjascente desta
    this->user = user;
    this->next = next;
}

/**
 * @brief Destroi a célula
 * 
 */
Server::Cell::~Cell(){
    // deleta o usuário contido na célula e torna sua célula adjascente nula
    delete user;
    next = nullptr;
}

/**
 * @brief Constoi um novo objeto do tipo UserList
 * 
 */
Server::UserList::UserList(){
    // inicializa a cabeça da lista encadeada
    head = new Cell(new User::User(-1), nullptr);
}

/**
 * @brief Insere um novo usuário no começo da lista
 * 
 * @param user Ponteiro para o usuário
 * @return User::User* | ponteiro para o usuário que foi inserido
 */
User::User* Server::UserList::insert(User::User* user){
    // insere um novo usuário no começo da lista e retorna um ponteiro para o usuário que foi inserido
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
    // define a variável que será usada para se percorrer a lista
    Server::Cell* current = head->next;
    
    // percorre todos os elementos da lista se procurando pelo ID do usuário desejado
    while(current != nullptr){
        if(current->user->getId() == ID){
            return current->user;
        }
        current = current->next;
    }

    // retorna nullptr indicando que o usuário desejado não foi encontrado
    return nullptr;
}

/**
 * @brief Destroi objeto UserList
 * 
 */
Server::UserList::~UserList(){
    // cria variável auxilizar para se deletar os elemetnos da lista
    Server::Cell* aux = nullptr;

    // remove continuamente o primeiro elemento da lista até que não sovre mais nenhum
    while(head->next != nullptr){
        aux = head->next;
        head->next = aux->next;
        delete aux;
    }

    // deleta a cabeça da lista
    delete head;
}