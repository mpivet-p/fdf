/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 00:26:11 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/06/22 07:32:45 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fdf_draw_line(t_fmlx *ptr, t_point one, t_point two)
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
					(int)lround((slope * (double)one.x) + pitch), 0xFF0000);
			one.x += s.x;
		}
		return ;
	}
	slope = (double)delta.x / (double)delta.y;
	pitch = (double)one.x - (slope * (double)one.y);
	while (one.y != two.y)
	{
		mlx_pixel_put(ptr->mlx, ptr->win, (int)lround((slope * (double)one.y) + pitch),
				one.y, 0xFF0000);
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
	fdf_draw_line(&ptr, fdf_point(42, 42), fdf_point(430, 750));
	mlx_key_hook(ptr.win, deal_key, (void *)0);
	mlx_loop(ptr.mlx);

}

int		main(void)
{
	t_fmap	map;
	int i;

	i = 42;
	printf("%i\n", fdf_parse("maps/42.fdf", NULL));
	fdf_parse("maps/42.fdf", &map);
//	fdf(&map);
	return (0);
}
