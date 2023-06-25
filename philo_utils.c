/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaisal <mfaisal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 20:49:54 by mfaisal           #+#    #+#             */
/*   Updated: 2023/06/09 20:59:10 by mfaisal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_digit(char *av[])
{
	int			i;
	int			j;
	long long	value;

	i = 1;
	j = 0;
	while (av[j])
	{
		if (av[j][0] == '\0')
			return (printf("\x1B[31mError\n"), 0);
		j++;
	}
	while (av[i])
	{
		value = ft_atoi(av[i]);
		j = 0;
		while (av[i][j])
		{
			if ((ft_isdigit(av[i], av[i][j], &j)
				&& (value <= 2147483647 && value >= -2147483648))
					|| (av[i][j] == ' '))
				j++;
			else
			{
				printf("\x1B[31mError\n");
				exit(1);
			}
		}
		i++;
	}
	return (1);
}
