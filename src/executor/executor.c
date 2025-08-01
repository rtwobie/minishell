/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgorlich <fgorlich@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 14:07:47 by admin             #+#    #+#             */
/*   Updated: 2025/07/31 19:03:12 by rha-le           ###   ########.fr       */
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

// TODO: search for cmd first then fork
// TODO: case: `$ argument/` -> throw error "Is a directory" (from errno)
//				or "Not a directory"
// TODO: case: `$ argument/path` -> find absolut/relative path
// TODO: understand getenv()
// TODO: understand execve() specifically the 3 param

static int	_execute_simple_command(t_command_node *cmd, int fd_in, int fd_out)
{
	pid_t	pid;
	char	*program;

	program = NULL;
	if (cmd->program_argv[0])
	{
		program = search_program(cmd->program_argv[0]);
		if (!program)
			return (EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1)
		return (EXIT_FAILURE);
	else if (pid == 0)
	{
		_redirect_io(cmd, fd_in, fd_out);
		if (execve(program, cmd->program_argv, NULL))
		{
			free(program);
			exit(127);
		}
	}
	else if (pid > 0)
		waitpid(pid, NULL, 0);
	return (free(program), EXIT_SUCCESS);
}

// static int	_execute_node(t_ast_node *node, int fd_in, int fd_out)
// {
// 	int		pipefd[2];
//
// 	if (node == NULL)
// 		return (EXIT_FAILURE);
// 	if (node->type == NODE_TYPE_COMMAND)
// 		_execute_simple_command(node->data.command_node, fd_in, fd_out);
// 	else if (node->type == NODE_TYPE_PIPE)
// 	{
// 		pipe(pipefd);
// 		_execute_node(node->data.pipe_node->left, fd_in, pipefd[1]);
// 		close(pipefd[1]);
// 		_execute_node(node->data.pipe_node->right, pipefd[0], fd_out);
// 		close(pipefd[0]);
// 	}
// 	return (EXIT_SUCCESS);
// }

int	executor(t_ast_node **tree, char **envp)
{
	(void)envp;
	if (!tree || !*tree)
		return (EXIT_FAILURE);
	t_command_node *cmd = (t_command_node *)(*tree)->data.command_node;
	_execute_simple_command(cmd, STDIN_FILENO, STDOUT_FILENO);
	// _execute_node(*tree, STDIN_FILENO, STDOUT_FILENO);

	return (EXIT_SUCCESS);
}
