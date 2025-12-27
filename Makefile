NAME	:= mandelbrot
CFLAGS	:= -Wextra -Wall -Werror -Wunreachable-code -O3 -ffast-math
MLX_DIR	:= ./MLX42
MLX_LIB := $(MLX_DIR)/build/libmlx42.a
INCLUDE	:= -I./include -I$(MLX_DIR)/include
LIBS	:= $(MLX_LIB) -ldl -lglfw -pthread -lm
SRCS	:= $(wildcard src/*.c)
OBJS	:= ${SRCS:src/%.c=obj/%.o}

all: $(MLX_LIB) $(NAME)
	# ./mandelbrot

$(NAME): $(OBJS) $(MLX_LIB)
	$(CC) $(OBJS) $(LIBS) $(INCLUDE) -o $(NAME)

mlx: $(MLX_LIB)

d: $(MLX_DIR)
	$(CC) $(SRCS) $(LIBS) -g $(INCLUDE)

$(MLX_LIB): $(MLX_DIR)
	@cmake $(MLX_DIR)/ -B $(MLX_DIR)/build && make -C $(MLX_DIR)/build -j4

$(MLX_DIR):
	git clone https://github.com/codam-coding-college/MLX42.git

obj/%.o: src/%.c ./include/fractal.h
	mkdir -p obj
	$(CC) $(CFLAGS) -c $< $(INCLUDE) -o $@

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)
	rm -rf $(MLX_DIR)
	rm -rf obj
	rm -f compile_commands.json

re: fclean all

.SECONDARY: $(OBJS)
.PHONY: all clean fclean re d mlx
