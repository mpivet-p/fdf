/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 04:37:29 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/06/22 07:55:57 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	fdf_deltab(char ****tab)
{
	int i;
	int j;

	i = 0;
	j = -1;
	if (tab && *tab)
	{
		while (*(tab[i]))
		{
			j = -1;
			while (*tab[i][++j])
				ft_strdel(tab[i][j]);
			free(*(tab[i]));
			*(tab[i]) = NULL;
			i++;
		}
		free(*tab);
		*tab = NULL;
	}
}
