/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 02:45:38 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/06/27 08:51:56 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		**delmap(int ***map, int y)
{
	int		**ptr;
	int		i;

	ptr = NULL;
	i = 0;
	if (map && *map)
	{
		ptr = *map;
		*map = NULL;
		while (i < y)
		{
			free(ptr[i]);
			ptr[i] = NULL;
			i++;
		}
		free(ptr);
	}
	return (NULL);
}

int		**gen_map(int x, int y)
{
	int **map;
	int i;

	i = 0;
	map = NULL;
	if (!(map = (int**)malloc(sizeof(int*) * (y))))
		return (NULL);
	while (i < y)
	{
		if (!(map[i] = (int*)malloc(sizeof(int) * (x))))
			return (delmap(&map, i));
		i++;
	}
	return (map);
}

int		fill_map(char *path, t_fmap *map, char **tab, char *line)
{
	int		x;
	int		y;
	int		fd;

	y = -1;
	x = -1;
	if ((fd = open(path, O_RDONLY)) < 0)
		return (-1);
	while (++y >= 0 && get_next_line(fd, &line) > 0)
	{
		tab = ft_strsplit(line, ' ');
		ft_strdel(&line);
		if (!(tab))
		{
			close(fd);
			return (-1);
		}
		while (tab[++x])
		{
			map->map[y][x] = ft_atoi(tab[x]);
			ft_strdel(&(tab[x]));
		}
		if (tab)
			free(tab);
		x = -1;
	}
	close(fd);
	return (0);
}

int		fdf_parse(char *path, t_fmap *map)
{
	char *name;

	name = NULL;
	if (!path || !(path[0]))
		return (-1);
	if (fdf_verify(path, map, NULL, 0) != 0)
	{
		ft_putstr_fd("fdf: invalid file.\n", 2);
		return (-1);
	}
	if (!(map->map = gen_map(map->size_x, map->size_y))
			|| fill_map(path, map, NULL, NULL) != 0)
	{
		ft_putstr_fd("fdf: error\n", 2);
		delmap(&(map->map), map->size_y);
		return (-1);
	}
	if (ft_strchr(path, '/'))
		map->name = ft_strdup(ft_strchr(path, '/') + 1);
	else
		map->name = ft_strdup(name);
	fdf_reset(map);
	return (0);
}
