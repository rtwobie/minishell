/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgorlich <fgorlich@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 14:13:10 by fgorlich          #+#    #+#             */
/*   Updated: 2025/07/28 14:13:26 by fgorlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPE_H
# define PIPE_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "parser.h"
# include "pipe.h"
# include "libft.h"

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

void	execute_command(t_command_node *com_nd);
void	redirect_io(int input_fd, int output_fd);
int		main_pipe(t_ast_node **tree);
void	execute_node(t_ast_node *node, int input_fd, int output_fd);

#endif
