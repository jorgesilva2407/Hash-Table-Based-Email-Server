#ifndef USERS
#define USERS

#include "Home.hpp"

namespace Users{
    class User{
        friend class Users;

        int ID;
        Home::Home* home;
        User* next;

        /**
         * @brief Controi um novo objeto do tipo User
         * 
         * @param ID ID do usuário
         */
        User(int ID);
    };

    class Users{
        
    };
}

#endif