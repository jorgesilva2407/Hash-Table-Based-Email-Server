#include "Server.hpp"

/**
 * @brief Constroi um novo objeto do tipo Server
 * 
 * @param serverSize Tamanho da tabela hash que representa oo servidor
 * @param outputFile Caminho do arquivo de saída
 */
Server::Server::Server(int serverSize, std::string outputFile){
    hashTableSize = serverSize;
    hashTable = (UserList**)malloc(hashTableSize*sizeof(UserList*));
    for(int i=0; i < hashTableSize; i++){
        hashTable[i] = nullptr;
    }
    out.open(outputFile);
    if(!out.is_open()) throw "Falha ao abrir o arquivo de saída";
}

/**
    * @brief Insere um novo email no servidor
    * 
    * @param userId ID do usuário que está recebendo o email
    * @param email Conteúdo do email
    * 
    * @return Imprime na tela o ID do email, do usuário e em que linha da tabela se encontra
    */
void Server::Server::insert(int userId, User::Email* email){
    int index = hashFunction(userId);

    if(hashTable[index] == nullptr){
        hashTable[index] = new UserList();
    }

    User::User* aux = hashTable[index]->find(userId);

    if(aux == nullptr){
        aux = hashTable[index]->insert(new User::User(userId));
    }

    aux->insert(email);

    out << "OK: MENSAGEM " << email->id << " PARA " << userId << " ARMAZENADA EM " << index << std::endl;
}

/**
    * @brief Procura por um email no servidor
    * 
    * @param userId ID do usuário que recebeu o email
    * @param emailId ID do email
    * 
    * @return Imprime na tela o conteúdo do email, se ele foi encontrada
    */
void Server::Server::find(int userId, int emailId){
    out << "CONSULTA " << userId << " " << emailId << ": ";
    
    int index = hashFunction(userId);

    if(hashTable[index] == nullptr){
        out << "MENSAGEM INEXISTENTE" << std::endl;
        return;
    }

    User::User* aux = hashTable[index]->find(userId);

    if(aux == nullptr){
        out << "MENSAGEM INEXISTENTE" << std::endl;
        return;
    }

    User::Email* email = aux->find(emailId);

    if(email == nullptr){
        out << "MENSAGEM INEXISTENTE" << std::endl;
        return;
    }

    out << email->message << std::endl;
}

/**
    * @brief Remove um email do servidor
    * 
    * @param userId ID do usuário que recebeu o email
    * @param emailId ID do email
    * 
    * @return Imprime na tela se o email foi removido ou não encontrada
    */
void Server::Server::erase(int userId, int emailId){
    int index = hashFunction(userId);

    if(hashTable[index] == nullptr){
        out << "ERRO: MENSAGEM INEXISTENTE" << std::endl;
        return;
    }

    User::User* aux = hashTable[index]->find(userId);

    if(aux == nullptr){
        out << "ERRO: MENSAGEM INEXISTENTE" << std::endl;
        return;
    }

    User::Email* email = aux->find(emailId);

    if(email == nullptr){
        out << "ERRO: MENSAGEM INEXISTENTE" << std::endl;
        return;
    }

    out << "OK: MENSAGEM APAGADA" << std::endl;
}

/**
    * @brief Destroi objeto Server
    * 
    */
Server::Server::~Server(){
    for(int i=0; i < hashTableSize; i++){
        delete hashTable[i];
    }
    delete hashTable;
}