/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 00:26:11 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/06/26 08:04:02 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fdf_exit(t_fmap *mlx)
{
	delmap(&(mlx->map), mlx->size_y);
	ft_strdel(&(mlx->name));
	exit(0);
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
	fdf_exit(&map);
	return (0);
}
