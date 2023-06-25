/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mofaisal <mofaisal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 20:49:54 by mfaisal           #+#    #+#             */
/*   Updated: 2023/06/25 20:14:34 by mofaisal         ###   ########.fr       */
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

size_t	get_current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec * 0.001));
}
