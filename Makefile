# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aistok <aistok@student.42london.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/13 21:29:37 by aistok            #+#    #+#              #
#    Updated: 2025/07/13 21:29:43 by aistok           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

SRC_DIR = src
BONUS_DIR = srcb
OBJ_DIR = obj
INC_DIR = inc

LIBFT_DIR = libft
LIBFT = ${LIBFT_DIR}/libft.a

LIBMLX_DIR = minilibx-linux
LIBMLX = ${LIBMLX_DIR}/libmlx.a

# TO GET THE ALL SOURCE FILES (TEMPORARILY), UNTIL THE PROJECT BECOMES MORE STABLE
TMP_SRC_DIRS = ${shell find ${SRC_DIR} -type d}
TMP_OBJ_DIRS = ${subst ${SRC_DIR},${OBJ_DIR},${TMP_SRC_DIRS}}
TMP_FILES = ${wildcard ${addsuffix /*, ${TMP_SRC_DIRS}}}
TMP_INC_FILES = ${shell find ${INC_DIR} -name "*.h"}
SRC = ${filter %.c, $(TMP_FILES)}

#SRC =	src/main.c src/error.c src/utils.c \
#		src/parsing/check_arg.c src/parsing/parse_file.c src/parsing/check_map.c

OBJS = ${SRC:${SRC_DIR}/%.c=${OBJ_DIR}/%.o}

BONUS =
BONUS_OBJS = ${BONUS:${BONUS_DIR}/%.c=${OBJ_DIR}/%.o}

CC = gcc -g
RM = rm -rf

CFLAGS = -Wall -Wextra -Werror -O0
# -ffast-math -march=native
# -D WIDTH=1000 -D HEIGHT=1000
# -g
# -O3 -Ofast -march=native
# -Wall -Wextra -Werror

all: ${NAME}

${NAME}: ${LIBFT} ${LIBMLX} ${OBJS} ${TMP_INC_FILES}
	${CC} ${CFLAGS} ${OBJS} -o $@ -I${INC_DIR} -I${LIBFT_DIR} -L${LIBFT_DIR} -lft -L${LIBMLX_DIR} -lmlx -lXext -lX11 -lm

${OBJ_DIR}/%.o:${SRC_DIR}/%.c ${TMP_INC_FILES} | ${OBJ_DIR}
	${CC} ${CFLAGS} -I${INC_DIR} -I${LIBMLX_DIR} -I${LIBFT_DIR} -c $< -o $@

${BONUS_DIR}/%.o:${BONUS_DIR}/%.c ${TMP_INC_FILES} | ${OBJ_DIR}
	${CC} ${CFLAGS} -I${INC_DIR} -I${LIBMLX_DIR} -I${LIBFT_DIR} -c $< -o $@

${OBJ_DIR}:
	mkdir -p ${TMP_OBJ_DIRS}

${LIBFT}: | ${LIBFT_DIR}
	git submodule update --init ${LIBFT_DIR}
	@echo "compiling libft"
	make bonus -C ${LIBFT_DIR}

${LIBFT_DIR}:
	mkdir -p $@

${LIBMLX}: | ${LIBMLX_DIR}
	git submodule update --init ${LIBMLX_DIR}
	make -C ${LIBMLX_DIR}

${LIBMLX_DIR}:
	mkdir -p $@

#bonus: ${LIBFT} ${BONUS_OBJS}
#	${CC} ${CFLAGS} ${BONUS_OBJS} -o fractol -Lminilibx-linux -lmlx -lXext -lX11 -lm ${LIBFT}

run:
	./${NAME} map.cub

v valgrind: ${NAME}
	valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes -s ./cub3D "maps/bad/empty.cub"

clean:
	${RM} ${OBJ_DIR}
	make -C ${LIBFT_DIR} clean
	make -C ${LIBMLX_DIR} clean

fclean: clean
	${RM} ${NAME}
	${RM} ${LIBFT}
	${RM} ${LIBMLX}

re: fclean all

rec:
	${RM} ${OBJ_DIR}
	make all

.PHONY: all clean fclean re run
