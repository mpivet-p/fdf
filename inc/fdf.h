#ifndef FDF_H
# define FDF_H
# define SWIN_X 840
# define SWIN_Y 840

# include "libft.h"
# include "mlx.h"
# include <math.h>
# include <stdio.h>
# include <fcntl.h>

typedef struct	s_fmlx
{
	void	*mlx;
	void	*win;
}				t_fmlx;

typedef struct	s_point
{
	int x;
	int y;
}				t_point;

typedef struct	s_fmap
{
	int		**map;
	int		size_y;
	int		size_x;
}				t_fmap;

int		fdf_parse(char *path, t_fmap *map);
int		parse_checkline(char **tab, int prev_len);
void	fdf_deltab(char ****tab);

#endif
