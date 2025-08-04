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

#include <readline/readline.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>

#include "parser.h"
#include "executor_internal.h"
#include "executor.h"

static int	_execute_simple_cmd(t_ast_node **tree, t_command_node *cmd,
int fd_in, int fd_out)
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
		rl_clear_history();
		if (redirect_io(cmd, fd_in, fd_out))
			(free(program), cleanup_ast(tree), exit(EXIT_FAILURE));
		if (execve(program, cmd->program_argv, NULL))
			(free(program), cleanup_ast(tree), exit(127));
	}
	else if (pid > 0)
		waitpid(pid, NULL, 0);
	return (free(program), EXIT_SUCCESS);
}

static int	_execute_node(t_ast_node **tree, t_ast_node *node,
int fd_in, int fd_out)
{
	int		pipefd[2];

	if (node == NULL)
		return (EXIT_FAILURE);
	if (node->type == NODE_TYPE_COMMAND)
	{
		if (_execute_simple_cmd(tree, node->data.command_node, fd_in, fd_out))
			return (EXIT_FAILURE);
	}
	else if (node->type == NODE_TYPE_PIPE)
	{
		pipe(pipefd);
		_execute_node(tree, node->data.pipe_node->left, fd_in, pipefd[1]);
		close(pipefd[1]);
		_execute_node(tree, node->data.pipe_node->right, pipefd[0], fd_out);
		close(pipefd[0]);
	}
	return (EXIT_SUCCESS);
}

int	executor(t_ast_node **tree, char **envp)
{
	(void)envp;
	if (!tree || !*tree)
		return (EXIT_FAILURE);
	if (_execute_node(tree, *tree, STDIN_FILENO, STDOUT_FILENO))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
