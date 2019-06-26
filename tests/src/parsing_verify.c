/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 05:19:13 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/06/26 08:32:22 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		parse_hmn_elem(char *line)
{
	char	**ptr;
	int		ret;
	int		i;

	i = 0;
	ret = 0;
	ptr = NULL;
	if (line != NULL && line[0])
	{
		if (line[0] == 10 || !(ptr = ft_strsplit(line, ' ')))
			return (-1);
		while (ptr[i])
		{
			if (!((ptr[i][0] == '+' || ptr[i][0] == '-')
				&& (ptr[i][1] >= '0' && ptr[i][1] <= '9'))
					&& !(ptr[i][0] >= '0' && ptr[i][0] <= '9'))
				ret = -1;
			ft_strdel(&(ptr[i]));
			i++;
		}
		free(ptr);
		if (ret != -1)
			return (i);
	}
	return (-1);
}

int		fdf_verify(char *path, t_fmap *map, int ret)
{
	char	*line;
	int		fd;
	int		x;
	int		y;

	x = 0;
	y = 0;
	line = NULL;
	if ((fd = open(path, O_RDONLY)) <= 0)
		return (-1);
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		x = parse_hmn_elem(line);
		ft_strdel(&line);
		if ((x < 1 || (map->size_x != -1 && x != map->size_x)))
		{
			close(fd);
			return (-1);
		}
		map->size_x = x;
		y++;
	}
	ft_strdel(&line);
	map->size_y = y;
	close(fd);
	return (ret);
}
