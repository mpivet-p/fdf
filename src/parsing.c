/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 02:45:38 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/06/23 03:19:48 by mpivet-p         ###   ########.fr       */
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
		//if (parse_checkline(tab[i], len) != 0)
		//	return (1);
		i++;
	}
	return (ret);
}

int **delmap(int ***map)
{
	int		**ptr;
	int		i;

	ptr = NULL;
	i = 0;
	if (map && *map)
	{
		ptr = *map;
		*map = NULL;
		while (ptr[i])
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
	if (!(map = (int**)malloc(sizeof(int*) * y)))
		return (NULL);
	while (i != y)
	{
		if (!(map[i] = (int*)malloc(sizeof(int) * x)))
			return (delmap(&map));
		if (i + 1 < y)
			map[i + 1] = NULL;
		i++;
	}
	return (map);
}

int		fdf_parse(char *path, t_fmap *map)
{
	char ***temp;

	temp = NULL;
	if (fdf_verify(path, map) != 0)
	{
		ft_putstr_fd("fdf: invalid file.\n", 2);
		return (-1);
	}
	if (!(temp = (char***)malloc(sizeof(char**) * (map->size_y + 1))))
		return (-1);
	if (!(map->map = gen_map(map->size_x, map->size_y)))
	{
		free(temp);
		return (-1);
	}
	printf("OK\n");
	return (0);
}
