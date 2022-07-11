#include "Home.hpp"

/**
 * @brief Constroi um novo Node
 * 
 * @param email Email que ficará contido na árvore
 */
User::Node::Node(User::Email* email){
    // inicializa os valores do nó
    this->email = email;
    this->left = nullptr;
    this->right = nullptr;
}

/**
 * @brief Deleta um Node e seus filhos
 * 
 */
User::Node::~Node(){
    // deleta o email armazenado pelo nó
    delete email;

    // deleta os filhos do nó de forma recursiva
    delete left;
    delete right;
}

/**
 * @brief Constoi um novo objeto Home
 * 
 */
User::Home::Home(){
    // inicializa a raíz da árvore
    root = nullptr;
}

/**
 * @brief Insere o novo email na Home
 * 
 * @param email email a ser inserido
 * @return User::Email* | email inserido
 */
User::Email* User::Home::insert(User::Email* email){
    // verifica se algum elemento já foi inserido na árvore
    if(root == nullptr){
        root = new Node(email);
        return email;
    }

    // define a variável usada para caminhar pela árvore
    User::Node* current = root;

    while(true){
        // comparação para definir para qual lado da árvore se deve ir
        if(email->id < current->email->id){
            // vê se o nó atual possui um filho do lado esquerdo
            if(current->left == nullptr){
                // no caso de não possuir um filho, o valor a ser inserido se torna seu filho
                current->left = new Node(email);
                return email;
            }
            // caso se tenha um filho, o processo desse loop é repetido para seu filho
            current = current->left;
        } else {
            // mesmos passos do if anterior
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
    // define a variável que será usada para caminhar pela árvore
    User::Node* current = root;
    
    while(current != nullptr){
        if(ID == current->email->id){
            // se o ID coincidir, o email foi encontrado e é, portanto, retornado
            return current->email;
        } else if(ID < current->email->id){
            // procura-se na subárvore a esquerda do nó atual, caso o nó armazene o email desejado
            current = current->left;
        } else {
            // procura-se na subárvore a direita do nó atual, caso o nó armazene o email desejado
            current = current->right;
        }
    }

    // retorna nulo indicando que o email não foi encontrado
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
    // deleta a raíz da árvore e, recursivamente, seus filhos, deletando assim, a árvore inteira
    delete root;
}