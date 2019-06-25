/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools->c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42->fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 04:37:29 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/06/25 02:48:12 by mpivet-p         ###   ########.fr       */
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

t_point	fdf_coords(int x, int y, int z, t_fmap *map)
{
	t_point point;

	point.x = x * map->scale;
	point.y = y * map->scale;
	point.z = z * map->scale;

	point.y = (point.y * cos(map->rx)) - (point.z * sin(map->rx));
	point.z = (point.y * sin(map->rx)) + (point.z * cos(map->rx));

	point.x = (point.x * cos(map->ry)) + (point.z * sin(map->ry));
	point.z = (point.z * cos(map->ry)) - (point.x * sin(map->ry));

	point.x = (point.x * cos(map->rz)) - (point.y * sin(map->rz));
	point.y = (point.x * sin(map->rz)) + (point.y * cos(map->rz));

	point.x += map->x_shift;
	point.y += map->y_shift;
	return (point);
}
