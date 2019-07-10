/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 01:30:54 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/07/10 04:04:39 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fdf_reset(t_fmap *map)
{
	map->scale = (SIMG_X / 2) / map->size_x;
	map->x_shift = (SIMG_X - (map->size_x * map->scale)) / 2;
	map->y_shift = (SIMG_Y - (map->size_y * map->scale)) / 2;
	map->rx = 0;
	map->ry = 0;
	map->rz = 0;
	map->proj = 0;
	map->zmod = 1;
}

t_point	fdf_coords(int x, int y, int z, t_fmap *map)
{
	t_point point;

	x = x * map->scale;
	y = y * map->scale;
	z = z * map->scale * map->zmod;
	if (map->proj & FDF_ISO)
	{
		point.x = ((x - y) * cos(0.523599));
		point.y = (-z + (x + y) * sin(0.523599));
	}
	else
	{
		point.y = (y * cos(map->rx)) + (z * sin(map->rx));
		point.z = (z * cos(map->rx)) - (y * sin(map->rx));
		point.x = (x * cos(map->ry)) + (point.z * sin(map->ry));
		x = point.x;
		point.x = (point.x * cos(map->rz)) - (point.y * sin(map->rz));
		point.y = (x * sin(map->rz)) + (point.y * cos(map->rz));
	}
	point.x += map->x_shift;
	point.y += map->y_shift;
	return (point);
}
