#pragma once

#include <fstream>
#include <string>
#include <map>


// TODO: Сохранять строки с одинаковым содержимым как одно целое
// Тогда при сохранении вернуть новый индекс (или уже имеющийся)
class StringVault {
public:
    explicit StringVault(const std::string& filename);
    StringVault(const StringVault&) = delete;
    StringVault& operator=(const StringVault&) = delete;
    ~StringVault();

    bool isVaultOpen() const;
    unsigned int currentId() const;

    const std::string& getStrById(unsigned int id) const;
    std::string& getStrById(unsigned int id);

    void setStr(unsigned int id, const std::string& value);
    void setStr(unsigned int id, std::string&& value);

    void append(const std::string& value);
    void append(std::string&& value);

private:
    std::fstream file_;
    std::map<unsigned int, std::string> db_;
    unsigned int curr_id = 0;
};
