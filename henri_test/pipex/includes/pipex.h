/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 16:09:06 by hpatsi            #+#    #+#             */
/*   Updated: 2024/01/19 14:23:26 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPE_H
# define PIPE_H

# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>

# include "libft.h"

int		pipex(char ***commands, int file_fds[]);

int		pipe_commands(char ***commands, int *file_fds, int **process_ids);

int		count_commands(char ***commands);
void	print_command_fd(char **command, int fd);
void	print_commands_fd(char ***commands, int fd);

#endif