#ifndef FDF_H
# define FDF_H
# define SWIN_X 1000
# define SWIN_Y 840

# include "libft.h"
# include "mlx.h"
# include <math.h>
# include <stdio.h>
# include <fcntl.h>

typedef struct	s_fmlx
{
	void			*mlx;
	void			*win;
	struct s_fmap	*fmap;
}				t_fmlx;

typedef struct	s_point
{
	int x;
	int y;
	int z;
}				t_point;

typedef struct	s_fmap
{
	int		**map;
	int		size_y;
	int		size_x;
	int 	scale;
	int		x_shift;
	int		y_shift;
	double	rx;
	double	ry;
	double	rz;
}				t_fmap;

int		fdf_parse(char *path, t_fmap *map);
int		fdf_verify(char *path, t_fmap *map);

#endif
