/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 02:45:38 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/06/23 04:57:55 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int **delmap(int ***map, int y)
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

int		fill_map(char *path, t_fmap *map, char **tab)
{
	char	*line;
	int		x;
	int		y;
	int		fd;

	y = -1;
	x = -1;
	line = NULL;
	if((fd = open(path, O_RDONLY)) < 0)
		return (-1);
	while (++y >= 0 && get_next_line(fd, &line) > 0)
	{
		if (!(tab = ft_strsplit(line, ' ')))
		{
			ft_strdel(&line);
			close(fd);
			return (-1);
		}
		ft_strdel(&line);
		while (tab[++x])
			map->map[y][x] = ft_atoi(tab[x]);
		x = -1;
	}
	close(fd);
	return (0);
}


// DEBUG
/*
void	print_int_tab(int **map, int x, int y)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < y)
	{
		while (j < x)
		{
			ft_putnbr(map[i][j]);
			ft_putchar(' ');
			j++;
		}
		j = 0;
		i++;
		ft_putchar('\n');
	}
}*/

int		fdf_parse(char *path, t_fmap *map)
{
	if (fdf_verify(path, map) != 0)
	{
		ft_putstr_fd("fdf: invalid file.\n", 2);
		return (-1);
	}
	if (!(map->map = gen_map(map->size_x, map->size_y)) || fill_map(path, map, NULL) != 0)
	{
		ft_putstr_fd("fdf: error\n", 2);
		delmap(&(map->map), map->size_y);
		return (-1);
	}
	return (0);
}
