CC = gcc
RM = rm -rf

CFLAGS = -Wall -Wextra -Werror\
						-I$(INCDIR)
			
LDLIBS = -lmlx\
						-framework OpenGL\
						-framework AppKit\
						-framework OpenCL

INCDIR = ./include
SRCSDIR = srcs/
SRCS = main.c buttons.c output.c mouse_events.c key_event.c ft_strcmp.c

OBJS = $(SRCS:.c=.o)
TARGET = fractol

.PHONY: all
all: $(TARGET)

$(TARGET): $(OBJS)
	@echo 'making executable'
	@$(CC) -o $@ $(OBJS) $(LDLIBS)
	@echo DONE!

$(OBJS): %.o: $(SRCSDIR)%.c $(INCDIR)/fractol.h
	@$(CC) -c $< $(CFLAGS)

$(INCDIR)/fractol.h:

.PHONY: clean
clean:
	@echo deliting object files
	@$(RM) $(OBJS)

.PHONY: fclean
fclean: clean
	@echo deliting executable files
	@$(RM) $(TARGET)

.PHONY: re
re: fclean all