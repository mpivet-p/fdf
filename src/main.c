/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 00:26:11 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/06/24 10:46:05 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fill_pxl(char *image, int x, int y, int color)
{
	int i;

	i = (((SIMG_X * x) + y) * 4);
	image[i] = color;
//		printf("x = %i   y = %i   %x\n", x, y, color);
}

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
	if (fabs(delta.y) < fabs(delta.x))
	{
		slope = delta.y / delta.x;
		pitch = one.y - (slope * one.x);
		while (one.x != two.x)
		{
			fill_pxl(ptr->screen, (int)round(one.x), (int)lround((slope * one.x) + pitch), color);
			one.x += s.x;
		}
		return ;
	}
	slope = delta.x / delta.y;
	pitch = one.x - (slope * one.y);
	while (one.y != two.y)
	{
		fill_pxl(ptr->screen, (int)lround((slope * one.y) + pitch), (int)round(one.y), color);
		one.y += s.y;
	}
}

void	fdf_disp(t_fmlx *mlx, t_fmap *ptr)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	ft_bzero(mlx->screen, (SIMG_X * SIMG_Y * 4));
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
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
}

int		deal_key(int key, t_fmlx *mlx)
{
	if (key == 124)
		mlx->fmap->x_shift += 42;
	if (key == 123)
		mlx->fmap->x_shift -= 42;
	if (key == 126)
		mlx->fmap->y_shift -= 42;
	if (key == 125)
		mlx->fmap->y_shift += 42;
	if (key == 91)
		mlx->fmap->rx += (10 * 3.14 / 180);
	if (key == 84)
		mlx->fmap->rx -= (10 * 3.14 / 180);
	if (key == 88)
		mlx->fmap->ry += (10 * 3.14 / 180);
	if (key == 86)
		mlx->fmap->ry += (10 * 3.14 / 180);
	if (key == 69)
		mlx->fmap->scale += 2;
	if (key == 78)
		mlx->fmap->scale -= 2;
	if (key == 49)
	{
		mlx->fmap->rx = 0;
		mlx->fmap->ry = 0;
		mlx->fmap->rz = 0;
	}
	fdf_disp(mlx, mlx->fmap);
	if (key == 53)
		exit(0);
	return (key);
}

void	fdf(t_fmap *map)
{
	t_fmlx	ptr;
	int bpp;
	int size_line;
	int endian;

	ptr.fmap = map;
	if(!(ptr.mlx = mlx_init()))
		return ;
	if (!(ptr.win = mlx_new_window(ptr.mlx, SWIN_X, SWIN_Y, "test mlx")))
		return ;
	if (!(ptr.img = mlx_new_image(ptr.mlx, SIMG_X, SIMG_Y)))
		return ;
	if (!(ptr.screen = mlx_get_data_addr(ptr.img, &bpp, &size_line, &endian)))
		return ;
	mlx_hook(ptr.win, 2, 0, deal_key, &ptr);
	fdf_disp(&ptr, map);
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
