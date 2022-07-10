#include "Email.hpp"
#include "Server.hpp"
#include "memlog.h"
#include <sstream>
#include <fstream>
#include <string>
#include <iostream>

int main(int argc, char** argv){

    try{
        // tamanho do servidor que irá armazenar usuários e e-mails
        unsigned int serverSize;

        // variáveis que indicam os arquivos de entrada e saída do programa
        std::string inputFile = "";
        std::string outputFile = "";

        // variável auxiliar para capturar as linhas da entrada
        std::string buffer;

        // variável auxiliar para facilitar a leitura das linhas
        std::stringstream ss;

        // flag que define se o log de acesso deve ser criado ou não
        bool activateMemLog = false;

        // processa os parâmetros passados na chamada do programa
        for(int i=1; i < argc; i++){
            std::string aux = argv[i];
            if(aux == "-i"){
                i++;
                inputFile = argv[i];
            } else if(aux == "-o"){
                i++;
                outputFile = argv[i];
            } else if(aux == "-l"){
                activateMemLog = true;
            }
        }

        // verifica se os arquivos de entrada e saída foram passados como parâmetros
        if(inputFile == "") throw "Nenhum arquivo de entrada passado como parâmetro";
        if(outputFile == "") throw "Nenhum arquivo de saída passado como parâmetro";

        // inicia log de memória
        char memLog[] = "memLog.out";
        iniciaMemLog(memLog);

        // define se o log de memória deve ou não ser escrito
        activateMemLog ? ativaMemLog():desativaMemLog();

        // abre o arquivo de entrada e observa se foi aberto corretamente
        std::ifstream in(inputFile);
        if(!in.is_open()) throw "Falha ao abrir o arquivo de entrada";
        
        // lê a primeira linha do arquivo
        std::getline(in, buffer);
        ss << buffer;

        // inicializa o tamanho da tabela hash
        ss >> serverSize;

        // cria o servidor
        Server::Server* table = new Server::Server(serverSize, outputFile);

        // variáveis que podem ser lidas na entrada
        int userId;
        int emailId;
        int nWords;
        std::string command = "";

        while(!in.eof()){
            // lê a linha e a coloca em uma stringstream para facilitar seu processamento
            std::getline(in, buffer);
            ss << buffer;

            // lê o comando a ser executado
            ss >> command;

            // decide o que o programa deve fazer de acordo com o comando que foi passado
            if(command == "ENTREGA"){
                // cria um e-mail
                User::Email* email = new User::Email();

                // lê o ID do usuário e do e-mail, e a quantidade de palavras da mensagem
                ss >> userId >> email->id >> nWords;
                
                // variável auxiliar para a leitura da mensagem
                std::string aux;

                // lê a mensagem
                for(int i=0; i < nWords; i++){
                    ss >> aux;
                    email->message += aux;
                }

                // insere o e-mail, atribuído a um usuário
                table->insert(userId, email);
            } else if(command == "CONSULTA"){
                // lê o ID do usuário e o ID do e-mail
                ss >> userId >> emailId;

                // procura pelo e-mail na tabela hash
                table->find(userId, emailId);
            } else if(command == "APAGA"){
                // lê o ID do usuário e o ID do e-mail
                ss >> userId >> emailId;

                // apaga o e-mail, atribuído a um usuário
                table->erase(userId, emailId);
            } 
            // else {
            //     throw "Comando inválido passado durante a execução";
            // }
        }

        // fecha o arquivo
        in.close();

        // finaliza o log de memória
        finalizaMemLog();
    }

    catch(const char* e){
        std::cout << "ERRO: " << e << std::endl;
    }

    return 0;
}