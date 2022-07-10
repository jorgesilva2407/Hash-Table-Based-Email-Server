#ifndef USER
#define USER

#include "Home.hpp"
#include "Email.hpp"

namespace User{
    class User{
        int ID;
        Home* home;

        public:
            User(int ID);
            inline int getId() const {return ID;}
            Email* insert(Email* email);
            Email* find(int ID);
            Email* erase(int ID);
            ~User();
    };
}

#endif