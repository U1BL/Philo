/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mofaisal <mofaisal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 22:04:28 by mofaisal          #+#    #+#             */
/*   Updated: 2023/02/22 21:56:53 by mofaisal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **env)
{
	char	*path;
	char	*cmd_path;
	pid_t	pid;
	int		fd[2];
	
	if (argc != 5)
		exit(ft_printf(STRING) * 0 + 1);

	pid = fork();
	pipe(fd);
	if (pid == 0)
	{
		child_process(argv, env, fd);
	}
	else if (pid < 0)
		return (ft_printf("Forking the process failed\n"), 0);
	else
	{
		wait(NULL);
		parent_process(argv, env, fd);
	}

	
	free_string_array(dirs);
	free(cmd_path);
	free(path);
	return (0);
}
