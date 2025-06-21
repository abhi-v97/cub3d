NAME = cub3D

SRC_DIR = src
BONUS_DIR = srcb
OBJ_DIR = obj

SRC =	src/main.c src/error.c \
		src/parsing/check_arg.c src/parsing/parse_file.c

BONUS =

OBJS = ${SRC:${SRC_DIR}/%.c=${OBJ_DIR}/%.o}
# OBJ = ${SRC:.c=.o}
# OBJS = &{addprefix &{OBJ_DIR}}

BONUS_OBJS = ${BONUS:${BONUS_DIR}/%.c=${OBJ_DIR}/%.o}

CC = cc

CFLAGS = -Wall -Wextra -Werror -O3 -ffast-math -march=native -g
# -D WIDTH=1000 -D HEIGHT=1000
# -g
# -O3 -Ofast -march=native
# -Wall -Wextra -Werror

LIBFT = libft/libft.a

${NAME}: ${LIBFT} ${OBJS}
	${CC} ${OBJS} -I. ${LIBFT} -o $@ -Lminilibx-linux -lmlx -lXext -lX11 -lm 

${OBJ_DIR}/%.o:${SRC_DIR}/%.c
	mkdir -p obj
	mkdir -p obj/parsing
	${CC} ${CFLAGS} -c $< -o $@ 

${OBJ_DIR}/%.o:${BONUS_DIR}/%.c
	mkdir -p obj
	${CC} ${CFLAGS} -c $< -o $@

${LIBFT}:
	@echo "compiling libft"
	make bonus -C libft/
	cd minilibx-linux && ./configure

all: ${NAME}

bonus: ${LIBFT} ${BONUS_OBJS}
	${CC} ${BONUS_OBJS} -o fractol -Lminilibx-linux -lmlx -lXext -lX11 -lm ${LIBFT}

clean:
	rm -f ${OBJS} ${BONUS_OBJS}
	make -C libft clean
	make -C minilibx-linux clean

fclean: clean
	rm -f ${NAME}
	rm -f libft/libft.a

re: fclean all

.PHONY: all clean fclean re
