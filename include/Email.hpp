#ifndef EMAIL
#define EMAIL

#include <string>

namespace User{
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

        /**
         * @brief Destroi objeto Email
         * 
         */
        ~Email(){
            id = -1;
            message = "";
        }
    };
}

#endif