#ifndef SERVER
#define SERVER

#include "Users.hpp"
#include "Email.hpp"
#include <string>
#include <fstream>

namespace Server{
    class Server{
        Users::Users* hashTable;
        int hashTableSize;
        std::ofstream out;

        /**
         * @brief Função de hashing da tabela
         * 
         * @param n Valor a ser processado pela função
         * @return int | Posição na tabela
         */
        inline int hashFunction(int n) const;

        public:
            /**
             * @brief Constroi um novo objeto do tipo Server
             * 
             * @param serverSize Tamanho da tabela hash que representa oo servidor
             * @param outputFile Caminho do arquivo de saída
             */
            Server(int serverSize, std::string outputFile);

            /**
             * @brief Insere um novo email no servidor
             * 
             * @param userId ID do usuário que está recebendo o email
             * @param mail Conteúdo do email
             * 
             * @return Imprime na tela o ID do email, do usuário e em que linha da tabela se encontra
             */
            void insert(int userId, Email mail);

            /**
             * @brief Procura por um email no servidor
             * 
             * @param userId ID do usuário que recebeu o email
             * @param emailId ID do email
             * 
             * @return Imprime na tela o conteúdo do email, se ele foi encontrada
             */
            void find(int userId, int emailId);

            /**
             * @brief Remove um email do servidor
             * 
             * @param userId ID do usuário que recebeu o email
             * @param emailId ID do email
             * 
             * @return Imprime na tela se o email foi removido ou não encontrada
             */
            void erase(int userId, int emailId);

            /**
             * @brief Destroi o objeto Server
             * 
             */
            ~Server();
    };
}

#endif