/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 02:45:38 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/06/22 07:52:58 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		parse_fillandcheck(const int fd, char ***tab)
{
	char	*line;
	int		ret;
	int		len;
	int		i;

	line = NULL;
	i = 0;
	len = -1;
	ret = 0;
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		if ((tab[i] = ft_strsplit(line, ' ')) == NULL)
			return (-1);
		if (parse_checkline(tab[i], len) != 0)
			return (1);
		i++;
	}
	return (ret);
}

int		parse_getmap(t_fmap *map, char ***tab)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (!(map->map = (int**)malloc(sizeof(int*) * map->size_y)))
		return (-1);
	while (tab[i])
	{
		if (!(map->map[i] = (int*)malloc(sizeof(int) * map->size_x)))
		{
//			free_map(ptr, i); A CODER
			return (-1);
		}
		while (tab[i][++j])
			map->map[i][j] = atoi(tab[i][j]);
		j = -1;
		i++;
	}
	return (0);
}

int		fdf_parse(char *path, t_fmap *map)
{
	char	***tab;
	int		fd;
	int		ret;
	int		size;

	size = 0;
	ret = 0;
	if (!map || (fd = open(path, O_RDONLY)) == -1)
		return (-1);
	size = how_many_lines(fd);
	close(fd);
	if (size < 1 || !(tab = (char***)malloc(sizeof(char**) * (size + 1))))
		return (-1);
	map->size_y = size;
	if ((ret = parse_fillandcheck(fd, tab)) != 0
			|| (ret = parse_getmap(map, tab)) != 0)
	{
		fdf_deltab(&tab);
		return (ret);
	}
	return (0);
}
