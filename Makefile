NAME			:= cub3d
NICKNAME		:= CUB3D

# Directories
HDR_DIR			:= include
LIB_DIR			:= lib
SRC_DIR			:= src
OBJ_DIR			:= obj

# Compiler flags
CC				:= gcc
CFLAGS			:= -Wall -Werror -Wextra 
# MLX_FLAGS		:= -lglfw -L "/Users/$(USER)/.brew/opt/glfw/lib/"
# MLX_FLAGS		:= -framework Cocoa -framework OpenGL -framework IOKit -ldl -lglfw3 -pthread

ifdef DEBUG
	CFLAGS		+= -g -fsanitize=address
endif

# Includes
HDR_FILES :=									\
				cub3d.h							\
				declarations.h					\
				colors.h						\

# Libft
LIBFT_DIR		:= $(LIB_DIR)/libft
LIBFT			:= $(LIBFT_DIR)/libft.a

# MLX42
MLX_DIR			:= $(LIB_DIR)/MLX
MLX				:= $(MLX_DIR)/build/libmlx42.a
MLX_FLAGS		:= -L$(MLX_DIR)/build -lmlx42 -lglfw -lm

# Files
SRC_FILES :=									\
				main.c							\
				init.c							\
				utils.c 						\
				errors.c						\
\
				loop.c							\
\
				parsing.c						\
\
				minimap.c						\
				casting.c						\


SRC				:= $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJ				:= ${addprefix ${OBJ_DIR}/, ${SRC_FILES:.c=.o}}
HDR				:= $(addprefix $(HDR_DIR)/, $(HDR_FILES))
INC				:= -I include/ -I $(LIBFT_DIR)/include/ -I $(MLX_DIR)/include

# Colours
GREEN			:= \033[32;1m
YELLOW			:= \033[33;1m
RED				:= \033[31;1m
BOLD			:= \033[1m
RESET			:= \033[0m

# Rules
all: ${NAME}

$(NAME): $(LIBFT) $(MLX) $(OBJ)
	@ printf "%b%s%b" "$(YELLOW)$(BOLD)" "Compiling $(NICKNAME)..." "$(RESET)"
	@ gcc $(CFLAGS) $(OBJ) $(LIBFT) $(MLX_FLAGS) $(MLX) $(INC) -o $(NAME)
	@ printf "\t\t%b%s%b\n" "$(GREEN)$(BOLD)" "[OK]" "$(RESET)"

$(LIBFT):
	@ printf "%b%s%b" "$(YELLOW)$(BOLD)" "Compiling LIBFT..." "$(RESET)"
	@ make -C $(LIBFT_DIR)														> /dev/null
	@ printf "\t\t%b%s%b\n" "$(GREEN)$(BOLD)" "[OK]" "$(RESET)"

$(MLX):
	@ printf "%b%s%b" "$(YELLOW)$(BOLD)" "Compiling MLX42..." "$(RESET)"
	@ cmake $(MLX_DIR) -B $(MLX_DIR)/build										> /dev/null
	@ make -C $(MLX_DIR)/build -j4												> /dev/null
	@ printf "\t\t%b%s%b\n" "$(GREEN)$(BOLD)" "[OK]" "$(RESET)"
	
$(OBJ_DIR)/%.o: src/%.c $(HDR)
	@ mkdir -p obj
	@ gcc $(CFLAGS) -c $< -o $@ $(INC)

open: $(NAME)
	@ ./$(NAME) maps/s.cub


norm:
	@ norminette $(HDR_DIR) $(SRC)

clean:
	@ echo "$(RED)$(BOLD)Cleaning LIBFT...$(RESET)"
	@ make clean -C $(LIBFT_DIR)

	@ echo "$(RED)$(BOLD)Cleaning $(NICKNAME)...$(RESET)"
	@ rm -rf $(OBJ)
	@ rm -rf $(OBJ_DIR)

fclean: 
	@ echo "$(RED)$(BOLD)Fully cleaning LIBFT...$(RESET)"
	@ make fclean -C $(LIBFT_DIR)

	@ echo "$(RED)$(BOLD)Fully cleaning MLX42...$(RESET)"
	@ make clean -C $(MLX_DIR)/build

	@ echo "$(RED)$(BOLD)Fully cleaning $(NICKNAME)...$(RESET)"
	@ rm -rf ${NAME}
	@ rm -rf $(OBJ)
	@ rm -rf $(OBJ_DIR)

re: fclean ${NAME}

.PHONY: all norm clean fclean re libft libmlx cleanmlx