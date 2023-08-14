NAME			:= cub3d
NICKNAME		:= CUB3d

# Directories
HDR_DIR			:= include
LIB_DIR			:= lib
SRC_DIR			:= src
OBJ_DIR			:= obj

# Compiler flags
CC				:= c++
CFLAGS			:= -Wall -Werror -Wextra

ifdef DEBUG
	CFLAGS		+= -g -fsanitize=address
endif

# Includes
HDR_FILES		:=							\
					cubed.h					\

# Files
SRC_FILES		:=							\
					main.c					\
					cub3d.c					\


SRC				:= $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJ				:= ${addprefix ${OBJ_DIR}/, ${SRC_FILES:.cpp=.o}}
HDR				:= $(addprefix $(HDR_DIR)/, $(HDR_FILES))

# Colours
GREEN			:= \033[32;1m
YELLOW			:= \033[33;1m
RED				:= \033[31;1m
BOLD			:= \033[1m
RESET			:= \033[0m

# Rules
all: ${NAME}

$(NAME): $(OBJ)
	@ printf "%b%s%b" "$(YELLOW)$(BOLD)" "Compiling $(NICKNAME)..." "$(RESET)"
	@ $(CC) $(CFLAGS) $(OBJ) -o $(NAME) 
	@ printf "\t\t%b%s%b\n" "$(GREEN)$(BOLD)" "[OK]" "$(RESET)"


$(OBJ_DIR)/%.o: src/%.cpp $(HDR)
	@ mkdir -p obj
	@ $(CC) $(CFLAGS) -c $< -o $@ -I $(HDR_DIR)

open: $(NAME)
	@ ./$(NAME)

log:
	@ git log --graph --format=format:'%C(bold blue)%h%C(reset) - %C(bold green)(%ar)%C(reset) %C(white)%an%C(reset)%C(bold yellow)%d%C(reset) %C(dim white)- %s%C(reset)' --all

clean:
	@ echo "$(RED)$(BOLD)Cleaning $(NICKNAME)...$(RESET)"
	@ rm -rf $(OBJ_DIR)

fclean:
	@ echo "$(RED)$(BOLD)Fully cleaning $(NICKNAME)...$(RESET)"
	@ rm -rf $(OBJ_DIR)
	@ rm -rf ${NAME}

re: fclean ${NAME}

.PHONY: all norminette clean fclean re