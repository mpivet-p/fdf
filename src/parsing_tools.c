/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 05:19:13 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/06/22 07:34:02 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		is_allowed(char c)
{
	if (!(c >= '0' && c <= '9')
			&& !(c >= 'A' && c <= 'F')
			&& !(c >= 'a' && c<= 'f')
			&& !(c == 'x' || c == ','))
		return (-1);
	return (0);
}

void	parse_error(int error, int line)
{
	if (error == 'c')
	{
		ft_putstr_fd("fdf: forbidden character at line ", 2);
		ft_putnbr_fd(line, 2);
	}
	else if (error == 'l')
	{
		ft_putstr_fd("fdf: invalid length  at line ", 2);
		ft_putnbr_fd(line, 2);
	}
	ft_putchar_fd('\n', 2);
}

int		parse_checkline(char **tab, int prev_len)
{
	int i;
	int j;

	i = 0;
	j = -1;
	while (tab[i])
	{
		while (tab[i][++j])
			if (is_allowed(tab[i][j]) != 0)
			{
				parse_error('c', i);
				return (1);
			}
		j = -1;
		i++;
	}
	if (i != prev_len)
	{
		parse_error('l', i);
		return (1);
	}
	return (0);
}
