/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mofaisal <mofaisal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 19:09:08 by mofaisal          #+#    #+#             */
/*   Updated: 2023/03/07 19:49:45 by mofaisal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *input, ...)
{
	int		result;
	int		i;
	va_list	args;

	va_start(args, input);
	i = 0;
	result = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '%' && input[i + 1])
			result += ft_format(args, input[++i]);
		else
			result += ft_putchar(input[i]);
		i++;
	}
	va_end(args);
	return (result);
}

#include <stdio.h>
int main()
{
	int m = ft_printf("%s%d%s\n", "jklj", 3131, "jhjkhk");
	ft_printf("%d\n", m);
	return (0);
}