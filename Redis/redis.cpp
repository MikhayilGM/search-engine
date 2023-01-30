#include "redis.h"

std::vector<std::string> split(const std::string& str, const std::string& spliter)
{
    std::vector<std::string> vec;
    std::string tmp;

    for(size_t i = 0; i < str.size(); i++)
    {
        bool smt = 1;
        for (size_t j = 0; j < spliter.size(); j++)
        {
            if(spliter[j] == str[i])
            {
                if(tmp.size() != 0)
                {
                    vec.push_back(tmp);
                    tmp.clear();
                }
                smt = 0;
                break;
            }
        }

        if(smt)
        {
            tmp.push_back(str[i]);
        }
        
    }

    vec.push_back(tmp);

    return vec;
}

void Redis::add_value(const std::string& value, const std::string& file_name)
{
    std::ifstream fin;
    std::ofstream fout;
    fin.open(file_name);
    std::vector<std::string> vector;
    while(!fin.eof())
    {
        char tmp[64];
        fin.getline(tmp, 64, '\n');
        std::string smt = tmp;
        if(smt != "")
        {
            vector.push_back(tmp);
        }
        else
        {
            break;
        }
    }
    fin.close();

    vector.push_back(value);

    fout.open(file_name);

    for(int i = 0; i < vector.size() - 1; ++i)
    {
        fout << vector[i] << '\n';
    }
    fout << vector.back();
}

void Redis::add_value_at_start(const std::string& value, const std::string& file_name)
{
    std::ifstream fin;
    std::ofstream fout;
    fin.open(file_name);
    std::vector<std::string> vector;
    vector.push_back(value);
    while(!fin.eof())
    {
        char tmp[64];
        fin.getline(tmp, 64, '\n');
        std::string smt = tmp;
        if(smt != "")
        {
            vector.push_back(tmp);
        }
        else
        {
            break;
        }
    }
    fin.close();
    fout.open(file_name);

    for(int i = 0; i < vector.size() - 1; ++i)
    {
        fout << vector[i] << '\n';
    }

    fout << vector.back();

}

std::string Redis::get_value(int pos)
{
    if(pos == (-1))
    {
        return "nil";
    }
    char* re_value;
    std::fstream file(db_name+".value");

    for(int i = 0; i <= pos; ++i)
    {
        file.getline(re_value, '\n');
    }

    file.close();
    return re_value;
}

std::string Redis::get_hash_value(int pos, const std::string& fields)
{
    char* re_value;
    std::fstream file(db_name+".hash_info");
    if(pos == (-1))
    {
        return "nil";
    }
    for(int i = 0; i <= pos; ++i)
    {
        file.getline(re_value, '\n');
        std::cout << "sdasf";
    }

    std::vector<std::string> re_value_v = split(std::string(re_value), " :");
    std::string re_value_s;

    for (int i = 0; i < re_value_v.size(); i+=2)
    {
        if(fields == re_value_v[i])
        {
            re_value_s += (re_value_v[i] + " ");
        }
    }

    if(re_value_s.empty())
    {
        return "nil";
    }
    else
    {
        return re_value_s;
    }
}

Redis::Redis() : db_name()
{

}

Redis::Redis(const std::string& database_name) : db_name(database_name)
{
    std::ofstream db_file;
    db_file.open(db_name, std::ios::out);
}

Redis::~Redis()
{

}

void Redis::open_db(const std::string& database_name)
{
    db_name = database_name;
    std::ofstream db_file;
    db_file.open(db_name, std::ios::out);
}

void Redis::set(const std::string& key, const std::string& value)
{
    add_value(key, db_name+".key");
    add_value(value, db_name+".value");
}

const std::string Redis::get(const std::string& key)
{
    int pos = -1;
    int count = 0;
    std::ifstream file(db_name+".key");
    while(!file.eof())
    {
        char* tmp; 
        file.getline(tmp, 128, '\n');
        if(tmp == key)
        {
            pos = count;
            break;
        }
        ++count;
    }
    file.close();

    return get_value(pos);
}

void Redis::lpush(const std::string& value)
{
    std::fstream push_keys(db_name+".keys_number");
    int key_number;
    if(push_keys.is_open())
    {
        char* tmp;
        push_keys.getline(tmp, 64, '\n');
        if(tmp != "")
        {
            key_number = std::stoi(tmp) + 1;
        } 
        push_keys.close();
        push_keys.open(db_name+".keys_number");
        push_keys << std::to_string(key_number);
    }
    else 
    {
        push_keys.open(db_name+".keys_number", std::ios::out);
        push_keys << "1";
        key_number = 1;
    }
    add_value_at_start("KEY" + std::to_string(key_number), db_name+".key");
    add_value_at_start(value, db_name+".value");
}

void Redis::rpush(const std::string& value)
{
    std::fstream push_keys(db_name+".keys_number");
    int key_number;
    if(push_keys.is_open())
    {
        char* tmp;
        push_keys.getline(tmp, 64, '\n');
        if(tmp != "")
        {
            key_number = std::stoi(tmp);
        } 
        push_keys.close();
        push_keys.open(db_name+".keys_number");
        push_keys << std::to_string(++key_number);
    }
    else 
    {
        push_keys.open(db_name+".keys_number", std::ios::out);
        push_keys << "1";
        key_number = 1;
    }
    add_value("KEY" + std::to_string(key_number), db_name+".key");
    add_value(value, db_name+".value");
}

int Redis::llen()
{
    std::ifstream keys; 
    keys.open(db_name + ".keys");
    int counter = 0;
    while(!keys.eof() && keys.is_open())
    {
        char* tmp;
        keys.getline(tmp, 64, '\n');
        ++counter;
    }
    keys.close();
    keys.open(db_name + ".hash_key");
    while(!keys.eof() && keys.is_open())
    {
        char* tmp;
        keys.getline(tmp, 64, '\n');
        ++counter;
    }
    keys.close();
    return counter;
}

void Redis::hset(const std::string& key, const std::vector<std::string>& fields_n_values)
{
    add_value(key, db_name+".hash_key");
    if(fields_n_values.size()%2 != 0)
    {
        std::cout << "Your entered keys and values count are equal.\n";
        return;
    }
    std::string output_text;
    for(int i = 0; i < fields_n_values.size(); i+=2)
    {
        output_text += fields_n_values[i] + " : " + fields_n_values[i+1] + " ";
    }

    add_value(output_text, db_name+".hash_info");
}

const std::string Redis::hget(const std::string& hash_key, const std::string& fields_keys)
{
    int pos = -1;
    int count = 0;
    std::ifstream file(db_name+".hash_key");
    
    while(!file.eof())
    {
        char* tmp; 
        file.getline(tmp, 128, '\n');
        std::cout << tmp << "=" << hash_key;
        if(tmp == hash_key)
        {
            pos = count;
            break;
        }
        ++count;
    }
    file.close();

    return get_hash_value(pos, fields_keys);
}

const std::string Redis::hgetall(const std::string& hash_key)
{
    int pos = -1;
    int count = 0;
    std::ifstream file(db_name+".hash_key");
    while(!file.eof())
    {
        char* tmp; 
        file.getline(tmp, 128, '\n');
        if(tmp == hash_key)
        {
            pos = count;
            break;
        }
        ++count;
    }
    file.close();

    return get_value(pos);
}

int main()
{
    Redis redis("random");
    std::cout << redis.hgetall("RDA");
    return 0;
}