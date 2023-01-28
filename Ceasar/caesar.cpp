#include "caesar.h"

char Caesar::sym_enc(char sym)
{
    if (sym >= 'A' && sym <= 'Z' )
    {
        if(sym + (encrip % 26) >= 'A' && sym + (encrip % 26) <= 'Z' )
        {
            return sym + (encrip % 26);    
        }
        else if(sym + (encrip % 26) < 'A')
        {
            return sym+(encrip % 26) + 26;   
        }
        else
        {
            return sym+(encrip % 26) - 26;
        }
        
    }
    if (sym >= 'a' && sym <= 'z' )
    {
        if(sym + (encrip % 26) >= 'a' && sym + (encrip % 26) <= 'z' )
        {
            return sym + (encrip % 26);    
        }
        else if(sym + (encrip % 26) < 'a')
        {
            return sym+(encrip % 26) + 26;   
        }
        else
        {
            return sym+(encrip % 26) - 26;
        }
        
    }
    
    return sym;
}

char Caesar::sym_denc(char sym)
{
    if (sym >= 'A' && sym <= 'Z' )
    {
        if(sym - (encrip % 26) >= 'A' && sym - (encrip % 26) <= 'Z' )
        {
            return sym - (encrip % 26);    
        }
        else if(sym - (encrip % 26) < 'A')
        {
            return sym - (encrip % 26) + 26;   
        }
        else
        {
            return sym + (encrip % 26) - 26;
        }
        
    }
    if (sym >= 'a' && sym <= 'z' )
    {
        if(sym - (encrip % 26) >= 'a' && sym - (encrip % 26) <= 'z' )
        {
            return sym - (encrip % 26);    
        }
        else if(sym - (encrip % 26) < 'a')
        {
            return sym - (encrip % 26) + 26;   
        }
        else
        {
            return sym - (encrip % 26) -  26;
        }
        
    }
    
    return sym;
}

void Caesar::set_text(const std::string& entered_text) 
{
    text = entered_text;
}


void Caesar::set_enc_code(int num) 
{
    encrip = num;
}

std::string Caesar::encryption()
{
    std::string tmp = text;
    for(int i = 0; i < tmp.size(); ++i)
    { 
        tmp[i] = Caesar::sym_enc(tmp[i]);
    }
    return tmp;
}

std::string Caesar::dencryption()
{
    std::string tmp = text;
    for(int i = 0; i < tmp.size(); ++i)
    { 
        tmp[i] = Caesar::sym_denc(tmp[i]);
    }
    return tmp;
}