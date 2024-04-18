#pragma once

#include <fstream>
#include <string>
#include <unordered_map>

namespace graphs {

    namespace io {
        // пока примитивное тестовое хранилище всех строковых значений (ключи-значения свойств и метки)
        class StringVault {
        public:
            StringVault(const std::string& filename);

            const std::string& getStrById(unsigned int id) const;
            std::string& getStrById(unsigned int id);

            void setStr(unsigned int id, const std::string& value);
            void setStr(unsigned int id, std::string&& value);

            void append(const std::string& value);
            void append(std::string&& value);
        private:
            std::fstream file_;
            std::unordered_map<int, std::string> db_;
            static inline int curr_id = 0;
        };
    };

};
