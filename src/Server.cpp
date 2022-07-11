#include "Server.hpp"

/**
 * @brief Constroi um novo objeto do tipo Server
 * 
 * @param serverSize Tamanho da tabela hash que representa oo servidor
 * @param outputFile Caminho do arquivo de saída
 */
Server::Server::Server(int serverSize, std::string outputFile){
    // inicializa o tamanho que a tabela hash terá
    hashTableSize = serverSize;
    
    // aloca memória para a tabela hash
    hashTable = (UserList**)malloc(hashTableSize*sizeof(UserList*));
    
    // inicializa as posições da tabela hash com valores nulos
    for(int i=0; i < hashTableSize; i++){
        hashTable[i] = nullptr;
    }

    // abre o arquivo de saída do programa
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
    // encontra a posição do usuário na tabela de acordo com sua função de hashing
    int index = hashFunction(userId);

    // verifica se existem usuários nessa posição
    if(hashTable[index] == nullptr){
        // caso não existam, é criada uma lista encadeada para armazenar os usuário pertencentes a esssa posição
        hashTable[index] = new UserList();
    }

    // procura pela posição do usuário que irá receber o email
    User::User* aux = hashTable[index]->find(userId);

    // verifica se o usuário foi encontrado
    if(aux == nullptr){
        // caso não foi encontrado, ele é inserido na lista
        aux = hashTable[index]->insert(new User::User(userId));
    }

    // insere o email na caixa de entrada do destinatário
    aux->insert(email);

    // imprime mensagem no arquivo indicando que a operação foi um sucesso
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
    // imprime valores inicialmente por conveniência
    out << "CONSULTA " << userId << " " << emailId << ": ";
    
    // encontra a posição do usuário na tabela de acordo com sua função de hashing
    int index = hashFunction(userId);

    // verifica se existem usuários nessa posição da tabela hash
    if(hashTable[index] == nullptr){
        // caso não existam, então a mensagem informada também não foi envidada para este usuário
        out << "MENSAGEM INEXISTENTE" << std::endl;
        
        // encerra função
        return;
    }

    // procura pelo usuário desejado dentre a lista de usuários
    User::User* aux = hashTable[index]->find(userId);

    // verifica se o usuário existe
    if(aux == nullptr){
        // caso não exista, ele não recebeu a mensagem que se busca
        out << "MENSAGEM INEXISTENTE" << std::endl;

        // encerra função
        return;
    }

    // procura pelo email na caixa de entrada do usuário
    User::Email* email = aux->find(emailId);

    // verifica se o email foi encontrado
    if(email == nullptr){
        // email não foi encontrado
        out << "MENSAGEM INEXISTENTE" << std::endl;

        // encerra função
        return;
    }

    // imprime a mensagem contida no email
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
    // imprime valores inicialmente por conveniência
    int index = hashFunction(userId);

    // verifica se existem usuários nessa posição da tabela hash
    if(hashTable[index] == nullptr){
        // impossível apagar mensagens que não existem
        out << "ERRO: MENSAGEM INEXISTENTE" << std::endl;

        // encerra função
        return;
    }

    // procura pelo usuário desejado dentre a lista de usuários
    User::User* aux = hashTable[index]->find(userId);

    // verifica se usuário existe
    if(aux == nullptr){
        // impossível apagar mensagens que não existem
        out << "ERRO: MENSAGEM INEXISTENTE" << std::endl;
        
        // encerra função
        return;
    }

    // tenta apagar a mensagem na caixa de entrada do usuário
    User::Email* email = aux->erase(emailId);

    // verifica se a operação teve sucesso
    if(email == nullptr){
        // mensagem não foi encontrada
        out << "ERRO: MENSAGEM INEXISTENTE" << std::endl;

        // encerra função
        return;
    }

    // deleta o email
    delete email;

    // mensagem informando o sucesso da operação
    out << "OK: MENSAGEM APAGADA" << std::endl;
}

/**
    * @brief Destroi objeto Server
    * 
    */
Server::Server::~Server(){
    // destroi todos os elementos de cada posição da tabela hash
    for(int i=0; i < hashTableSize; i++){
        delete hashTable[i];
    }
    
    // destroi a tabela hash em si
    free(hashTable);
}