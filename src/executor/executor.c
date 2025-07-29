/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgorlich <fgorlich@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 14:07:47 by admin             #+#    #+#             */
/*   Updated: 2025/07/28 23:58:39 by rha-le           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "parser.h"
#include "executor_internal.h"
#include "executor.h"
#include "libft.h"

static void	_execute_command(t_command_node *com_nd)
{
	char	*program;

	program = ft_strjoin("/bin/", com_nd->program_argv[0]);
	if (execve(program, com_nd->program_argv, NULL))
		perror(com_nd->program_argv[0]);
}

static void	_execute_node(t_ast_node *node, int input_fd, int output_fd)
{
	pid_t	pid;
	int		pipefd[2];

	if (node == NULL)
		return ;
	if (node->type == NODE_TYPE_COMMAND)
	{
		pid = fork();
		if (pid == 0)
		{
			_redirect_io(node->data.command_node, input_fd, output_fd);
			_execute_command(node->data.command_node);
			exit(127);
		}
		if (pid > 0)
			waitpid(pid, NULL, 0);
	}
	else if (node->type == NODE_TYPE_PIPE)
	{
		pipe(pipefd);
		_execute_node(node->data.pipe_node->left, input_fd, pipefd[1]);
		close(pipefd[1]);
		_execute_node(node->data.pipe_node->right, pipefd[0], output_fd);
		close(pipefd[0]);
	}
}

int	executor(t_ast_node **tree)
{
	if (!tree || !*tree)
		return (EXIT_FAILURE);
	_execute_node(*tree, STDIN_FILENO, STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
