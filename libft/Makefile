# MAKEFLAGS += -s
# STEP 1 create variables
# all functions that included to compilation
SRC = ft_isalpha \
	ft_isdigit \
	ft_isalnum \
	ft_isascii \
	ft_isprint \
	ft_isspace \
	ft_strlen \
	ft_memset \
	ft_bzero \
	ft_memcpy \
	ft_memmove \
	ft_strlcpy \
	ft_strlcat \
	ft_toupper \
	ft_tolower \
	ft_strchr \
	ft_strrchr \
	ft_strncmp \
	ft_memchr \
	ft_memcmp \
	ft_strnstr \
	ft_atoi \
	ft_calloc \
	ft_strdup \
	ft_substr \
	ft_strjoin \
	ft_strtrim \
	ft_split \
	ft_itoa \
	ft_strmapi \
	ft_striteri \
	ft_putchar_fd \
	ft_putstr_fd \
	ft_putendl_fd \
	ft_putnbr_fd

# bonus functions
BFN = ft_lstnew \
	ft_lstadd_front \
	ft_lstsize \
	ft_lstlast \
	ft_lstadd_back \
	ft_lstdelone \
	ft_lstclear \
	ft_lstiter \
	ft_lstmap

# compiler
CC = cc

# extra flafs for compiler
CFLAGS = -Wall -Wextra -Werror

# create a list of *.c files from list of program names
#CFL = $(SRC:%=%.c)
# create a list of objective files from list of program names
OFL = $(SRC:%=%.o)

#BCFL = $(BFN:%=%.c)
BOFL = $(BFN:%=%.o)

# target program file name
NAME = libft.a

# STEP 2 create commands
# create for each *.c file an object file
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# create archive file from *.o files
$(NAME): $(OFL)
	ar -rcs $(NAME) $(OFL)
	@echo "make: $(NAME) is compiled."


# command for compiling target archive file
all: $(NAME)

# command for deleting all object files
clean:
	rm -f $(OFL) $(BOFL)
	@echo "make: object files are cleaned up."

# command for deleting target executive file and *.o files
fclean: clean
	rm -f $(NAME)
	@echo "make: $(NAME) is deleted."

# command for deleting all compiled files and restart compiling
re: fclean all

bonus: $(NAME) $(BOFL)
# create archive file from *.o files
	ar -rcs $(NAME) $(BOFL)
	@echo "make: $(NAME) with bonus are compiled."

.PHONY:
	all, clean, fclean, re, bonus
