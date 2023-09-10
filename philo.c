/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mofaisal <mofaisal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 20:28:45 by mfaisal           #+#    #+#             */
/*   Updated: 2023/09/08 21:41:27 by mofaisal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int ac, char *av[])
{
    if (!(ac < 5) && !(ac > 6))
    {
       if (!ft_digit(av))
           return (printf("Error: Invalid arguments\n"), 0);
       else if (ft_atoi(av[1]) < 1 || ft_atoi(av[1]) > 200)
           return (printf("Error: Invalid number of philosophers\n"), 0);
       else if (ft_atoi(av[2]) < 60 || ft_atoi(av[3]) < 60 || ft_atoi(av[4]) < 60)
           return (printf("Error: Invalid time\n"), 0);
       else if (ac == 6 )
       {
            if (ft_atoi(av[5]) < 1)
            return (printf("Error: Invalid number of times to eat\n"), 0);
       }
        threads(ac, av);
    }
    else
         printf("Error: Invalid number of arguments\n");   
    return (0);
}

