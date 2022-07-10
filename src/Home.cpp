#include "Home.hpp"

/**
 * @brief Constroi um novo Node
 * 
 * @param email Email que ficará contido na árvore
 */
User::Node::Node(User::Email* email){
    this->email = email;
    this->left = nullptr;
    this->right = nullptr;
}

/**
 * @brief Deleta um Node e seus filhos
 * 
 */
User::Node::~Node(){
    delete email;
    delete left;
    delete right;
}

/**
 * @brief Constoi um novo objeto Home
 * 
 */
User::Home::Home(){
    root = nullptr;
}

/**
 * @brief Insere o novo email na Home
 * 
 * @param email email a ser inserido
 * @return User::Email* | email inserido
 */
User::Email* User::Home::insert(User::Email* email){
    if(root == nullptr){
        root = new Node(email);
        return email;
    }

    User::Node* current = root;
    while(true){
        if(email->id < current->email->id){
            if(current->left == nullptr){
                current->left = new Node(email);
                return email;
            }
            current = current->left;
        } else {
            if(current->right == nullptr){
                current->right = new Node(email);
                return email;
            }
            current = current->right;
        }
    }
}

/**
 * @brief Encontra e retorna um email, caso exista
 * 
 * @param ID ID do email
 * @return User::Email* | ponteiro para o email
 */
User::Email* User::Home::find(int ID){
    User::Node* current = root;
    
    while(current != nullptr){
        if(ID == current->email->id){
            return current->email;
        } else if(ID < current->email->id){
            current = current->left;
        } else {
            current = current->right;
        }
    }

    return nullptr;
}

/**
 * @brief Apaga um email da Home, caso exista
 * 
 * @param ID ID do email
 * @return User::Email* | o email que foi apagado
 */
User::Email* User::Home::erase(int ID){
    return nullptr;
}

/**
 * @brief Destroi a Home
 * 
 */
User::Home::~Home(){
    delete root;
}