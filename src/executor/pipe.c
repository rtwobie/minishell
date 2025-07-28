/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgorlich <fgorlich@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 14:07:47 by admin             #+#    #+#             */
/*   Updated: 2025/07/28 17:22:01 by rha-le           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "parser.h"
#include "executor.h"
#include "libft.h"

static void	_execute_command(t_command_node *com_nd)
{
	char	*program;

	program = ft_strjoin("/bin/", com_nd->program_argv[0]);
	execve(program, com_nd->program_argv, NULL);
}

static void	_redirect_io(int input_fd, int output_fd)
{
	if (input_fd != STDIN_FILENO)
	{
		if (dup2(input_fd, STDIN_FILENO) == -1)
			perror("error duplicating input\n"); // or better an errno
	}
	if (output_fd != STDOUT_FILENO)
	{
		if (dup2(output_fd, STDOUT_FILENO) == -1)
			perror("error duplicating output\n"); // or better an errno
	}
	if (input_fd != STDIN_FILENO)
		close(input_fd);
	if (output_fd != STDOUT_FILENO)
		close(output_fd);
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
			_redirect_io(input_fd, output_fd);
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
		return (-1);
	_execute_node(*tree, STDIN_FILENO, STDOUT_FILENO);
	return (0);
}
