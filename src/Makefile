sources= \
            reverse-group-nodes.cpp \
            main.cpp
headers = \
            reverse-group-nodes.hpp

objects = ${sources:.cpp=.o}

CXXFLAGS = --std=c++20 -g -Werror -Wall -I.

binary=k-reverse-list

.PHONY: clean all test
all: $(binary)

debug: CXXFLAGS += -DDEBUG -O0
debug: all


$(binary): $(objects)
	$(CXX) -o $@ $(objects)


%.o: %.cpp $(headers)
	$(CXX) $(CXXFLAGS) -c $< -o $@


test: $(binary)
	./test.sh


clean:
	rm -f $(binary) $(objects)
