# --- Colors ---
RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BOLD = \033[1m
RESET = \033[0m
CLEAR = \033[2K\r

# --- Variables ---
NAME = a.out
CXX = c++
INCLUDES = -I.
CPPFLAGS = -Wall -Wextra -Werror -std=c++98 $(INCLUDES)
LFLAGS =  $(CPPFLAGS)
SRC = ./A.cpp ./B.cpp ./C.cpp ./Base.cpp  ./main.cpp
OBJ = $(SRC:%.cpp=obj/%.o)

all: $(NAME)
	@printf "$(GREEN)$(BOLD)$(NAME) done!$(RESET)\n"

$(NAME): $(OBJ)
	@printf "$(CLEAR)$(YELLOW)linking $(NAME)...$(RESET)\n"
	@$(CXX) $(OBJ) $(LFLAGS) -o $(NAME)

obj/%.o: %.cpp
	@mkdir -p $(dir $@)
	@printf "[$(GREEN)$(BOLD) OK $(RESET)$(BOLD)]$(RESET) compiling $(BOLD)$@...$(RESET)$(CLEAR)"
	@$(CXX) -c $(CPPFLAGS) $< -o $@

clean:
	@printf "$(RED)$(BOLD)cleaning object files...\n"
	@rm -rf obj/

fclean: clean
	@printf "$(RED)$(BOLD)cleaning all...\n"
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
.SECONDARY: $(OBJ)
