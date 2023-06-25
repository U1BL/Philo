/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mofaisal <mofaisal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 20:28:45 by mfaisal           #+#    #+#             */
/*   Updated: 2023/06/25 18:51:16 by mofaisal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	get_current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec * 0.001));
}

void *routine(void *args)
{
    t_philo *philo = (t_philo *)args;
    if (philo->id == 3)
        sleep(1);
    if(philo->id % 2 == 0)
    {
        pthread_mutex_lock(&philo->right_fork->fork);
        pthread_mutex_lock(&philo->left_fork->fork);
    }
    else
    {
        pthread_mutex_lock(&philo->left_fork->fork);
        pthread_mutex_lock(&philo->right_fork->fork);
    }
    printf("%zu Philo id: %d is eating\n", get_current_time() - philo->time,  philo->id);
    pthread_mutex_unlock(&philo->left_fork->fork);
    pthread_mutex_unlock(&philo->right_fork->fork);

    if ((int)(get_current_time() - philo->time) > philo->time_to_die)
    {
        printf("%zu Philo id: %d is dead\n", get_current_time() - philo->time,  philo->id);
        return (NULL);
    }
    
    return (NULL);
}

int threads(char *av[])
{
    int i = 0;
    t_philo *philo = malloc(sizeof(t_philo) * ft_atoi(av[1]));
    philo->ph = ft_atoi(av[1]);
    t_fork *forks = malloc(sizeof(t_fork) * philo->ph);

    while(i < philo->ph)
    {
        pthread_mutex_init(&forks[i].fork, NULL);
        i++;
    }
    i = 0;
    while(i < philo->ph)
    {
        philo[i].time = get_current_time();
        philo[i].left_fork = &forks[i];
        philo[i].right_fork = &forks[(i + 1) % philo->ph];
        philo[i].id = i + 1;
        philo[i].time_to_eat = ft_atoi(av[3]);
        philo[i].time_to_die = ft_atoi(av[2]);
        philo[i].time_to_sleep = ft_atoi(av[4]);
        i++;
    }
    i = 0;
    pthread_t *th = malloc(sizeof(pthread_t) * philo->ph);
    while (i < philo->ph)
    {
        pthread_create(&th[i], NULL, routine, &philo[i]);
        i++;
    }
    i = 0;
    while (i < philo->ph)
    {
        pthread_join(th[i], NULL);
        i++;
    }
    return (0);
}

int main(int ac, char *av[])
{
    if (!(ac < 5) && !(ac > 6))
    {
       if (!ft_digit(av))
           printf("Error: Invalid arguments\n");
       else if (ft_atoi(av[1]) < 1 || ft_atoi(av[1]) > 200)
           printf("Error: Invalid number of philosophers\n");
       else if (ft_atoi(av[2]) < 60 || ft_atoi(av[3]) < 60 || ft_atoi(av[4]) < 60)
           printf("Error: Invalid time\n");
       else if (ac == 6 && ft_atoi(av[5]) < 0)
           printf("Error: Invalid number of times to eat\n");
       else
       {
            threads(av);
            if (ac == 6)
               printf("Number of times each philosopher must eat: %d\n", ft_atoi(av[5]));
       }
   }
   else
    printf("Error: Invalid number of arguments\n");
}