# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kei2003730 <kei2003730@student.42.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/18 21:11:39 by kjikuhar          #+#    #+#              #
#    Updated: 2025/07/14 08:35:36 by kei2003730       ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#-----------------------------------------------------------------------------
#> options
#-----------------------------------------------------------------------------
BLACK	:=	\033[30m
RED		:=	\033[31m
GREEN	:=	\033[32m
YELLOW	:=	\033[33m
BLUE	:=	\033[96m
MAGENTA	:=	\033[38;5;206m
CYAN	:=	\033[36m
WHITE	:=	\033[37m
RESET	:=	\033[0m
BOLD	:=	\033[1m
DIM		:=	\033[2m
ITALIC	:=	\033[3m
UNDER	:=	\033[4m
BLINK	:=	\033[5m
REVERSE	:=	\033[7m
HIDDEN	:=	\033[8m
PINK	:=	\033[35m

#-----------------------------------------------------------------------------

#▸ variables

#-----------------------------------------------------------------------------

NAME		:=	push_swap

#─ compile config ────────────────────────────────────────────────────────────

CC			:=	cc
# CFLAGS		:=	-Wall -Wextra -Werror -Iincludes -Ilibft
CFLAGS		:=	-Iincludes -Ilibft -lm
# CFLAGS		:=	-Wall -Wextra -Werror -Iincludes -Ilibft -fsanitize=address
T_CFLAGS	:=	-Iincludes -Ilibft

#─ directory name ────────────────────────────────────────────────────────────

SRCDIR		:=	src
MAND 		:=	mandatory
OBJDIR		:=	obj
LIBFT_DIR	:=	libft
LIBFT_A		:=	$(LIBFT_DIR)/libft.a

#─ sources & objects ─────────────────────────────────────────────────────────

#mandatory sources
SRCS_MAND	:=	src/mandatory/01_is_valid_args.c \
				src/mandatory/02_init_info.c \
				src/mandatory/00_main.c \
				src/mandatory/03_parse_args.c \
				src/mandatory/04_sort_stacks.c \
				src/mandatory/04_0_operation.c \
				src/mandatory/04_0_sort_small_stack_constrained.c \
				src/mandatory/05_print_operation.c \
				src/mandatory/99_deque_utils_2.c \
				src/mandatory/99_deque_utils_1.c
# 				src/bonus/checker.c

ifeq ($(MAKECMDGOALS),bubble)
SRCS_MAND	+=	src/mandatory/04_1_bubble_sort.c
else ifeq ($(MAKECMDGOALS),insertion)
SRCS_MAND	+=	src/mandatory/04_2_insertion_sort.c
else ifeq ($(MAKECMDGOALS),insertion_optimized)
SRCS_MAND	+=	src/mandatory/04_2_insertion_sort_optimized.c
else ifeq ($(MAKECMDGOALS),selection)
SRCS_MAND	+=	src/mandatory/04_3_selection_sort.c
else ifeq ($(MAKECMDGOALS),radix)
SRCS_MAND	+=	src/mandatory/04_4_radix_sort.c
else ifeq ($(MAKECMDGOALS),quick)
SRCS_MAND	+=	src/mandatory/04_5_quick_sort.c
else ifeq ($(MAKECMDGOALS),quick_3)
SRCS_MAND	+=	src/mandatory/04_5_quick_sort_3way.c
else ifeq ($(MAKECMDGOALS),chunk)
SRCS_MAND	+=	src/mandatory/04_6_chunk_sort_0_main.c \
				src/mandatory/04_6_chunk_sort_1_splitter.c \
				src/mandatory/04_6_chunk_sort_2_individual.c \
				src/mandatory/04_6_chunk_sort_99_utils.c
else ifeq ($(MAKECMDGOALS),LIS)
SRCS_MAND	+=	src/mandatory/04_9_LISsort.c
else
SRCS_MAND	+=	src/mandatory/04_1_bubble_sort.c
endif

#bonus sources

SRCS_BONUS	:=

#object files

OBJS_MAND	:=	$(SRCS_MAND:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
OBJS_BONUS	:=	$(SRCS_BONUS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
# OBJS	 	:=	$(OBJS_MAND) $(OBJS_BONUS)

#test

TEST        := test/test_printf.c
OBJ_T       := $(TEST:.c=.o)

#-----------------------------------------------------------------------------

#▸ rules

#-----------------------------------------------------------------------------

all: $(NAME)

bubble: fclean all

insertion: fclean all

insertion_optimized: fclean all

selection: fclean all

radix: fclean all

quick: fclean all

quick_3: fclean all

chunk: fclean all

LIS: fclean all

$(NAME): $(LIBFT_A) $(OBJS_MAND)
	@echo "Compiled with $(GREEN)$(BOLD)$(CFLAGS)$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS_MAND) -o $@ $(LIBFT_A) -lm
	@echo "$(YELLOW)$(BOLD)========================================="
	@echo "    You can use My $(NAME)!!"
	@echo "=========================================$(RESET)"

# compile object files

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	@echo "Compiled ✅ $(WHITE) $(BOLD) $^ $(RESET)"
	@$(CC) $(CFLAGS) -c -o $@ $^ -lm

# libft
$(LIBFT_A):
	@$(MAKE) -C $(LIBFT_DIR)

# clean targets
clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	@rm -rf $(OBJDIR)

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@rm -f $(NAME)

re: fclean all

# bonus: $(LIBFT_A) $(OBJS_BONUS)
# 	@cp $(LIBFT_A) $(NAME)
# 	@echo "Compiled with $(GREEN)$(BOLD)$(CFLAGS)$(RESET)"
# 	@ar rcs $(NAME) $(OBJS_BONUS)
# 	@echo "$(YELLOW)$(BOLD)========================================="
# 	@echo "  You can use My Bonus_$(NAME)!!"
# 	@echo "=========================================$(RESET)"

# test: $(NAME)
# 	@norminette $(SRCS_MAND) $(SRCS_BONUS)
# 	@$(CC) $(T_CFLAGS) $(TEST) $(NAME) -o $(OBJ_T)
# 	@valgrind --leak-check=full ./$(OBJ_T)
# 	@rm $(OBJ_T)
# 	fclean

# test_bonus: bonus
# 	@$(CC) $(T_CFLAGS) $(TEST) $(NAME) -o $(OBJ_T)
# 	@valgrind --leak-check=full ./$(OBJ_T)
# 	@rm $(OBJ_T)
# 	fclean

.PHONY: all clean fclean re bonus test
