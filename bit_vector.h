class bit_vector
{
public:
    bit_vector();
    bit_vector(int bit_count);
    bit_vector(bit_vector&& rhs);
    bit_vector(const bit_vector& rhs);

    void set(bool val, int pos);
    short get(int pos);    
private:
    int* array;
    int size;
};