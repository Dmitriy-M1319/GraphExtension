#ifndef DATA_PROPERTIES_H
#define DATA_PROPERTIES_H

#include <iostream>
#include <string>
#include <stdexcept>
#include <unordered_map>
#include <vector>


namespace data_containers {
    
class data_properties {
public:
	data_properties();
	data_properties(const std::vector<std::string>& keys,
			const std::vector<std::string>& values);

	const std::string& operator[](std::string key);
	void insert(const std::string& key, const std::string& value);
	const std::vector<std::string>& keys() const;

private:
	std::vector<std::string> keys_;
	std::unordered_map<std::string, std::string> properties_;
};

};
#endif // data_properties.h
