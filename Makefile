CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror -O3 #-fsanitize=address -g3

LIBDIR	=	libft
MLXDIR	=	minilibx-linux
MLXGIT	=	https://github.com/42paris/minilibx-linux.git

IFLAGS	=	-I$(LIBDIR) -I$(MLXDIR) -IHEADERS
LFLAGS	=	-L$(MLXDIR) -lX11 -lXext -lbsd -lm
LIBS	=	$(LIBDIR)/libft.a $(MLXDIR)/libmlx.a


####################################===SOURCE FILES===####################################

PARSE_DIR	=	parsing
PARSE_FILES	=	init_gamedata.c

INPUT_DIR	=	inputs
INPUT_FILES	=	handle_keyrelease.c

LOOP_DIR	=	game_loop
LOOP_FILES	=	game_loop.c

MODULES		=	PARSE	INPUT	LOOP

$(foreach M,$(MODULES), $(eval $(M)_SRCS = $(addprefix $($(M)_DIR)/, $($(M)_FILES))))

SRCDIR		=	SRCS
SRCFILES	=	main.c	close_and_exit.c
SRCS		=	$(addprefix $(SRCDIR)/, $(SRCFILES)										\
										$(foreach M,$(MODULES), $($(M)_SRCS)))

##########################################################################################


OBJDIR	=	OBJS
OBJS	=	$(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

NEEDS_REBUILD_CMD	:=															\
	for src in $(SRCS); do														\
		obj="$$(echo "$$src" | sed 's|^$(SRCDIR)|$(OBJDIR)|')";					\
		obj="$${obj%.c}.o";														\
		if [ ! -f "$$obj" ] || [ "$$src" -nt "$$obj" ]; then echo "$$src"; fi;	\
	done
NEEDS_REBUILD 	:=	$(shell $(NEEDS_REBUILD_CMD))
SRCTOTAL		:=	$(words $(NEEDS_REBUILD))
SRCNUM			:=	0

RESET		=	\033[0m
BOLD		=	\033[1m
RED			=	\033[31m
GREEN		=	\033[32m
YELLOW		=	\033[33m
ORANGE		=	\033[38;5;208m
YLLWGRN		=	\033[38;2;150;255;25m
PREVLINE	=	\033[A
RMLINE		=	\r\033[K


#########################################################################################

NAME	=	cub3D

all: $(NAME)

$(NAME): $(LIBS) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) $(LFLAGS) -o $(NAME)
	@printf "$(RMLINE)$(BOLD)$(YELLOW)$(NAME) successfully compiled\n"

$(LIBS): $(MLXDIR)
	@make -s -C $(MLXDIR) >> /dev/null 2>&1
	@make -s -C $(LIBDIR)

$(MLXDIR):
	@git clone $(MLXGIT) $(MLXDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(IFLAGS) $(DFLAGS) -c $< -o $@
	@$(eval SRCNUM := $(shell expr $(SRCNUM) + 1))
	@$(eval CALCPERCENT := $(shell echo "scale=4; $(SRCNUM) / $(SRCTOTAL) * 100" | bc))
	@$(eval PERCENT := $(shell printf "%.0f" $(CALCPERCENT)))
	@if [ $(SRCNUM) -gt 1 ]; then printf "$(PREVLINE)\r"; fi;
	@printf "$(BOLD)Compiling $(NAME): ["
	@$(eval PROGRESS := $(shell expr $(PERCENT) / 5))
	@if [ $(PERCENT) -ge 5 ]; then printf "$(GREEN)%0.s#" $(shell seq 1 $(PROGRESS)); fi;
	@$(eval CALCPADS := $(shell expr 20 - $(PROGRESS)))
	@if [ $(PERCENT) -lt 100 ]; then printf "$(RESET)$(BOLD)%0.s-" $(shell seq 1 $(CALCPADS)); fi;
	@printf "$(RESET)$(BOLD)] "
	@if [ $(PERCENT) -lt 25  ]; then	\
		printf "$(RED)";				\
	elif [ $(PERCENT) -lt 50 ]; then	\
		printf "$(ORANGE)";				\
	elif [ $(PERCENT) -lt 75 ]; then	\
		printf "$(BOLD)$(YELLOW)";		\
	elif [ $(PERCENT) -lt 100 ]; then	\
		printf "$(BOLD)$(YLLWGRN)";		\
	else								\
		printf "$(BOLD)$(GREEN)"; fi;
	@printf "%d%% $(RESET)\n" $(PERCENT)
	@printf "Compiling %-34s" $(notdir $@)

clean:
	@printf "$(RED)"
	@if [ -d $(MLXDIR) ]; then						\
		rm -rf $(MLXDIR);							\
		printf "Removed $(MLXDIR)\n";				\
	else											\
		printf "$(MLXDIR) not found\n"; fi;
	@make fclean -s -C $(LIBDIR)
	@printf "$(RED)"
	@if [ -d $(OBJDIR) ]; then						\
		rm -rf $(OBJDIR);							\
		printf "Removed $(NAME) OBJS directory\n";	\
	else											\
		printf "$(NAME) objects not found\n"; fi;
	@printf "$(RESET)"

fclean: clean
	@printf "$(RED)"
	@if [ -f $(NAME) ]; then				\
		rm -f $(NAME);						\
		printf "Removed $(NAME)\n";			\
	else									\
		printf "$(NAME) not found\n"; fi;
	@printf "$(RESET)"

re: fclean
	@make -s all

bonus: all

.PHONY: all clean fclean re bonus
