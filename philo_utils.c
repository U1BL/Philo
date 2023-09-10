/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mofaisal <mofaisal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 20:49:54 by mfaisal           #+#    #+#             */
/*   Updated: 2023/09/10 18:42:11 by mofaisal         ###   ########.fr       */
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

void	mysleep(size_t ms_time)
{
	size_t	start;

	start = get_current_time();
	while (ms_time > get_current_time() - start)
		usleep(100);
}

t_fork **init_fork(char *av[])
{
    t_fork **forks;
    int i = 0;
    forks = malloc(sizeof(t_fork) * ft_atoi(av[1]));
    while (i < ft_atoi(av[1]))
    {
        forks[i] = malloc(sizeof(t_fork));
        pthread_mutex_init(&forks[i]->fork, NULL);
        i++;
    }
    forks[i] = NULL;
    return (forks);
}

t_philo *init_philo(int ac, char *av[] , t_fork *forks[])
{
    t_philo *philo;
    int i = 0;
    philo = malloc(sizeof(t_philo) * ft_atoi(av[1]));
    philo->num_times_to_eat = -1;
    philo->lock_print = malloc(sizeof(pthread_mutex_t));
    philo->lock_eat = malloc(sizeof(pthread_mutex_t));
    philo->lock_eat1 = malloc(sizeof(pthread_mutex_t));
    philo->lock_lasteat = malloc(sizeof(pthread_mutex_t));
    philo->lock_dead = malloc(sizeof(pthread_mutex_t));
    pthread_mutex_init(philo->lock_print, NULL);
    pthread_mutex_init(philo->lock_eat, NULL);
    pthread_mutex_init(philo->lock_eat1, NULL);
    pthread_mutex_init(philo->lock_lasteat, NULL);
    pthread_mutex_init(philo->lock_dead, NULL);
    while (i < ft_atoi(av[1]))
    {
        philo[i].id = i + 1;
        philo[i].is_dead = 0;
        philo->num_ph = ft_atoi(av[1]);
        philo[i].time_to_eat = ft_atoi(av[3]);
        philo[i].time_to_sleep = ft_atoi(av[4]);
        philo[i].time_to_die = ft_atoi(av[2]);
        philo[i].time = get_current_time();
        philo[i].num_times_eaten = 0;
        philo[i].left_fork = forks[i];
        philo[i].last_time_eat = 0;
        philo[i].right_fork = forks[(i + 1) % ft_atoi(av[1])];
        philo[i].lock_print = philo->lock_print;
        philo[i].lock_eat = philo->lock_eat;
        philo[i].lock_lasteat = philo->lock_lasteat;
        philo[i].lock_dead = philo->lock_dead;
        if (ac == 6)
            philo[i].num_times_to_eat = ft_atoi(av[5]);
        else
            philo[i].num_times_to_eat = INT_MAX;
        i++;
    }
    return (philo);
}


void create_threads(t_philo *philo, char *av[])
{
    int i = 0;
    philo->threads = malloc(sizeof(pthread_t) * ft_atoi(av[1]));
    if (philo->threads == NULL)
            free(philo->threads);
    while (i < ft_atoi(av[1]))
    {
        pthread_create(&philo->threads[i], NULL, routine, &philo[i]);
        i++;
    }
    // pthread_mutex_unlock(&philo->lock_dead);
    // free_string_array(philo->threads);
    // while(1)
    // {
    //     if ((int)(get_current_time() - philo->time) > philo->time_to_die)
    //     {   
    //         philo->is_dead = true;
    //         printf("\e[1;97mtime:%zu || Philo \e[1;91mid:%d \e[0m\e[1;97mis \e[1;91m[dead]\n\e[0m", get_current_time() - philo->time, philo->id);
    //         i = 0;
    //         while (i < ft_atoi(av[1]))
    //         {
    //             pthread_join(philo->threads[i], NULL);
    //             i++;
    //         }
    //         return ;
    //     }
    // }
}