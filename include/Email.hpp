#ifndef EMAIL
#define EMAIL

#include <string>

struct Email{
    int id;
    std::string message;

    /**
     * @brief Constroi um novo objeto do tipo Email
     * 
     */
    Email(){
        id = -1;
        message = "";
    }
};

#endif