#include "data_properties.h"

using namespace data_containers;

data_properties::data_properties(): keys_{}, properties_{} {}

data_properties::data_properties(const std::vector<std::string>& keys,
			const std::vector<std::string>& values): properties_{}, keys_{keys} {
	if(keys.size() != values.size()) {
		throw std::runtime_error("Keys size and values size are different");
	}
	std::unordered_map<std::string, std::string> tmp;
	for(int i = 0; i < keys.size(); ++i) {
		tmp[keys.at(i)] = values.at(i);
	}
	std::swap(tmp, properties_);
}

const std::string& data_properties::operator[](std::string key) {
    return properties_.at(key);
}


void data_properties::insert(const std::string& key, const std::string& value) {
    auto result = properties_.insert_or_assign(key, value);
	// Проверка на условие нового ключа в словаре
	if(std::get<1>(result)) {
		keys_.push_back(key);
	}
}

const std::vector<std::string>& data_properties::keys() const {
    return keys_;
}

