/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mofaisal <mofaisal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 22:04:20 by mofaisal          #+#    #+#             */
/*   Updated: 2023/02/26 12:10:40 by mofaisal         ###   ########.fr       */
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
		array[i] = NULL;
		i++;
	}
	free(array);
	array = NULL;
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

char	*find_command_existance(char **dir, char *cmd)
{
	char	*joinedstr;
	int		i;

	i = 0;
	while (dir[i])
	{
		joinedstr = ft_strjoin(dir[i], cmd);
		if (access(joinedstr, F_OK) == 0)
			return (free_string_array(dir), (free(cmd)), joinedstr);
		free(joinedstr);
		i++;
	}
	return (free(cmd), NULL);
}

char	*find_command_path(char **directories, char *command)
{
	int		i;
	int		j;
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
	return (find_command_existance(directories, cmd));
	i = -1;
	free_string_array(directories);
	return (NULL);
}

void	execute(char *argv, char **env, int fd)
{
	char	**flags;
	char	*path;
	char	**dirs;
	char	*tmp;

	tmp = NULL;
	path = get_path_from_env(env);
	if (argv && argv[0])
	{
		if (!path)
		{
			flags = ft_split(argv, ' ');
			if (!flags)
				tmp = NULL;
			else
				tmp = flags[0];
		}
		else
		{
			flags = ft_split(argv, ' ');
			if (!flags || argv[0] == ' ')
				tmp = NULL;
			else
			{
				dirs = ft_split(path, ':');
				tmp = find_command_path(dirs, flags[0]);
			}
		}
		close(fd);
		if (tmp)
		{
			if (execve(tmp, flags, env) < 0)
			{
				free(tmp);
				exit((write(2, "Error: Executing the command failed\n", 37))
					* 0 + 1);
			}
		}
		else
		{
			free(tmp);
			exit((write(2, "Error: Command not found\n",
						ft_strlen("Error: Command not found\n"))) * 0 + 1);
		}
	}
	else
	{
		free(path);
		exit((write(2, "Error: Command not found\n",
					ft_strlen("Error: Command not found\n"))) * 0 + 1);
	}
}
