#ifndef DATA_PROPERTIES_H
#define DATA_PROPERTIES_H

#include <iostream>
#include <string>
#include <stdexcept>
#include <unordered_map>
#include <vector>


namespace graphs {
    
class VertexProps {
public:
	VertexProps();
	VertexProps(const std::vector<std::string>& keys,
			const std::vector<std::string>& values);

	const std::string& operator[](std::string key) const;
    std::string& operator[](std::string key);

	void add(const std::string& key, const std::string& value);
	const std::vector<std::string>& keys() const;

private:
	std::vector<std::string> keys_;
	std::unordered_map<std::string, std::string> properties_;
};

};
#endif // data_properties.h
