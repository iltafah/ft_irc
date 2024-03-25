NAME		=	ircserv

CC			=	c++

CFLAGS		=	-Wall -Wextra -std=c++98

# directories
SRC_DIR		=	./
OBJ_DIR		=	obj/
INC_DIR		=	./

# controll codes
RESET		=	\033[0m
GREEN		=	\033[32m
YELLOW		=	\033[33m
BLUE		=	\033[34m
RED			=	\033[31m
UP			=	\033[A
CUT			=	\033[K

#source files
SRC_FILES	=	Server/server.cpp \
                Server/main.cpp \
				Database/database.cpp \
				Channels/channel.cpp \
				Users/user.cpp \
				Commands/Commands.cpp Commands/kick.cpp Commands/join.cpp

INC_FILES	=	Server/server.hpp \
				Database/database.hpp \
				Channels/channel.hpp \
				Users/user.hpp \
				Commands/Commands.hpp


OBJ_FILES	=	$(SRC_FILES:.cpp=.o)

#paths
SRC			=	$(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ			=	$(addprefix $(OBJ_DIR), $(OBJ_FILES))


#all rule
all: $(NAME)
	@printf "\n"
	@printf "$(GREEN)███████╗████████╗     					██╗██████╗  ██████╗\n$(RESET)"
	@printf "$(GREEN)██╔════╝╚══██╔══╝     					██║██╔══██╗██╔════╝\n$(RESET)"
	@printf "$(GREEN)█████╗     ██║        					██║██████╔╝██║     \n$(RESET)"
	@printf "$(GREEN)██╔══╝     ██║        					██║██╔══██╗██║     \n$(RESET)"
	@printf "$(GREEN)██║        ██║			███████╗		██║██║  ██║╚██████╗\n$(RESET)"
	@printf "$(GREEN)╚═╝        ╚═╝			╚══════╝		╚═╝╚═╝  ╚═╝ ╚═════╝\n$(RESET)"
	@printf "\n"

#compile the executable
$(NAME): $(OBJ) $(INC_FILES)
	@echo "$(YELLOW)Compiling [$(NAME)]...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "$(GREEN)Finished [$(NAME)]$(RESET)"

#compile objects
$(OBJ_DIR)%.o:$(SRC_DIR)%.cpp $(INC_FILES)
	@mkdir -p $(dir $@)
	@echo "$(YELLOW)Compiling [$@]...$(RESET)"
	@$(CC) $(CFLAGS) -I $(INC_DIR) -o $@ -c $<
	@printf "$(UP)$(CUT)"
	@echo "$(GREEN)Finished [$@]$(RESET)"
	@printf "$(UP)$(CUT)"

#clean rule
clean:
	@if [ -d "$(OBJ_DIR)" ]; then \
	rm -rf $(OBJ_DIR); \
	echo "$(BLUE)Deleting all objects from /ex02...$(RESET)"; else \
	echo "No objects to remove from /ex02."; \
	fi;

#fclean rule
fclean: clean
	@if [ -f "$(NAME)" ]; then \
	rm -f $(NAME); \
	echo "$(BLUE)Deleting $(NAME) from /ex02...$(RESET)"; else \
	echo "No Executable to remove from /ex02."; \
	fi;

#re rule
re: fclean all

#phony
.PHONY: all clean fclean re    