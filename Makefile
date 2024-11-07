NAME	:= webserv

CC		:= c++
FLAGS	:= -Wextra -Wall -Werror

OBJ_DIR := ./src/Objects
SRCS_DIR = ./src

SRCS	:= $(SRCS_DIR)/main.cpp $(SRCS_DIR)/HttpServer.cpp
		
OBJS	:= $(addprefix $(OBJ_DIR)/, $(notdir ${SRCS:.cpp=.o}))

all: $(NAME)

$(OBJ_DIR)/%.o: $(SRCS_DIR)/%.cpp | $(OBJ_DIR)
	@$(CC) -o $@ -c $< $(FLAGS) && printf "Compiling: $(notdir $<)\n"
			
$(NAME): $(OBJS)
	@$(CC) $(FLAGS) $(OBJS) -o $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re