NAME			:= cub3d
NICKNAME		:= CUB3D

# Directories
HDR_DIR			:= include
LIB_DIR			:= lib
SRC_DIR			:= src
OBJ_DIR			:= obj

# Libft
LIBFT_DIR		:= $(LIB_DIR)/libft
LIBFT			:= $(LIBFT_DIR)/libft.a

# MLX42
MLX_DIR			:= $(LIB_DIR)/MLX
MLX				:= $(MLX_DIR)/build/libmlx42.a

# Compiler flags
CC				:= clang
CFLAGS			:= -Wall -Werror -Wextra
INCL			:= -I $(HDR_DIR)/ -I $(LIBFT_DIR)/include/ -I $(MLX_DIR)/include/MLX42/ 

ifdef FAST
	CFLAGS		+= -Ofast -flto -march=native
endif

ifdef DEBUG
	CFLAGS		+= -g -fsanitize=address
endif

# Includes
HDR_FILES :=									\
				cub3d.h							\
				colors.h						\
				map.h							\
				rays.h							\
				vector.h						\


ifeq ($(shell uname), Linux)
	MLX_FLAGS	 := -L$(MLX_DIR)/build -lmlx42 -lglfw -lm
else
	MLX_FLAGS	 := -lglfw -L "/Users/$(USER)/.brew/opt/glfw/lib/"
endif

# Files
SRC_FILES :=									\
				main.c							\
				errors.c						\
				init.c							\
				map.c							\
\
				engine/casting.c				\
				engine/rays.c					\
				engine/loop.c					\
				engine/minimap.c				\
\
				vector.c						\


SRC				:= $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJ				:= ${addprefix ${OBJ_DIR}/, ${SRC_FILES:.c=.o}}
HDR				:= $(addprefix $(HDR_DIR)/, $(HDR_FILES))

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
	@ $(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX_FLAGS) $(MLX) -o $(NAME)
	@ printf "\t\t%b%s%b\n" "$(GREEN)$(BOLD)" "[OK]" "$(RESET)"

$(OBJ_DIR)/%.o: src/%.c $(HDR) | $(OBJ_DIR)
	@ printf	"$(YELLOW)Compiling $(notdir $<)...$(RESET)"
	@ $(CC) $(CFLAGS) $(INCL) -c $< -o $@
	@ printf	"\t\t\t$(GREEN)$(BOLD)[OK]$(RESET)\n"

$(OBJ_DIR):
	@ mkdir -p $(OBJ_DIR) $(OBJ_DIR)/engine

$(LIBFT):
	@ printf "%b%s%b" "$(YELLOW)$(BOLD)" "Compiling and archiving LIBFT..." "$(RESET)"
	@ git submodule update --init --recursive $(LIBFT_DIR)
	@ make -C $(LIBFT_DIR)														> /dev/null
	@ printf "\t\t%b%s%b\n" "$(GREEN)$(BOLD)" "[OK]" "$(RESET)"

$(MLX):
	@ printf "%b%s%b" "$(YELLOW)$(BOLD)" "Compiling and archiving MLX42..." "$(RESET)"
	@ git submodule update --init --recursive $(MLX_DIR)
	@ cmake $(MLX_DIR) -B $(MLX_DIR)/build										> /dev/null
	@ make -C $(MLX_DIR)/build -j4												> /dev/null
	@ printf "\t\t%b%s%b\n" "$(GREEN)$(BOLD)" "[OK]" "$(RESET)"

open: $(NAME)
	@ ./$(NAME) maps/s.cub

norm:
	@ norminette $(HDR_DIR) $(SRC) | grep -v -e "Empty line in function" -e "Comment is invalid in this scope" -e "extra tabs before function name"

clean:
	@ echo "$(RED)$(BOLD)Cleaning LIBFT...$(RESET)"
	@ make clean -C $(LIBFT_DIR)												> /dev/null

	@ echo "$(RED)$(BOLD)Cleaning $(NICKNAME)...$(RESET)"
	@ rm -rf $(OBJ)
	@ rm -rf $(OBJ_DIR)

fclean: 
	@ echo "$(RED)$(BOLD)Fully cleaning LIBFT...$(RESET)"
	@ make fclean -C $(LIBFT_DIR)												> /dev/null

	@ echo "$(RED)$(BOLD)Fully cleaning MLX42...$(RESET)"
	@ make clean -C $(MLX_DIR)/build											> /dev/null

	@ echo "$(RED)$(BOLD)Fully cleaning $(NICKNAME)...$(RESET)"
	@ rm -rf ${NAME}
	@ rm -rf $(OBJ)
	@ rm -rf $(OBJ_DIR)

re: fclean ${NAME}

.PHONY: all submodule norm clean fclean re submodule