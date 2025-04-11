NAME 					= philo

CC						= gcc

STD_FLAGS				= -Wall -Wextra -Werror

SRCS					= src/main.c \
						  src/data_init.c \
						  src/dinner.c \
						  src/eat.c \
						  src/error_exit.c \
						  src/get_long.c \
						  src/get_status.c \
						  src/parse_input.c \
						  src/safe_malloc.c \
						  src/safe_mutex.c \
						  src/safe_thread.c \
						  src/set_long.c \
						  src/set_status.c \
						  src/sleep.c \
						  src/think.c \
						  src/timestamp.c \
						  src/wait_all_threads_ready.c \
						  src/write_action.c \
						  src/free_all.c \
						  src/monitoring.c \
						  src/increase_long.c \

OBJS					= ${SRCS:.c=.o}

REMOVE					= rm -f ${OBJS}; rm -f philo; rm -f *.out

all:					${NAME}

${NAME}:
						${CC} ${SRCS} ${STD_FLAGS} -o ${NAME}

clean:
						${REMOVE}

fclean:					clean
						make fclean
						
re:						clean all

.PHONY:					all clean fclean re