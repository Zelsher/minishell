# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eboumaza <eboumaza.trav@gmail.com>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/29 18:06:01 by eboumaza          #+#    #+#              #
#    Updated: 2023/08/29 18:06:01 by eboumaza         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#clean fclean re name all Flags

CC = gcc
AR = ar
CFLAGS = -Wall -Wextra -Wextra
SRC_DIR1 = functions
SRC_DIR2 = printf
SRC_DIR2 = printf_error
OBJ_DIR = Obj
HEADER_FILE = libft.h

SRC_FILES1 = $(wildcard $(SRC_DIR1)/*.c)
SRC_FILES2 = $(wildcard $(SRC_DIR2)/*.c)
SRC_FILES3 = $(wildcard $(SRC_DIR3)/*.c)
OBJ_FILES1 = $(patsubst $(SRC_DIR1)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES1))
OBJ_FILES2 = $(patsubst $(SRC_DIR2)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES2))
OBJ_FILES3 = $(patsubst $(SRC_DIR3)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES3))

TARGET = libft.a

OBJ_FILES_WITH_HEADER = $(OBJ_FILES1) $(OBJ_FILES2) $(OBJ_FILES3)

.PHONY: all clean fclean re

all: $(OBJ_DIR) $(TARGET)

$(OBJ_DIR)/%.o: $(SRC_DIR1)/%.c $(HEADER_FILE)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR2)/%.c $(HEADER_FILE)
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJ_FILES_WITH_HEADER)
	$(AR) rcs $@ $^

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(TARGET)

re: fclean all
