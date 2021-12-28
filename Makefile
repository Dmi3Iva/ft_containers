NAME=test

STL_NAME=stl
STL_FILE=stl_file.log

FT_NAME=ft
FT_FILE=ft_file.log

SRC = main.cpp
OBJ=$(SRC:.cpp=.o)

red=`tput setaf 1`
green=`tput setaf 2`
reset=`tput sgr0`

HEADERS = common_iterator.hpp iterator_traits.hpp map.hpp Node.hpp reverse_iterator.hpp stack.hpp Tree.hpp tree_iterator.hpp utils.hpp vector.hpp

CXX=clang++

CXXFLAGS= -g -Wall -Wextra -Werror -Wshadow -Wno-shadow -std=c++98

all: $(NAME)

%.o: %.cpp $(HEADERS) $(SRC)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(STL_NAME):$(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(STL_NAME)

$(FT_NAME):$(OBJ) $(HEADERS)
	$(CXX) $(CXXFLAGS) -DFT $(OBJ) -o $(FT_NAME)

$(NAME): $(STL_NAME) $(FT_NAME)
	@echo "calculate FT time..."
	(time ./$(FT_NAME)) > $(FT_FILE)
	@echo "calculate STL time..."
	(time ./$(STL_NAME)) > $(STL_FILE)
	@echo "Compare results..."
	@cmp -s $(STL_FILE) $(FT_FILE); \
    RETVAL=$$?; \
    if [ $$RETVAL -eq 0 ]; then \
            echo "${green}Results are equal, test passed${reset}"; \
    else \
            echo "${red}Results aren't equal, test failed${reset}\n"; \
            diff  $(STL_FILE) $(FT_FILE); \
    fi


clean:
	rm -rf $(OBJ) $(FT_FILE) $(STL_FILE)

fclean: clean
	rm -rf $(FT_NAME) $(STL_NAME)

re: fclean all

