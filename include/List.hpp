#ifndef LIST
#define LIST

#include "User.hpp"

namespace Server{
    struct Cell{
        User::User* user;
        Cell* next;

        Cell(User::User* user, Cell* next);
        ~Cell();
    };

    class UserList{
        Cell* head;

        public:
            UserList();
            User::User* insert(User::User* user);
            User::User* find(int ID);
            ~UserList();
    };
}

#endif