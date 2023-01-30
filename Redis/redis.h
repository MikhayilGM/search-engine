#ifndef ____REDIS__H_____
#define ____REDIS__H_____

#include <vector>
#include <string>
#include <iostream>
#include <fstream>

std::vector<std::string> split(const std::string& str, const std::string& spliter);

class Redis
{
protected:
    void add_value(const std::string& value, const std::string& file_name);
    void add_value_at_start(const std::string& value, const std::string& file_name);
    std::string get_value(int pos);
    std::string get_hash_value(int pos, const std::string&);
public:
    Redis();
    Redis(const std::string&);
    ~Redis();

    void open_db(const std::string&);
    void set(const std::string& key, const std::string& value);
    const std::string get(const std::string&);
    void lpush(const std::string&);
    void rpush(const std::string&);
    int llen();
    void hset(const std::string& key, const std::vector<std::string>& keys_n_values);
    const std::string hget(const std::string& hash_key, const std::string& fields_keys);
    const std::string hgetall(const std::string& hash_key);

protected:
    std::string db_name;

};

#endif