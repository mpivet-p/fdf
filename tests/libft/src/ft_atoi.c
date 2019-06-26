/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 17:17:10 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/05/05 17:17:25 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_atoi(const char *str)
{
	int i;
	int result;
	int sign;

	i = 0;
	result = 0;
	sign = 1;
	while ((str[i] == '\t' || str[i] == '\n' || str[i] == '\r' || str[i] == '\v'
				|| str[i] == ' ' || str[i] == '\f') && str[i])
		i++;
	if ((str[i] == '+' || str[i] == '-') && str[i])
		i++;
	if (str[i - 1] == '-' && str[i])
		sign = -1;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		if (result >= 214748364 && str[i] > '8' && sign == -1)
			return (0);
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}
