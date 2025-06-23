NAME = cub3D

SRC_DIR = src
BONUS_DIR = srcb
OBJ_DIR = obj

# TO GET THE ALL SOURCE FILES (TEMPORARILY), UNTIL THE PROJECT BECOMES MORE STABLE
TMP_SRC_DIRS = ${shell find $(SRC_DIR) -type d}
TMP_OBJ_DIRS = ${TMP_SRC_DIRS:${SRC_DIR}/%=${OBJ_DIR}/%}
TMP_FILES = ${wildcard ${addsuffix /*, ${TMP_SRC_DIRS}}}
SRC = ${filter %.c, $(TMP_FILES)}

#SRC =	src/main.c src/error.c src/utils.c \
#		src/parsing/check_arg.c src/parsing/parse_file.c src/parsing/check_map.c

BONUS =

OBJS = ${SRC:${SRC_DIR}/%.c=${OBJ_DIR}/%.o}
# OBJ = ${SRC:.c=.o}
# OBJS = &{addprefix &{OBJ_DIR}}

BONUS_OBJS = ${BONUS:${BONUS_DIR}/%.c=${OBJ_DIR}/%.o}

CC = gcc -g
RM = rm -rf

CFLAGS = -Wall -Wextra -Werror -O0
# -ffast-math -march=native
# -D WIDTH=1000 -D HEIGHT=1000
# -g
# -O3 -Ofast -march=native
# -Wall -Wextra -Werror

LIBFT = libft/libft.a

${NAME}: ${LIBFT} ${OBJS}
	${CC} ${OBJS} -I. ${LIBFT} -o $@ -Lminilibx-linux -lmlx -lXext -lX11 -lm 

${OBJ_DIR}/%.o:${SRC_DIR}/%.c | ${OBJ_DIR}
	${CC} ${CFLAGS} -c $< -o $@ 

${OBJ_DIR}/%.o:${BONUS_DIR}/%.c | ${OBJ_DIR}
	${CC} ${CFLAGS} -c $< -o $@

${OBJ_DIR}:
	mkdir -p ${TMP_OBJ_DIRS}

${LIBFT}:
	@echo "compiling libft"
	make bonus -C libft/
	cd minilibx-linux && ./configure

all: ${NAME}

#bonus: ${LIBFT} ${BONUS_OBJS}
#	${CC} ${BONUS_OBJS} -o fractol -Lminilibx-linux -lmlx -lXext -lX11 -lm ${LIBFT}

clean:
	${RM} ${OBJ_DIR}
	make -C libft clean
	make -C minilibx-linux clean

fclean: clean
	${RM} ${NAME}
	${RM} libft/libft.a

re: fclean all

.PHONY: all clean fclean re