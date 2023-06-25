/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mofaisal <mofaisal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 20:31:27 by mfaisal           #+#    #+#             */
/*   Updated: 2023/06/25 20:14:41 by mofaisal         ###   ########.fr       */
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

typedef struct s_fork
{
	pthread_mutex_t fork;
} t_fork;


typedef struct s_philo
{
	int ph;
	int id;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	size_t time;
	t_fork *left_fork;
	t_fork *right_fork;
} t_philo;



typedef struct s_table
{
	t_philo *philo;
} t_table;


int	ft_digit(char *av[]);
int error_checking(int ac, char *av);
size_t	get_current_time(void);


# endif
