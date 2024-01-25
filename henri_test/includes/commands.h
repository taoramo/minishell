/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 16:09:06 by hpatsi            #+#    #+#             */
/*   Updated: 2024/01/25 11:15:14 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_H
# define COMMANDS_H

# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>

# include "libft.h"

int		extract_files(int file_fds[], char *str);

void	remove_redirects(char **str);

int		quote_length(char *str);

/**
 * Splits command by whitespaces outside quotations.
 * 
 * @param[in] str The string to be split.
 * @returns A list of strings or a null pointer on fail.
 */
char	**split_command(char *str);

/**
 * Tries to add a valid path to a command.
 * 
 * @param[in] command The command name without a path.
 * @param[in] paths A list of paths to search.
 * @returns The command with a valid path or a copy of the original command if no path found.
 */
char	*add_path(char *command, char **paths);

/**
 * Creates a child process and runs the given command, with the option to overwrite stdin and stdout.
 * 
 * @param[in] file_fds The file descriptors to replace stdin (index 0) and stdout (index 1).
 * @param[in] command The command in argv format.
 * @returns Process id of the child process created to run the command or -1 on fail.
 */
int		run_command(int file_fds[], char **command);
int		execute_command(int input_fd, int output_fd, char **command);

/**
 * Runs all the given commands through a pipe.
 * 
 * @param[in] commands A list of commands in argv format.
 * @param[in] file_fds An array of file descriptors, replace stdin at index 0 and replace stdout at index 1.
 * @returns Returns the exit code of the final command or -1 on fail.
 */
int		pipex(char ***commands, int file_fds[]);
int		pipe_commands(char ***commands, int *file_fds, int **process_ids);

#endif