all :
	gcc -Wall -Wextra -Werror -Llibs/mlx_mms -lmlx -framework OpenGL -framework AppKit -L. -lft -o so_long ./main.c \
																					./utils/parser.c \
																					./utils/error.c \
																					./utils/gnl/get_next_line.c \
																					./utils/utils.c \
																					./utils/sprites.c \
																					./utils/get_pixel.c \
