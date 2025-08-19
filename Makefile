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

CC = gcc -g
RM = rm -rf

CFLAGS = -Wall -Wextra -Werror -O0
# -ffast-math -march=native
# -D WIDTH=1000 -D HEIGHT=1000
# -g
# -O3 -Ofast -march=native
# -Wall -Wextra -Werror

SRC_ROOT_DIR		= src
SRC_MANDATORY_DIR	= ${SRC_ROOT_DIR}/mandatory
SRC_BONUS_DIR 		= ${SRC_ROOT_DIR}/bonus
SRC_DIR				= ${SRC_MANDATORY_DIR}

OBJ_ROOT_DIR		= obj
OBJ_MANDATORY_DIR	= ${OBJ_ROOT_DIR}/mandatory
OBJ_BONUS_DIR		= ${OBJ_ROOT_DIR}/bonus
OBJ_DIR				= ${OBJ_MANDATORY_DIR}

INC_ROOT_DIR		= inc
INC_MANDATORY_DIR	= ${INC_ROOT_DIR}/mandatory
INC_BONUS_DIR 		= ${INC_ROOT_DIR}/bonus
INC_DIR				= ${INC_MANDATORY_DIR}

LIBFT_DIR = libft
LIBFT = ${LIBFT_DIR}/libft.a

LIBMLX_DIR = minilibx-linux
LIBMLX = ${LIBMLX_DIR}/libmlx.a

INC_FILES = ${INC_DIR}/cub3d.h

# assume mandatory will be built
CURRENT_VERSION = .mandatory
OTHER_VERSION = .bonus

#if bonus is an argument for make
ifneq ($(filter bonus,$(MAKECMDGOALS)),)
SRC_DIR			:=	${SRC_BONUS_DIR}
OBJ_DIR			:=	${OBJ_BONUS_DIR}
INC_DIR			:=	${INC_BONUS_DIR}
INC_FILES		:=	${INC_BONUS_DIR}/cub3d.h
CURRENT_VERSION	:= .bonus
OTHER_VERSION	:= .mandatory
endif

SRC_DIRS = \
	${SRC_DIR} \
	${SRC_DIR}/parsing \
	${SRC_DIR}/render

OBJ_DIRS = ${subst ${SRC_DIR},${OBJ_DIR},${SRC_DIRS}}

SRC_MANDATORY = \
	${SRC_MANDATORY_DIR}/cleanup.c \
	${SRC_MANDATORY_DIR}/debug.c \
	${SRC_MANDATORY_DIR}/error.c \
	${SRC_MANDATORY_DIR}/fps.c \
	${SRC_MANDATORY_DIR}/init.c \
	${SRC_MANDATORY_DIR}/key_events.c \
	${SRC_MANDATORY_DIR}/main.c \
	${SRC_MANDATORY_DIR}/map_functions.c \
	${SRC_MANDATORY_DIR}/program_name.c \
	${SRC_MANDATORY_DIR}/utils.c \
	${SRC_MANDATORY_DIR}/parsing/check_arg.c \
	${SRC_MANDATORY_DIR}/parsing/check_map_bounds.c \
	${SRC_MANDATORY_DIR}/parsing/check_map.c \
	${SRC_MANDATORY_DIR}/parsing/map_fill.c \
	${SRC_MANDATORY_DIR}/parsing/parse_file.c \
	${SRC_MANDATORY_DIR}/parsing/parse_textures.c \
	${SRC_MANDATORY_DIR}/parsing/set_textures.c \
	${SRC_MANDATORY_DIR}/render/draw_wall.c \
	${SRC_MANDATORY_DIR}/render/put_pixel.c \
	${SRC_MANDATORY_DIR}/render/ray_create.c \
	${SRC_MANDATORY_DIR}/render/render_loop.c

SRC_BONUS = \
	${SRC_BONUS_DIR}/cleanup.c \
	${SRC_BONUS_DIR}/debug.c \
	${SRC_BONUS_DIR}/error.c \
	${SRC_BONUS_DIR}/fps.c \
	${SRC_BONUS_DIR}/init.c \
	${SRC_BONUS_DIR}/key_events.c \
	${SRC_BONUS_DIR}/key_helpers.c \
	${SRC_BONUS_DIR}/main.c \
	${SRC_BONUS_DIR}/map_functions.c \
	${SRC_BONUS_DIR}/mouse_events.c \
	${SRC_BONUS_DIR}/program_name.c \
	${SRC_BONUS_DIR}/sprite.c \
	${SRC_BONUS_DIR}/utils.c \
	${SRC_BONUS_DIR}/parsing/check_arg.c \
	${SRC_BONUS_DIR}/parsing/check_map_bounds.c \
	${SRC_BONUS_DIR}/parsing/check_map.c \
	${SRC_BONUS_DIR}/parsing/map_fill.c \
	${SRC_BONUS_DIR}/parsing/parse_file.c \
	${SRC_BONUS_DIR}/parsing/parse_textures.c \
	${SRC_BONUS_DIR}/parsing/set_sprite.c \
	${SRC_BONUS_DIR}/parsing/set_textures.c \
	${SRC_BONUS_DIR}/render/door.c \
	${SRC_BONUS_DIR}/render/draw_wall.c \
	${SRC_BONUS_DIR}/render/floorcast.c \
	${SRC_BONUS_DIR}/render/minimap.c \
	${SRC_BONUS_DIR}/render/put_pixel.c \
	${SRC_BONUS_DIR}/render/ray_create.c \
	${SRC_BONUS_DIR}/render/render_loop.c \
	${SRC_BONUS_DIR}/render/weapon_anim.c \
	${SRC_BONUS_DIR}/render/weapon.c

# assume mandatory will be built
SRC = ${SRC_MANDATORY}

#if bonus is an argument for make
ifneq ($(filter bonus,$(MAKECMDGOALS)),)
SRC		:=	${SRC_BONUS}
#CFLAGS	:= 	$(CFLAGS) -D BONUS=1
endif

OBJS = ${SRC:${SRC_DIR}/%.c=${OBJ_DIR}/%.o}

all: ${NAME}
bonus: all

${NAME}: ${CURRENT_VERSION} ${LIBFT} ${LIBMLX} ${OBJS} ${INC_FILES}
	${CC} ${CFLAGS} ${OBJS} -o $@ -I${INC_DIR} -I${LIBFT_DIR} -L${LIBFT_DIR} -lft -L${LIBMLX_DIR} -lmlx -lXext -lX11 -lm

${OBJ_DIR}/%.o:${SRC_DIR}/%.c ${INC_FILES} | ${OBJ_DIR}
	${CC} ${CFLAGS} -I${INC_DIR} -I${LIBMLX_DIR} -I${LIBFT_DIR} -c $< -o $@

${CURRENT_VERSION}:
	@${RM} ${OTHER_VERSION}
	@touch ${CURRENT_VERSION}

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

v valgrind: ${NAME}
	valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes -s ./cub3D "maps/mandatory/bad/empty.cub"

clean:
	${RM} ${OBJ_ROOT_DIR}
	make -C ${LIBFT_DIR} clean
	make -C ${LIBMLX_DIR} clean
	${RM} ${CURRENT_VERSION} ${OTHER_VERSION}

clean2:
	${RM} ${OBJ_ROOT_DIR}
	${RM} ${CURRENT_VERSION} ${OTHER_VERSION}

fclean: clean
	${RM} ${NAME}
	${RM} ${LIBFT}
	${RM} ${LIBMLX}

fclean2: clean2
	${RM} ${NAME}

re: fclean all

# only remove the obj dir (and leave the libft and minilibx-linux as is)
re2: fclean2 all

.PHONY: all clean clean2 fclean fclean2 re re2 bonus
