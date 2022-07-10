#ifndef HOME
#define HOME

#include "Email.hpp"

namespace User{
    struct Node{
        User::Email* email;
        Node* left;
        Node* right;

        Node(User::Email* email);
        ~Node();
    };
    
    class Home{
        Node* root;

        public:
            Home();
            User::Email* insert(User::Email* email);
            User::Email* find(int ID);
            User::Email* erase(int ID);
            ~Home();
    };
}

#endif