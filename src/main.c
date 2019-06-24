/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 00:26:11 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/06/24 06:58:16 by mpivet-p         ###   ########.fr       */
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

t_point	fdf_coords(int x, int y, int z, t_fmap *map)
{
	t_point ret;
	double	tmp_x;
	double	tmp_y;
	double	tmp_z;

//INIT

	tmp_x = x * map->scale;
	tmp_y = y * map->scale;
	tmp_z = z * map->scale;

// ROTATION EN X

	tmp_y = (tmp_y * cos(map->rx)) - (tmp_z * sin(map->rx));
	tmp_z = (tmp_y * sin(map->rx)) + (tmp_z * cos(map->rx));

// ROTATION EN Y

	tmp_x = (tmp_x * cos(map->ry)) + (tmp_z * sin(map->ry));
	tmp_z = (tmp_z * cos(map->ry)) - (tmp_x * sin(map->ry));

// ROTATION EN Z

	tmp_x = (tmp_x * cos(map->rz)) - (tmp_y * sin(map->rz));
	tmp_y = (tmp_x * sin(map->rz)) + (tmp_y * cos(map->rz));

	ret.x = tmp_x + map->x_shift;
	ret.y = tmp_y + map->y_shift;
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
				fdf_draw_line(mlx, fdf_coords(j, i, ptr->map[i][j], ptr), fdf_coords(j, i + 1, ptr->map[i + 1][j], ptr), 0xFFFFFF);
			if (i + 1 < ptr->size_y && ptr->map[i][j] > 0 && ptr->map[i + 1][j] > 0)
				fdf_draw_line(mlx, fdf_coords(j, i, ptr->map[i][j], ptr), fdf_coords(j, i + 1, ptr->map[i + 1][j], ptr), 0x4073ed);
			if (j + 1 < ptr->size_x)
				fdf_draw_line(mlx, fdf_coords(j, i, ptr->map[i][j], ptr), fdf_coords(j + 1, i, ptr->map[i][j + 1], ptr), 0xFFFFFF);
			if (j + 1 < ptr->size_x && ptr->map[i][j] > 0 && ptr->map[i][j + 1] > 0)
				fdf_draw_line(mlx, fdf_coords(j, i, ptr->map[i][j], ptr), fdf_coords(j + 1, i, ptr->map[i][j + 1], ptr), 0x4073ed);
			j++;
		}
		j = 0;
		i++;
	}
}

void	reset_win(t_fmlx *mlx)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < SWIN_X)
	{
		while (j < SWIN_Y)
		{
			mlx_pixel_put(mlx->mlx, mlx->win, i, j, 0x0);
			j++;
		}
		j = 0;
		i++;
	}
}

int		deal_key(int key, t_fmlx *mlx)
{
	if (key == 124)
	{
		mlx->fmap->x_shift += 42;
		reset_win(mlx);
		disp_connect_points(mlx, mlx->fmap);
	}
	if (key == 123)
	{
		mlx->fmap->x_shift -= 42;
		reset_win(mlx);
		disp_connect_points(mlx, mlx->fmap);
	}
	if (key == 126)
	{
		mlx->fmap->y_shift -= 42;
		reset_win(mlx);
		disp_connect_points(mlx, mlx->fmap);
	}
	if (key == 125)
	{
		mlx->fmap->y_shift += 42;
		reset_win(mlx);
		disp_connect_points(mlx, mlx->fmap);
	}
	if (key == 91)
	{
		mlx->fmap->rx += (10 * 3.14 / 180);
		reset_win(mlx);
		disp_connect_points(mlx, mlx->fmap);
	}
	if (key == 84)
	{
		mlx->fmap->rx -= (10 * 3.14 / 180);
		reset_win(mlx);
		disp_connect_points(mlx, mlx->fmap);
	}
	if (key == 86)
	{
		mlx->fmap->ry += (10 * 3.14 / 180);
		reset_win(mlx);
		disp_connect_points(mlx, mlx->fmap);
	}
	if (key == 88)
	{
		mlx->fmap->ry += (10 * 3.14 / 180);
		reset_win(mlx);
		disp_connect_points(mlx, mlx->fmap);
	}
	if (key == 69)
	{
		mlx->fmap->scale += 2;
		reset_win(mlx);
		disp_connect_points(mlx, mlx->fmap);
	}
	if (key == 78)
	{
		mlx->fmap->scale -= 2;
		reset_win(mlx);
		disp_connect_points(mlx, mlx->fmap);
	}
	if (key == 49)
	{
		mlx->fmap->rx = 0;
		mlx->fmap->ry = 0;
		mlx->fmap->rz = 0;
		reset_win(mlx);
		disp_connect_points(mlx, mlx->fmap);
	}
	if (key == 53)
		exit(0);
	return (key);
}

void	fdf(t_fmap *map)
{
	t_fmlx	ptr;

	ptr.fmap = map;
	map->scale = 15;
	map->x_shift = 340;
	map->y_shift = 340;
	map->rx = 0;
	map->ry = 0;
	map->rz = 0;
	if(!(ptr.mlx = mlx_init()))
		return ;
	if (!(ptr.win = mlx_new_window(ptr.mlx, SWIN_X, SWIN_Y, "test mlx")))
		return ;
	mlx_hook(ptr.win, 2, 0, deal_key, &ptr);
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
