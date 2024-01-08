CXX = g++
CXXFLAGS = -g -std=c++17


all: graph_extension

graph_extension: data_properties.o graph.h main.cc
	$(CXX) $(CXXFLAGS) data_properties.o graph.h main.cc -o graph_extension

data_properties.o: data_properties.cc
	$(CXX) $(CXXFLAGS) -c data_properties.cc

clean:
	rm *.o
