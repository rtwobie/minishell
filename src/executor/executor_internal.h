/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_internal.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rha-le <rha-le@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 21:54:52 by rha-le            #+#    #+#             */
/*   Updated: 2025/08/04 21:55:35 by rha-le           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_INTERNAL_H
# define EXECUTOR_INTERNAL_H

# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>

# include "parser.h"

// typedef struct s_pid
// {
// 	int					data;
// 	struct s_pidfork	*next;
// } t_pid;

typedef struct s_pid
{
	int		pipefd[2];
	pid_t	pid_left;
	pid_t	pid_right;
	int		input_fd;
	int		output_fd;
}	t_pid;

// redirect.c
int		redirect_io(t_command_node *cmd, int input_fd, int output_fd);

// search_program.c
int	search_program(char *lookup, char **program);
// char	*search_program(char *program);

#endif // !EXECUTOR_INTERNAL_H
