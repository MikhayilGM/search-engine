#include "bit_vector.h"
#include <iostream>

bit_vector::bit_vector() : array(nullptr), size(0)
{

}

bit_vector::bit_vector(int bit_count) : size(bit_count)
{
    if(size)
    {
        array = new int[size/sizeof(int)+1];
    }
}

bit_vector::bit_vector(bit_vector&& rhs)
{
    size = rhs.size;
    array = new int[size/sizeof(int)+1];
    for(int i = 0; i < size/sizeof(int)+1; ++i)
    {
        array[i] = rhs.array[i];
    }
}

bit_vector::bit_vector(const bit_vector& rhs)
{
    size = rhs.size;
    array = new int[size/sizeof(int)+1];
    for(int i = 0; i < size/sizeof(int)+1; ++i)
    {
        array[i] = rhs.array[i];
    }
}

void bit_vector::set(bool val, int pos)
{   
    if(pos > size)
    {
        return;
    }

    if(val)
    {
        array[pos/sizeof(int)] = array[pos/sizeof(int)] | (val << (pos % sizeof(int)));
    }
    else
    {
        int tmp = ~0;
        tmp = tmp ^ (1 << (pos%sizeof(int)));
        array[pos/sizeof(int)] = array[pos/sizeof(int)] & (val << (pos % sizeof(int)));
    }
}

short bit_vector::get(int pos)
{
    if(pos >= size)
    {
        return -1;
    }
    return array[pos/sizeof(int)] & (1 << (pos%sizeof(int)));    
}
