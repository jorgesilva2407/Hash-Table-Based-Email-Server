#include "Home.hpp"

#define RIGHT true
#define LEFT false

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
    // variável para informar se o último passo que ocorreu foi para a esquerda ou para a direita
    bool step;

    // variáveis para realizar o caminhamento sobre a árvore
    User::Node* previous = nullptr;
    User::Node* current = root;

    // realiza o caminhamento sobre a árvore
    while(current != nullptr){
        if(current->email->id == ID){
            // se o nó desejado foi encontrado, continua o programa
            break;
        } else if(ID < current->email->id){
            // procura-se na subárvore a esquerda do nó atual, caso o nó armazene o email desejado
            previous = current;
            current = current->left;
            step = LEFT;
        } else {
            // procura-se na subárvore a direita do nó atual, caso o nó armazene o email desejado
            previous = current;
            current = current->right;
            step = RIGHT;
        }
    }

    // verifica se o nó desejado foi encontrado ou se ele não existe
    if(current == nullptr) return nullptr;

    // remoção no caso do nó desejado ser a raiz
    if(current == root){
        // as duas primeiras condições avaliam se a árvore tem 1 ou nenhum filho, enquanto a última trata quando a árvore tem dois filhos
        if(current->left == nullptr){
            root = current->right;
        } else if(current->right == nullptr){
            root = current->left;
        } else {
            // variáveis para caminhar pela árvore e achar o adjascente da raíz
            User::Node* adjascente;
            User::Node* adjascentePrevious;
            adjascentePrevious = current;

            // opera na subárvore da direita 
            adjascente = current->right;
            
            // encontra o nó mais a esquerda da subárvore da direita
            while(adjascente->left != nullptr){
                adjascentePrevious = adjascente;
                adjascente = adjascente->left;
            }

            // remove o nó adascente da sua posição
            if(adjascente->right != nullptr){
                adjascentePrevious->left = adjascente->right;
            } else {
                adjascentePrevious->left = nullptr;
            }

            // substitui a ráiz pelo seu adjascente
            root = adjascente;

            // liga a nova raíz aos filhos da raíz anterior
            root->right = current->right;
            root->left = current->left;
        }

        // desaloca memória da ráiz anterior
        User::Email* aux = current->email;
        current->email = nullptr;
        current->right = nullptr;
        current->left = nullptr;
        delete current;
        return aux;
    }

    // caso de o nó a ser removido ser uma folha
    if(current->left == nullptr && current->right == nullptr){
        // apenas remove o nó
        if(step == RIGHT){
            previous->right = nullptr;
        } else {
            previous->left = nullptr;
        }

        // destroi o nó
        User::Email* aux = current->email;
        current->email = nullptr;
        delete current;
        return aux;
    }
    // caso de possuir somente um nó a esquerda 
    else if(current->left != nullptr && current->right == nullptr){
        // remove o nó, ligando seu sucessor com seu predecessor
        if(step == RIGHT){
            previous->right = current->left;
        } else {
            previous->left = current->left;
        }

        // destroi o nó
        User::Email* aux = current->email;
        current->email = nullptr;
        current->left = nullptr;
        delete current;
        return aux;
    } 
    // caso de possuir somente um nó a direita
    else if(current->left == nullptr && current->right != nullptr){
        // remove o nó, ligando seu sucessor com seu predecessor
        if(step == RIGHT){
            previous->right = current->right;
        } else {
            previous->left = current->right;
        }
        
        // destroi o nó
        User::Email* aux = current->email;
        current->email = nullptr;
        current->right = nullptr;
        delete current;
        return aux;
    } 
    // caso de possuir dois filhos
    else {
        // variáveis para caminhar pela árvore e achar o adjascente da raíz
        User::Node* adjascente;
        User::Node* adjascentePrevious;
        adjascentePrevious = current;

        // opera na subárvore da direita
        adjascente = current->right;
        
        // encontra o nó mais a esquerda da subárvore da direita
        while(adjascente->left != nullptr){
            adjascentePrevious = adjascente;
            adjascente = adjascente->left;
        }

        // remove o nó adascente da sua posição
        if(adjascente->right != nullptr){
            adjascentePrevious->left = adjascente->right;
        } else {
            adjascentePrevious->left = nullptr;
        }
        
        // liga o nó a ser inserido no lugar que deve ser inserido
        if(step == RIGHT){
            previous->right = adjascente;
        } else {
            previous->left = adjascente;
        }

        // liga o nó a ser inserido nos filhos do que acaba de ser removido
        adjascente->right = current->right;
        adjascente->left = current->left;

        // destroi o nó
        User::Email* aux = current->email;
        current->email = nullptr;
        current->right = nullptr;
        delete current;
        return aux;
    }
}

/**
 * @brief Destroi a Home
 * 
 */
User::Home::~Home(){
    // deleta a raíz da árvore e, recursivamente, seus filhos, deletando assim, a árvore inteira
    delete root;
}