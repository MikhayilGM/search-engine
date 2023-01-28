#ifndef __CAESAR_H___
#define __CAESAR_H___

#include <fstream>
#include <cstring>
#include <iostream>

class Caesar
{
    private:
        char sym_enc(char);
        char sym_denc(char);
    public:
        std::string dencryption();
        std::string encryption();
        void set_text(const std::string&);
        void set_enc_code(int);
    
    private:
        std::string text{};
        int encrip {3};
};

#endif