/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 00:26:11 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/07/02 01:57:16 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fdf_exit(t_fmlx *mlx)
{
	delmap(&(mlx->fmap->map), mlx->fmap->size_y);
	ft_strdel(&(mlx->fmap->name));
	mlx_destroy_image(mlx->mlx, mlx->img);
	mlx_destroy_window(mlx->mlx, mlx->win);
	exit(0);
}

void	key_parttwo(int key, t_fmlx *mlx)
{
	if (key == 78 && mlx->fmap->scale >= 2)
		mlx->fmap->scale -= 2;
	else if (key == 116)
		mlx->fmap->rz += (10 * 3.14 / 180);
	else if (key == 121)
		mlx->fmap->rz -= (10 * 3.14 / 180);
	else if (key == 75)
		mlx->fmap->zmod -= 0.1;
	else if (key == 67)
		mlx->fmap->zmod += 0.1;
	else if (key == 49)
		fdf_reset(mlx->fmap);
	else if (key == 48)
		mlx->fmap->proj ^= FDF_ISO;
}

int		deal_key(int key, t_fmlx *mlx)
{
	if (key == 124)
		mlx->fmap->x_shift += 42;
	else if (key == 123)
		mlx->fmap->x_shift -= 42;
	else if (key == 126)
		mlx->fmap->y_shift -= 42;
	else if (key == 125)
		mlx->fmap->y_shift += 42;
	else if (key == 91)
		mlx->fmap->rx -= (10 * 3.14 / 180);
	else if (key == 84)
		mlx->fmap->rx += (10 * 3.14 / 180);
	else if (key == 88)
		mlx->fmap->ry += (10 * 3.14 / 180);
	else if (key == 86)
		mlx->fmap->ry -= (10 * 3.14 / 180);
	else if (key == 69)
		mlx->fmap->scale += 2;
	else
		key_parttwo(key, mlx);
	fdf_disp(mlx, mlx->fmap);
	if (key == 53)
		fdf_exit(mlx);
	return (key);
}

void	fdf(t_fmap *map)
{
	t_fmlx	ptr;
	int		bpp;
	int		size_line;
	int		endian;

	ptr.fmap = map;
	if (!(ptr.mlx = mlx_init()))
		fdf_exit(&ptr);
	if (!(ptr.win = mlx_new_window(ptr.mlx, SWIN_X, SWIN_Y, map->name)))
		fdf_exit(&ptr);
	if (!(ptr.img = mlx_new_image(ptr.mlx, SIMG_X, SIMG_Y)))
		fdf_exit(&ptr);
	if (!(ptr.screen = mlx_get_data_addr(ptr.img, &bpp, &size_line, &endian)))
		fdf_exit(&ptr);
	mlx_hook(ptr.win, 2, 0, deal_key, &ptr);
	fdf_disp(&ptr, map);
	mlx_loop(ptr.mlx);
}

int		main(int argc, char **argv)
{
	t_fmap	map;

	map.size_x = -1;
	if (argc != 2)
	{
		ft_putstr_fd("usage : fdf file\n", 2);
		return (1);
	}
	if (fdf_parse(argv[1], &map) != 0)
		return (2);
	fdf(&map);
	return (0);
}
