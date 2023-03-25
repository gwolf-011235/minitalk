# text effects
RESET := \033[0m
BOLD := \033[1m
BLACK := \033[30m
GREEN := \033[32m
YELLOW := \033[33m
RED := \033[31m
BLUE := \033[34m
CYAN := \033[36m
CYAN_B := \033[46m

# directories
SRC_DIR := src
SRC_DIR_B := src/bonus
OBJ_DIR := obj
OBJ_DIR_B := obj/bonus
LIB_DIR := lib
LIB_DIR_FT := $(LIB_DIR)/libft
INC_DIR := include

# include
INC_SERVER := $(INC_DIR)/server.h
INC_CLIENT := $(INC_DIR)/client.h
INC := -I $(INC_DIR) -I lib/libft/include

# libraries
LIB_FT := -L $(LIB_DIR_FT) -l ft 

# compiling
CC := clang
CFLAGS = -Wall -Werror -Wextra
COMPILE = $(CC) $(CFLAGS) $(INC)

# targets
NAME_SERVER := server
NAME_CLIENT := client
LIBFT := $(LIB_DIR_FT)/libft.a

# progress bar
HIT_TOTAL = $(words $(SRCS))
HIT_COUNT = $(eval HIT_N != expr ${HIT_N} + 1)${HIT_N}
ECHO = printf "\033[2K\r[`expr ${HIT_COUNT} '*' 100 / ${HIT_TOTAL}`%%] %s"

# source files
SRC_SERVER :=  server.c
SRC_CLIENT :=  client.c

OBJ_SERVER := $(SRC_SERVER:.c=.o)
OBJ_CLIENT := $(SRC_CLIENT:.c=.o)

SRCS_SERVER := $(addprefix $(SRC_DIR)/, $(SRC_SERVER))
SRCS_CLIENT := $(addprefix $(SRC_DIR)/, $(SRC_CLIENT))

OBJS_SERVER := $(addprefix $(OBJ_DIR)/, $(OBJ_SERVER))
OBJS_CLIENT := $(addprefix $(OBJ_DIR)/, $(OBJ_CLIENT))

.PHONY: all, clean, fclean, re, debug, bonus, re_bonus
.SILENT:

all: $(NAME_SERVER) $(NAME_CLIENT)

$(NAME_SERVER): $(LIBFT) $(OBJS_SERVER) $(INC_SERVER)
	$(COMPILE) $(OBJS_SERVER) $(LIB_FT) -o $@
	echo "$(GREEN)$(NAME_SERVER) created!$(RESET)"

$(NAME_CLIENT): $(LIBFT) $(OBJS_CLIENT) $(INC_CLIENT)
	$(COMPILE) $(OBJS_CLIENT) $(LIB_FT) -o $@
	echo "$(GREEN)$(NAME_CLIENT) created!$(RESET)"

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR) message
	$(COMPILE) -c $< -o $@

message:
	printf "$(YELLOW)$(BOLD)compilation$(RESET) [$(BLUE)minitalk$(RESET)]\n"


$(LIBFT):
	printf "$(YELLOW)$(BOLD)compilation$(RESET) [$(BLUE)libft$(RESET)]\n"
	$(MAKE) -C $(LIB_DIR)/libft

clean: 
	printf "$(YELLOW)$(BOLD)clean$(RESET) [$(BLUE)minitalk$(RESET)]\n"
	rm -rf $(OBJ_DIR)
	printf "$(RED)removed subdir $(OBJ_DIR)$(RESET)\n"

fclean: clean
	rm -rf $(NAME_SERVER)
	rm -rf $(NAME_CLIENT)
	printf "$(RED)removed bin $(NAME_SERVER)$(RESET)\n"
	printf "$(RED)removed bin $(NAME_CLIENT)$(RESET)\n"
	printf "$(YELLOW)$(BOLD)clean$(RESET) [$(BLUE)libft$(RESET)]\n"
	$(MAKE) --no-print-directory -C $(LIB_DIR_FT) fclean

re: fclean all
	
re_bonus: fclean bonus

