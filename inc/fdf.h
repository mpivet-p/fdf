/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 01:32:48 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/07/02 03:10:53 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# define SWIN_X 1500
# define SWIN_Y 1200
# define SIMG_X 1500
# define SIMG_Y 1200
# define FDF_ISO 1

# include "libft.h"
# include "mlx.h"
# include <math.h>
# include <stdio.h>
# include <fcntl.h>

typedef struct	s_fmlx
{
	void			*mlx;
	void			*win;
	void			*img;
	char			*screen;
	struct s_fmap	*fmap;
}				t_fmlx;

typedef struct	s_point
{
	double x;
	double y;
	double z;
}				t_point;

typedef struct	s_fmap
{
	char	*name;
	double	rx;
	double	ry;
	double	rz;
	double	zmod;
	int		**map;
	int		size_y;
	int		size_x;
	int		scale;
	int		x_shift;
	int		y_shift;
	int		proj;
}				t_fmap;

int				parsing_tablen(char **tab);
void			fdf_disp(t_fmlx *mlx, t_fmap *ptr);
int				fdf_parse(char *path, t_fmap *map);
int				fdf_verify(char *path, t_fmap *map, char *line, int ret);
void			rotate_x(t_point *point, int theta);
void			rotate_y(t_point *point, int theta);
void			rotate_z(t_point *point, int theta);
t_point			fdf_coords(int x, int y, int z, t_fmap *map);
void			fdf_reset(t_fmap *map);
int				**delmap(int ***map, int y);

#endif
