/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mofaisal <mofaisal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 18:16:01 by mofaisal          #+#    #+#             */
/*   Updated: 2023/02/22 21:02:21 by mofaisal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# define STRING "You Have Entered Few Arguments Than Expected\n"

# include <unistd.h>
# include "./libft/libft.h"
# include "./printf/ft_printf.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <sys/wait.h>
# include <time.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <unistd.h>

void	free_string_array(char **array);
void	open_file_and_redirect_input(char *file_path);
char	*get_path_from_env(char **env);
char	*find_command_path(char **directories, char *command);
int		child_process(char *command, char *output_file_path,
			char *command_path);

#endif