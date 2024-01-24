/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 16:09:06 by hpatsi            #+#    #+#             */
/*   Updated: 2024/01/24 15:10:10 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_H
# define COMMANDS_H

# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>

# include "libft.h"

char	**split_command(char *str);
char	*add_path(char *command, char **paths);
int		run_command(int input_fd, int output_fd, char **command);
int		execute_command(int input_fd, int output_fd, char **command);

int		pipex(char ***commands, int file_fds[]);
int		pipe_commands(char ***commands, int *file_fds, int **process_ids);

#endif