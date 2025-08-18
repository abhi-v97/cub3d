# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: avalsang <avalsang@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/13 21:29:37 by aistok            #+#    #+#              #
#    Updated: 2025/08/16 14:07:36 by avalsang         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
NAME_BONUS = cub3D_bonus

CC = gcc -g
RM = rm -rf

CFLAGS = -Wall -Wextra -Werror -O0
# -ffast-math -march=native
# -D WIDTH=1000 -D HEIGHT=1000
# -g
# -O3 -Ofast -march=native
# -Wall -Wextra -Werror

SRC_DIR = src
SRC_BONUS_DIR = srcb
OBJ_DIR = obj
OBJ_BONUS_DIR = objb
INC_DIR = inc
INC_BONUS_DIR = ${INC_DIR}/bonus

LIBFT_DIR = libft
LIBFT = ${LIBFT_DIR}/libft.a

LIBMLX_DIR = minilibx-linux
LIBMLX = ${LIBMLX_DIR}/libmlx.a

#TMP_INC_FILES = ${shell find ${INC_DIR} -name "*.h"}
INC_FILES = ${INC_DIR}/cub3d.h

#if bonus is an argument for make
ifneq ($(filter bonus,$(MAKECMDGOALS)),)
SRC_DIR			:=	${SRC_BONUS_DIR}
OBJ_DIR			:=	${OBJ_BONUS_DIR}
INC_FILES		:=	${subst ${INC_DIR},${INC_BONUS_DIR},${INC_FILES}}
INC_DIR			:=	${INC_BONUS_DIR}
endif

# TO GET THE ALL SOURCE FILES (TEMPORARILY), UNTIL THE PROJECT BECOMES MORE STABLE
#TMP_SRC_DIRS = ${shell find ${SRC_DIR} -type d}
SRC_DIRS = ${SRC_DIR} \
		   ${SRC_DIR}/parsing \
		   ${SRC_DIR}/render

#SRCB_DIRS = ${subst ${SRC_DIR},${SRCB_DIR},${SRC_DIRS}}

#TMP_OBJ_DIRS = ${subst ${SRC_DIR},${OBJ_DIR},${TMP_SRC_DIRS}}
OBJ_DIRS = ${subst ${SRC_DIR},${OBJ_DIR},${SRC_DIRS}}

#TMP_FILES = ${wildcard ${addsuffix /*, ${TMP_SRC_DIRS}}}
SRC = \
	${SRC_DIR}/cleanup.c \
	${SRC_DIR}/debug.c \
	${SRC_DIR}/error.c \
	${SRC_DIR}/fps.c \
	${SRC_DIR}/init.c \
	${SRC_DIR}/key_events.c \
	${SRC_DIR}/main.c \
	${SRC_DIR}/map_functions.c \
	${SRC_DIR}/program_name.c \
	${SRC_DIR}/utils.c \
	${SRC_DIR}/parsing/check_arg.c \
	${SRC_DIR}/parsing/check_map_bounds.c \
	${SRC_DIR}/parsing/check_map.c \
	${SRC_DIR}/parsing/map_fill.c \
	${SRC_DIR}/parsing/parse_file.c \
	${SRC_DIR}/parsing/parse_textures.c \
	${SRC_DIR}/parsing/set_textures.c \
	${SRC_DIR}/render/draw_wall.c \
	${SRC_DIR}/render/put_pixel.c \
	${SRC_DIR}/render/ray_create.c \
	${SRC_DIR}/render/render_loop.c

SRCB = \
	${SRC_DIR}/cleanup.c \
	${SRC_DIR}/debug.c \
	${SRC_DIR}/error.c \
	${SRC_DIR}/fps.c \
	${SRC_DIR}/init.c \
	${SRC_DIR}/key_events.c \
	${SRC_DIR}/key_helpers.c \
	${SRC_DIR}/main.c \
	${SRC_DIR}/map_functions.c \
	${SRC_DIR}/mouse_events.c \
	${SRC_DIR}/program_name.c \
	${SRC_DIR}/sprite.c \
	${SRC_DIR}/utils.c \
	${SRC_DIR}/parsing/check_arg.c \
	${SRC_DIR}/parsing/check_map_bounds.c \
	${SRC_DIR}/parsing/check_map.c \
	${SRC_DIR}/parsing/map_fill.c \
	${SRC_DIR}/parsing/parse_file.c \
	${SRC_DIR}/parsing/parse_textures.c \
	${SRC_DIR}/parsing/set_sprite.c \
	${SRC_DIR}/parsing/set_textures.c \
	${SRC_DIR}/render/door.c \
	${SRC_DIR}/render/draw_wall.c \
	${SRC_DIR}/render/floorcast.c \
	${SRC_DIR}/render/minimap.c \
	${SRC_DIR}/render/put_pixel.c \
	${SRC_DIR}/render/ray_create.c \
	${SRC_DIR}/render/render_loop.c \
	${SRC_DIR}/render/weapon_anim.c \
	${SRC_DIR}/render/weapon.c

#if bonus is an argument for make
ifneq ($(filter bonus,$(MAKECMDGOALS)),)
SRC		:=	${SRCB}
#CFLAGS	:= 	$(CFLAGS) -D BONUS=1
endif

OBJS = ${SRC:${SRC_DIR}/%.c=${OBJ_DIR}/%.o}

#BONUS =
#BONUS_OBJS = ${BONUS:${BONUS_DIR}/%.c=${OBJ_DIR}/%.o}

all: ${NAME}
bonus: all

${NAME}: ${LIBFT} ${LIBMLX} ${OBJS} ${INC_FILES}
	${CC} ${CFLAGS} ${OBJS} -o $@ -I${INC_DIR} -I${LIBFT_DIR} -L${LIBFT_DIR} -lft -L${LIBMLX_DIR} -lmlx -lXext -lX11 -lm

${OBJ_DIR}/%.o:${SRC_DIR}/%.c ${INC_FILES} | ${OBJ_DIR}
	${CC} ${CFLAGS} -I${INC_DIR} -I${LIBMLX_DIR} -I${LIBFT_DIR} -c $< -o $@

#${BONUS_DIR}/%.o:${BONUS_DIR}/%.c ${INC_FILES} | ${OBJ_DIR}
#	${CC} ${CFLAGS} -I${INC_DIR} -I${LIBMLX_DIR} -I${LIBFT_DIR} -c $< -o $@

${OBJ_DIR}:
	mkdir -p ${OBJ_DIRS}

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
	./${NAME} maps/good/wolf.cub

v valgrind: ${NAME}
	valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes -s ./cub3D "maps/bad/empty.cub"

clean:
	${RM} ${OBJ_DIR}
	make -C ${LIBFT_DIR} clean
	make -C ${LIBMLX_DIR} clean

clean2:
	${RM} ${OBJ_DIR}

fclean: clean
	${RM} ${NAME}
	${RM} ${LIBFT}
	${RM} ${LIBMLX}

fclean2: clean2
	${RM} ${NAME}

re: fclean all

# only remove the obj dir (and leave the libft and minilibx-linux as is)
re2: fclean2 all

.PHONY: all clean clean2 fclean fclean2 re re2 run bonus
