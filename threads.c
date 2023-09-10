/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mofaisal <mofaisal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 17:13:40 by mofaisal          #+#    #+#             */
/*   Updated: 2023/09/10 19:07:24 by mofaisal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *routine(void *args)
{
    t_philo *philo = (t_philo *)args;
   
    while (philo->num_times_to_eat != 0)
    {
        if (philo->id % 2 == 0)
        {
            pthread_mutex_lock(philo->lock_print);
            printf(FORK, get_current_time() - philo->time,  philo->id);    
            pthread_mutex_unlock(philo->lock_print);
            pthread_mutex_lock(&philo->right_fork->fork);
            pthread_mutex_lock(&philo->left_fork->fork);
        }
        else
        {
            pthread_mutex_lock(philo->lock_print);
            printf(FORK, get_current_time() - philo->time,  philo->id);    
            pthread_mutex_unlock(philo->lock_print);
            pthread_mutex_lock(&philo->left_fork->fork);
            pthread_mutex_lock(&philo->right_fork->fork);
        }
        //lock death
        if(philo->is_dead)
        {
            pthread_mutex_unlock(&philo->left_fork->fork);
            pthread_mutex_unlock(&philo->right_fork->fork);
            // unlock death
            return (NULL);
        }
        // unlock death
        pthread_mutex_lock(philo->lock_print);
        printf(EAT, get_current_time() - philo->time,  philo->id);
        pthread_mutex_unlock(philo->lock_print);
        pthread_mutex_lock(philo->lock_eat);
        philo->num_times_to_eat--;
        pthread_mutex_unlock(philo->lock_eat);
        mysleep(philo->time_to_eat);
        pthread_mutex_lock(philo->lock_eat);
        philo->last_time_eat = get_current_time();
        pthread_mutex_unlock(philo->lock_eat);
        if(philo->is_dead)
        {
            pthread_mutex_unlock(&philo->left_fork->fork);
            pthread_mutex_unlock(&philo->right_fork->fork);
            return (NULL);
        }
        if (philo->id % 2 == 0)
        {    
            pthread_mutex_unlock(&philo->right_fork->fork);
            pthread_mutex_unlock(&philo->left_fork->fork);
        }
        else
        {    
            pthread_mutex_unlock(&philo->left_fork->fork);
            pthread_mutex_unlock(&philo->right_fork->fork);
        }
        pthread_mutex_lock(philo->lock_print);
        printf(SLEEP, get_current_time() - philo->time,  philo->id);
        pthread_mutex_unlock(philo->lock_print);
        mysleep(philo->time_to_sleep);
        if(philo->is_dead)
        {
            pthread_mutex_unlock(&philo->left_fork->fork);
            pthread_mutex_unlock(&philo->right_fork->fork);
            return (NULL);
        }
        pthread_mutex_lock(philo->lock_print);
        printf(THINK, get_current_time() - philo->time,  philo->id);
        pthread_mutex_unlock(philo->lock_print);
    }
        
    return (NULL);
}

static int checker(t_philo *philo)
{
    int i = -1;
    // pthread_mutex_lock(philo->lock_dead);
        while (++i < philo->num_ph)
        {
            pthread_mutex_lock(philo->lock_eat);
            long long time = get_current_time() - philo->time - philo->last_time_eat;
            pthread_mutex_unlock(philo->lock_eat);
            if ((time >= philo[i].time_to_die))
            {   
                int j = 0;
                while (j < philo->num_ph)
                {
                    pthread_mutex_lock(philo->lock_eat);
                    philo[j].is_dead = 1;
                    pthread_mutex_unlock(philo->lock_eat);
                    j++;
                }
                pthread_mutex_lock(philo->lock_print);
                printf(DEAD, get_current_time() - philo[i].time, philo[i].id);
                pthread_mutex_unlock(philo->lock_print);
                return 0;
            }
        }
    // pthread_mutex_unlock(philo->lock_dead);
        return 1;
}

void	free_string_array(t_fork **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
        pthread_mutex_destroy(&array[i]->fork);
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
	array = NULL;
}

int threads(int ac, char *av[])
{
    int     i;
    t_fork **forks;
    t_philo *philo;
    
    i = 0;
    forks = init_fork(av);
    philo = init_philo(ac, av, forks);
    create_threads(philo, av);
    while(1)
    {
        if(!checker(philo) || \
            philo->num_times_to_eat == 0)
        {
            i = 0;
            while (i < ft_atoi(av[1]))
            {
                pthread_join(philo->threads[i], NULL);
                i++;
            }
            return (free(philo->threads), free(philo), free_string_array(forks), 0);
        }
    }
    return (0);
}
