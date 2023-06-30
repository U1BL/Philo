/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mofaisal <mofaisal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 17:13:40 by mofaisal          #+#    #+#             */
/*   Updated: 2023/06/30 17:01:14 by mofaisal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	mysleep(size_t ms_time)
{
	size_t	start;

	start = get_current_time();
	while (ms_time > get_current_time() - start)
		usleep(100);
}

void *routine(void *args)
{
    t_philo *philo = (t_philo *)args;
    if (philo->id % 2 == 0)
    {
        printf("\e[1;97mtime:%zu || Philo \e[1;95mid:%d \e[0m\e[1;97mis \e[1;95m[Has Taking A Fork]\n\e[0m", get_current_time() - philo->time,  philo->id);    
        pthread_mutex_lock(&philo->right_fork->fork);
        pthread_mutex_lock(&philo->left_fork->fork);
    }
    else
    {
        printf("\e[1;97mtime:%zu || Philo \e[1;95mid:%d \e[0m\e[1;97mis \e[1;95m[Has Taking A Fork]\n\e[0m", get_current_time() - philo->time,  philo->id);    
        pthread_mutex_lock(&philo->left_fork->fork);
        pthread_mutex_lock(&philo->right_fork->fork);
    }
    if(philo->is_dead)
    {
        pthread_mutex_unlock(&philo->left_fork->fork);
        pthread_mutex_unlock(&philo->right_fork->fork);
        return (NULL);
    }
    printf("\e[1;97mtime:%zu || Philo \e[1;92mid:%d \e[0m\e[1;97mis \e[1;92m[eating]\n\e[0m", get_current_time() - philo->time,  philo->id);
    mysleep(philo->time_to_eat * 1000);
    printf("\e[1;97mtime:%zu || Philo \e[1;93mid:%d \e[0m\e[1;97mis \e[1;93m[sleeping]\n\e[0m", get_current_time() - philo->time,  philo->id);
    mysleep(philo->time_to_sleep * 1000);
    printf("\e[1;97mtime:%zu || Philo \e[1;94mid:%d \e[0m\e[1;97mis \e[1;94m[thinking]\n\e[0m", get_current_time() - philo->time,  philo->id);
    pthread_mutex_unlock(&philo->left_fork->fork);
    pthread_mutex_unlock(&philo->right_fork->fork);
    
        
    return (NULL);
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
    return (forks);
}

t_philo *init_philo(int ac, char *av[] , t_fork *forks[])
{
    t_philo *philo;
    int i = 0;
    philo = malloc(sizeof(t_philo) * ft_atoi(av[1]));
    philo->num_times_to_eat = -1;
    while (i < ft_atoi(av[1]))
    {
        philo[i].id = i + 1;
        philo->is_dead = false;
        philo[i].time_to_eat = ft_atoi(av[3]);
        philo[i].time_to_sleep = ft_atoi(av[4]);
        philo[i].time_to_die = ft_atoi(av[2]);
        philo[i].time = get_current_time();
        philo[i].num_times_eaten = 0;
        philo[i].left_fork = forks[i];
        philo[i].right_fork = forks[(i + 1) % ft_atoi(av[1])];
        if (ac == 6)
            philo[i].num_times_to_eat = ft_atoi(av[5]);
        i++;
    }
    return (philo);
}


void create_threads(t_philo *philo, char *av[])
{
    int i = 0;
    philo->threads = malloc(sizeof(pthread_t) * ft_atoi(av[1]));
    while (i < ft_atoi(av[1]))
    {
        pthread_create(&philo->threads[i], NULL, routine, &philo[i]);
        i++;
    }
    while(1)
    {
        if ((int)(get_current_time() - philo->time) > philo->time_to_die)
        {   
            philo->is_dead = true;
            printf("\e[1;97mtime:%zu || Philo \e[1;91mid:%d \e[0m\e[1;97mis \e[1;91m[dead]\n\e[0m", get_current_time() - philo->time, philo->id);
            return ;
        }
    }
    i = 0;
    while (i < ft_atoi(av[1]))
    {
        pthread_join(philo->threads[i], NULL);
        i++;
    }
}

int threads(int ac, char *av[])
{
    t_fork **forks;
    t_philo *philo = malloc(sizeof(t_philo));
    forks = init_fork(av);
    philo = init_philo(ac, av, forks);
    int i = 0;
    while (i < ft_atoi(av[1]))
    {
       
        i++;
    }
    create_threads(philo, av);
    return (0);
}
