NAME = test

CPP_FILE = main.cpp test_map.cpp test_stack.cpp test_vector.cpp

COPMILE_FERSION = -std=c++98

all: $(NAME)

$(NAME): $(CPP_FILE)
	clang++ $(CPP_FILE) $(COPMILE_FERSION) $(FLAGS) -o $(NAME)

fclean:
	@rm -f $(NAME) $(NAME2) $(NAME3)

re: fclean all

.PHONY: all fclean re