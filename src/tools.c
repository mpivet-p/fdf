/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools->c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42->fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 04:37:29 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/06/24 09:58:09 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point	fdf_point(int x, int y, int z)
{
	t_point ret;

	ret.x = x;
	ret.y = y;
	ret.z = z;
	return (ret);
}

void	rotate_x(t_point *point, int theta)
{
	point->y = (point->y * cos(theta)) - (point->z * sin(theta));
	point->z = (point->y * sin(theta)) + (point->z * cos(theta));
}

void	rotate_y(t_point *point, int theta)
{
	point->x = (point->x * cos(theta)) + (point->z * sin(theta));
	point->z = (point->z * cos(theta)) - (point->x * sin(theta));
}

void	rotate_z(t_point *point, int theta)
{
	point->x = (point->x * cos(theta)) - (point->y * sin(theta));
	point->y = (point->x * sin(theta)) + (point->y * cos(theta));
}

t_point	fdf_coords(int x, int y, int z, t_fmap *map)
{
	t_point point;

	point.x = x * map->scale;
	point.y = y * map->scale;
	point.z = z * map->scale;

	rotate_x(&point, map->rx);
	rotate_y(&point, map->ry);
	rotate_z(&point, map->rz);

	point.x += map->x_shift;
	point.y += map->y_shift;
	return (point);
}
