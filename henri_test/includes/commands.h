/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 16:09:06 by hpatsi            #+#    #+#             */
/*   Updated: 2024/01/25 17:58:14 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_H
# define COMMANDS_H

# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>

# include "libft.h"
# include "strs_helpers.h"

typedef struct s_command
{
	t_vec	argv;
	int		stdin_fd;
	int		stdout_fd;
	int		stderr_fd;
}	t_command;

/**
 * Tries to open any redirected infiles or outfiles and sets the infile and outfile fds.
 * 
 * @param[in] file_fds The file fds for input and output files. Set to stdin and stdout if no redirects.
 * @param[in] str The string to search.
 * @returns On fail returns -1.
 */
int		extract_files(t_command *command);

/**
 * Removes redirects from a command string by replacing them with spaces.
 * 
 * @param[in] str A pointer to the string to modify.
 */
void	remove_redirects(char **str);

/**
 * Finds the length of the string inside quotations.
 * 
 * @param[in] str A pointer to the start of the quote.
 * @returns The length of the string inside quotations or -1 on unclosed quote.
 */
int		quote_length(char *str);

/**
 * Splits command by whitespaces outside quotations.
 * 
 * @param[in] str The string to be split.
 * @returns A list of strings or a null pointer on fail.
 */
int		split_command(t_vec *strs, char *str);

/**
 * Tries to add a valid path to a command based on env paths.
 * 
 * @param[in] command The command name without a path.
 * @returns The command with a valid path or a copy of the original command if no path found.
 */
char	*add_path(char *command);

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