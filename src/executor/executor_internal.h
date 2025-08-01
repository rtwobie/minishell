/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_internal.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rha-le <rha-le@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 17:19:33 by rha-le            #+#    #+#             */
/*   Updated: 2025/07/31 18:26:58 by rha-le           ###   ########.fr       */
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

void	_redirect_io(t_command_node *cmd, int input_fd, int output_fd);

// search_program.c
char	*search_program(char *program);

#endif // !EXECUTOR_INTERNAL_H
