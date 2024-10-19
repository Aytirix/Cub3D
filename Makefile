NAME = cub3D
OBJDIR = objets
MLX = .mlx
SRC = 	main.c \
		utils.c \
		movement.c \
		movement2.c \
		game_loop.c \
		game_loop2.c \
		rendering.c \
		parsing/parsing.c \
		parsing/parsing_map.c \
		parsing/parsing_rgb.c \

OBJ = $(addprefix $(OBJDIR)/,$(SRC:.c=.o))
LIBFT = Libft
LIBFT_A = $(LIBFT)/libft.a
FLAGS = -g3 #-fsanitize=address #-Wall -Wextra -Werror
LIBS = -L$(MLX) -lmlx -L$(LIBFT) -lft -lXext -lX11 -lm

# Colors
RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
MAGENTA = \033[0;35m
CYAN = \033[0;36m
RESET = \033[0m

all: $(LIBFT_A) $(NAME)

$(LIBFT_A):
	@$(MAKE) -C $(LIBFT) --no-print-directory

$(NAME): $(OBJ)
	@echo "$(GREEN)Linking $(NAME) with libft...$(RESET)"
	@$(CC) $(FLAGS) -I$(MLX) -I$(LIBFT) $(OBJ) -o $@ $(LIBS)
	@echo "$(BLUE)$(NAME) linked successfully!$(RESET)"

recompile_objs: clean_objs $(OBJ)

$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@echo "$(CYAN)Compiling $< into $@...$(RESET)"
	@$(CC) $(FLAGS) -I$(MLX) -I$(LIBFT) -c $< -o $@

clean_objs:
	@echo "$(MAGENTA)Cleaning object files...$(RESET)"
	@rm -rf $(OBJDIR)

clean: clean_objs
	@$(MAKE) -C $(LIBFT) clean --no-print-directory

fclean: clean
	@echo "$(RED)Cleaning all files...$(RESET)"
	@rm -f $(NAME)
	@rm -rf $(OBJDIR)
	@$(MAKE) -C $(LIBFT) fclean --no-print-directory

re: fclean all

.PHONY: all clean clean_objs fclean re recompile_objs
