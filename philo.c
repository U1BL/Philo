/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mofaisal <mofaisal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 20:28:45 by mfaisal           #+#    #+#             */
/*   Updated: 2023/06/25 21:07:17 by mofaisal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *routine(void *args)
{
    t_philo *philo = (t_philo *)args;
    while ((int)(get_current_time() - philo->time) < philo->time_to_die)
    {
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
        printf("\e[1;97mtime:%zu || Philo \e[1;92mid:%d \e[0m\e[1;97mis \e[1;92m[eating]\n\e[0m", get_current_time() - philo->time,  philo->id);
        usleep(200000);
        printf("\e[1;97mtime:%zu || Philo \e[1;93mid:%d \e[0m\e[1;97mis \e[1;93m[sleeping]\n\e[0m", get_current_time() - philo->time,  philo->id);
        usleep(200000);
        printf("\e[1;97mtime:%zu || Philo \e[1;94mid:%d \e[0m\e[1;97mis \e[1;94m[thinking]\n\e[0m", get_current_time() - philo->time,  philo->id);
        pthread_mutex_unlock(&philo->left_fork->fork);
        pthread_mutex_unlock(&philo->right_fork->fork);
    }

    printf("\e[1;97mtime:%zu || Philo \e[1;91mid:%d \e[0m\e[1;97mis \e[1;91m[dead]\n\e[0m", get_current_time() - philo->time, philo->id);
    // exit(0);
    
    return (NULL);
}

int threads(char *av[])
{
    int i = 0;
    t_philo *philo = malloc(sizeof(t_philo) * ft_atoi(av[1])); //allocate memory for philo
    philo->ph = ft_atoi(av[1]); // number of philo
    t_fork *forks = malloc(sizeof(t_fork) * philo->ph); // allocate memory for forks

    while(i < philo->ph) // initialize forks
    {
        pthread_mutex_init(&forks[i].fork, NULL);
        i++;
    }
    i = 0;
    while(i < philo->ph) // initialize philo
    {
        philo[i].id = i + 1;
        philo[i].time_to_eat = ft_atoi(av[3]);
        philo[i].time_to_sleep = ft_atoi(av[4]);
        philo[i].time_to_die = ft_atoi(av[2]);
        philo[i].time = get_current_time();
        philo[i].left_fork = &forks[i];
        philo[i].right_fork = &forks[(i + 1) % philo->ph];
        i++;
    }
    i = 0;
    pthread_t *th = malloc(sizeof(pthread_t) * philo->ph);
    while (i < philo->ph) // create threads
    {
        pthread_create(&th[i], NULL, routine, &philo[i]);
        i++;
    }
    i = 0;
    while (i < philo->ph) // join threads
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
       }
   }
   else
    printf("Error: Invalid number of arguments\n");
}