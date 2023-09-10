/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mofaisal <mofaisal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 20:31:27 by mfaisal           #+#    #+#             */
/*   Updated: 2023/09/10 18:40:22 by mofaisal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PHILO_H
#define PHILO_H

#include "./libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

#define FORK "\e[1;97mtime:%zu || Philo \e[1;95mid:%d \e[0m\e[1;97mis \e[1;95m[Has Taking A Fork]\n\e[0m"
#define EAT "\e[1;97mtime:%zu || Philo \e[1;92mid:%d \e[0m\e[1;97mis \e[1;92m[eating]\n\e[0m"
#define SLEEP "\e[1;97mtime:%zu || Philo \e[1;93mid:%d \e[0m\e[1;97mis \e[1;93m[sleeping]\n\e[0m"
#define THINK "\e[1;97mtime:%zu || Philo \e[1;94mid:%d \e[0m\e[1;97mis \e[1;94m[thinking]\n\e[0m"
#define DEAD "\e[1;97mtime:%zu || Philo \e[1;91mid:%d \e[0m\e[1;97mis \e[1;91m[dead]\n\e[0m"

typedef struct s_fork
{
	pthread_mutex_t fork;
} t_fork;


typedef struct s_philo
{
	pthread_t *threads;
	int id;
	int time_to_die;
	int num_ph;
	int time_to_eat;
	int time_to_sleep;
	int is_dead;
	size_t time;
	t_fork *left_fork;
	t_fork *right_fork;
	int num_times_eaten; // Number of times the philosopher has eaten
	int num_times_to_eat;
	long long last_time_eat;
	bool dead;
    pthread_mutex_t *eat_count_mutex; // Mutex for accessing num_times_eaten
	pthread_mutex_t *lock_print;
	pthread_mutex_t *lock_eat;
	pthread_mutex_t *lock_eat1;
	pthread_mutex_t *lock_lasteat;
	pthread_mutex_t *lock_dead;
}	t_philo;

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
int check_dead(t_philo *philo);
void create_threads(t_philo *philo, char *av[]);
void	mysleep(size_t ms_time);
size_t	get_current_time(void);
int check_dead(t_philo *philo);
void	free_string_array(t_fork **array);
// int batata(t_philo *philo);




# endif
