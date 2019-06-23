/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 00:26:11 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/06/23 08:31:52 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fdf_draw_line(t_fmlx *ptr, t_point one, t_point two, int color)
{
	t_point	delta;
	t_point	s;
	double	slope;
	double	pitch;

	pitch = 0.0;
	slope = 0.0;
	delta.x = two.x - one.x;
	s.x = (delta.x < 0) ? -1 : 1;
	delta.y = two.y - one.y;
	s.y = (delta.y < 0) ? -1 : 1;
	if (fabs((double)delta.y) < fabs((double)delta.x))
	{
		slope = (double)delta.y / (double)delta.x;
		pitch = (double)one.y - (slope * (double)one.x);
		while (one.x != two.x)
		{
			mlx_pixel_put(ptr->mlx, ptr->win, one.x,
					(int)lround((slope * (double)one.x) + pitch), color);
			one.x += s.x;
		}
		return ;
	}
	slope = (double)delta.x / (double)delta.y;
	pitch = (double)one.x - (slope * (double)one.y);
	while (one.y != two.y)
	{
		mlx_pixel_put(ptr->mlx, ptr->win,
				(int)lround((slope * (double)one.y) + pitch), one.y, color);
		one.y += s.y;
	}
}

t_point	fdf_point(int x, int y)
{
	t_point ret;

	ret.x = x;
	ret.y = y;
	return (ret);
}

t_point	fdf_coords(int x, int y)
{
	t_point ret;

	ret.x = 200 + (x * 20);
	ret.y = 200 + (y * 20);
	return (ret);
}

void	disp_connect_points(t_fmlx *mlx, t_fmap *ptr)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < ptr->size_y)
	{
		while (j < ptr->size_x)
		{
			if (i + 1 < ptr->size_y)
				fdf_draw_line(mlx, fdf_coords(j, i), fdf_coords(j, i + 1), 0xFFFFFF);
			if (i + 1 < ptr->size_y && ptr->map[i][j] > 0 && ptr->map[i + 1][j] > 0)
				fdf_draw_line(mlx, fdf_coords(j, i), fdf_coords(j, i + 1), 0x4073ed);
			if (j + 1 < ptr->size_x)
				fdf_draw_line(mlx, fdf_coords(j, i), fdf_coords(j + 1, i), 0xFFFFFF);
			if (j + 1 < ptr->size_x && ptr->map[i][j] > 0 && ptr->map[i][j + 1] > 0)
				fdf_draw_line(mlx, fdf_coords(j, i), fdf_coords(j + 1, i), 0x4073ed);
			j++;
		}
		j = 0;
		i++;
	}
}

t_point		test_matrice(t_point point, int angle)
{
	(void)angle;
	point.x = (point.x * cos(angle)) + ((-1 * sin(angle)) * point.y);
	point.y = (point.x * sin(angle)) + (cos(angle) * point.y);
	printf("x = %i   y = %i\n", point.x, point.y);
	return (point);
}

int		deal_key(int key, void *param)
{
	(void)param;
	if (key == 53)
		exit(0);
	return (key);
}

void	fdf(t_fmap *map)
{
	t_fmlx	ptr;

	(void)map;
	if(!(ptr.mlx = mlx_init()))
		return ;
	if (!(ptr.win = mlx_new_window(ptr.mlx, SWIN_X, SWIN_X, "test mlx")))
		return ;
	mlx_key_hook(ptr.win, deal_key, (void *)0);
	fdf_draw_line(&ptr, fdf_point(42, 42), fdf_point(150, 42), 0x0000FF);
	fdf_draw_line(&ptr, test_matrice(fdf_point(42, 100), -30), test_matrice(fdf_point(150, 100), -30), 0xFFFFFF);
	disp_connect_points(&ptr, map);
	mlx_loop(ptr.mlx);

}

int		main(int argc, char **argv)
{
	t_fmap	map;

	(void)argc;
	map.size_x = -1;
	fdf_parse(argv[1], &map);
	fdf(&map);
	return (0);
}
