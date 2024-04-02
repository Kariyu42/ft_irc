# === Colors === #
RED = \033[0;31m
GREY = \033[0;90m
GREEN = \033[0;32m
BLUE = \033[0;34m
RESET = \033[0m

# === Prompt === #
PROMPT	=	${GREY}[${BLUE}${NAME}${GREY}]${RESET}:

# === Compilation === #
CC		=	c++
CFLAGS	=	-Wall -Wextra -Werror -std=c++98

ifndef STRICT
	CFLAGS	+=	-pedantic
endif

ifnef DEBUG
	CFLAGS	+=	-g3
endif

# === Sources & Objects === #

# Directories
SRCS_DIR	=	./srcs
OBJS_DIR	=	./objs # Add objects to a separate directory?
HEADER	=		./inc

# Files
SRCS	=	${addprefix ${SRCS_DIR}, main.cpp \
										utils.cpp}

OBJS	=	${SRCS:.cpp=.o}

%.o: %.cpp
	@printf "${PROMPT} ${GREEN}Compiling${RESET} $<"
	@${CC} ${CFLAGS} -I ${HEADER} -c $< -o $@

# === Rules === #
NAME	=	ircserv

all:		 ${NAME}

${NAME}:	${OBJS}
	@printf "${PROMPT} ${GREEN}Linking${RESET} ${NAME}"
	@${CC} ${CFLAGS} ${OBJS} -o ${NAME}

strict:
	@${MAKE} STRICT=1

debug:
	@${MAKE} DEBUG=1

clean:
	@printf "${PROMPT} ${RED}Cleaning${RESET} objects"
	@rm -f ${OBJS}

fclean:		clean
	@printf "${PROMPT} ${RED}Cleaning${RESET} ${NAME}"
	@rm -f ${NAME}

re:			fclean all

.PHONY:		all clean fclean re strict
