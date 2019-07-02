/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 22:16:15 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/07/02 00:46:01 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fill_pxl(char *image, int x, int y, int color)
{
	int i;

	i = (((SIMG_X * y) + x) * 4);
	if (x > 0 && y > 0 && x < SIMG_X && y < SIMG_Y)
	{
		image[i + 2] = (color >> 16) & 0xFF;
		image[i + 1] = (color >> 8) & 0xFF;
		image[i + 0] = color & 0xFF;
	}
}

void	drawline_init(t_point *delta, t_point *s, t_point one, t_point two)
{
	delta->x = two.x - one.x;
	s->x = (delta->x < 0) ? -1 : 1;
	delta->y = two.y - one.y;
	s->y = (delta->y < 0) ? -1 : 1;
}

void	fdf_draw_line(t_fmlx *ptr, t_point one, t_point two, int color)
{
	t_point	delta;
	t_point	s;
	double	slope;
	double	pitch;

	drawline_init(&delta, &s, one, two);
	slope = (fabs(delta.y) < fabs(delta.x)) ? delta.y / delta.x
		: delta.x / delta.y;
	pitch = (fabs(delta.y) < fabs(delta.x)) ? one.y - (slope * one.x)
		: one.x - (slope * one.y);
	if (fabs(delta.y) < fabs(delta.x))
		while ((int)round(one.x) != (int)round(two.x))
		{
			fill_pxl(ptr->screen, (int)round(one.x),
					(int)lround((slope * one.x) + pitch), color);
			one.x += s.x;
		}
	else
		while ((int)round(one.y) != (int)round(two.y))
		{
			fill_pxl(ptr->screen, (int)lround((slope * one.y) + pitch),
					(int)round(one.y), color);
			one.y += s.y;
		}
}

void	disp_join_points(t_fmlx *mlx, t_fmap *ptr, int i, int j)
{
	int color;

	color = 0xFFFFFF;
	if (i + 1 < ptr->size_y)
	{
		if (ptr->map[i][j] > 0 && ptr->map[i + 1][j] > 0)
			color = 0x4073ed;
		fdf_draw_line(mlx, fdf_coords(j, i, ptr->map[i][j], ptr),
			fdf_coords(j, i + 1, ptr->map[i + 1][j], ptr), color);
	}
	color = 0xFFFFFF;
	if (j + 1 < ptr->size_x)
	{
		if (ptr->map[i][j] > 0 && ptr->map[i][j + 1] > 0)
			color = 0x4073ed;
		fdf_draw_line(mlx, fdf_coords(j, i, ptr->map[i][j], ptr),
			fdf_coords(j + 1, i, ptr->map[i][j + 1], ptr), color);
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
			disp_join_points(mlx, ptr, i, j);
			j++;
		}
		j = 0;
		i++;
	}
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
}
