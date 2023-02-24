/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mofaisal <mofaisal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 22:04:20 by mofaisal          #+#    #+#             */
/*   Updated: 2023/02/24 21:20:07 by mofaisal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_string_array(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	open_file_and_redirect_input(char *file_path)
{
	int	fd;

	fd = open(file_path, O_RDONLY);
	if (fd == -1)
	{
		perror("Error while opening the file");
		exit(1);
	}
	dup2(fd, STDIN_FILENO);
}

char	*get_path_from_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if ((ft_strncmp("PATH=", env[i], 5) == 0))
			return (ft_strdup((env[i] + 5)));
		i++;
	}
	return (NULL);
}

char	*find_command_path(char **directories, char *command)
{
	int		i;
	int		j;
	char	*joinedstr;
	char	*cmd;

	i = 0;
	j = 1;
	cmd = malloc(ft_strlen(command) + 2);
	cmd[0] = '/';
	i = 0;
	while (command[i] && command[i] != ' ')
		cmd[j++] = command[i++];
	cmd[ft_strlen(command) + 1] = '\0';
	i = 0;
	if (access(command, F_OK) == 0)
		return (command);
	while (directories[i])
	{
		joinedstr = ft_strjoin(directories[i], cmd);
		if (access(joinedstr, F_OK) == 0)
			return (joinedstr);
		free(joinedstr);
		i++;
	}
	i = -1;
	while (directories[++i])
		free(directories[i]);
	free(directories);
	return (NULL);
}

void	execute(char *argv, char **env)
{
	char	**flags;
	char	*path;
	char	**dirs;
	char	*tmp;

	tmp = NULL;
	path = get_path_from_env(env);
	if (!path)
		exit((write(2, "Error: While Finding PATH\n", 27)) * 0 + 1);
	flags = ft_split(argv, ' ');
	dirs = ft_split(path, ':');
	tmp = find_command_path(dirs, flags[0]);
	if (execve(tmp, flags, env) < 0)
		exit((write(2, "Error: Executing the command failed\n", 37)) * 0 + 1);
	exit(0);
}
