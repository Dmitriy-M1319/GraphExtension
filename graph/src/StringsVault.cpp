#include "StringsVault.h"
#include <utility>

StringVault::StringVault(const std::string& filename): file_(filename, std::ios::in | std::ios::out) {
    if(file_.is_open()) {
        std::string line;
        while(std::getline(file_, line)) {
            if(line.back() == ' ')
                line.pop_back();
            db_[curr_id] = line;
            ++curr_id;
        }
        file_.clear();
        file_.seekg(0);
    }
}

StringVault::~StringVault() {
    file_.seekp(0, std::ios::beg);
    for(const auto& p: db_) {
        file_.write(p.second.c_str(), p.second.size());
        file_.put('\n');
    }
    file_.seekp(0, std::ios::end);
    file_.put(' ');
    file_.close();
}

unsigned int StringVault::currentId() const {
    return curr_id;
}

bool StringVault::isVaultOpen() const {
    return file_.is_open();
};

const std::string& StringVault::getStrById(unsigned int id) const {
    return db_.at(id - 1);
}

std::string& StringVault::getStrById(unsigned int id) {
    return db_.at(id - 1);
}


void StringVault::setStr(unsigned int id, const std::string& value) {
    db_[id - 1] = value;
}

void StringVault::setStr(unsigned int id, std::string&& value) {
    db_[id - 1] = std::move(value);
}

void StringVault::append(const std::string& value) {
    if(unsigned int idx = findStr(value) == 0) {
        db_.at(curr_id) = value;
        ++curr_id;
    }
}
void StringVault::append(std::string&& value) {
    db_.at(curr_id) = std::move(value);
    ++curr_id;

}

unsigned int StringVault::findStr(const std::string &value) const {
    for(const auto& p: db_) {
        if(p.second == value)
            return p.first;
    }
    return 0;
}

