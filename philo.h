/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mofaisal <mofaisal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 20:31:27 by mfaisal           #+#    #+#             */
/*   Updated: 2023/06/30 16:53:10 by mofaisal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PHILO_H
#define PHILO_H

#include "./printf/ft_printf.h"
#include "./libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include <string.h>
#include <stdbool.h>

typedef struct s_fork
{
	pthread_mutex_t fork;
} t_fork;


typedef struct s_philo
{
	pthread_t *threads;
	int id;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	bool is_dead;
	size_t time;
	t_fork *left_fork;
	t_fork *right_fork;
	int num_times_eaten; // Number of times the philosopher has eaten
	int num_times_to_eat;
    pthread_mutex_t eat_count_mutex; // Mutex for accessing num_times_eaten
} t_philo;



typedef struct s_table
{
	t_philo *philo;
} t_table;


int	ft_digit(char *av[]);
int error_checking(int ac, char *av);
size_t	get_current_time(void);
void *routine(void *args);
t_philo *init_philo(int ac, char *av[], t_fork *forks[]);
t_fork **init_fork(char *av[]);
int threads(int ac, char *av[]);
void create_threads(t_philo *philo, char *av[]);


# endif
