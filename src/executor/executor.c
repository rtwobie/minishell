/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgroo <student@42.de>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 14:07:47 by admin             #+#    #+#             */
/*   Updated: 2025/08/05 12:10:25 by fgroo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>

#include "parser.h"
#include "executor_internal.h"
#include "executor.h"

static	unsigned char	_get_exit_status(pid_t pid)
{
	unsigned char	exit_status;
	int				status;

	exit_status = 0;
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		exit_status = (unsigned char)WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		exit_status = (unsigned char)WTERMSIG(status) + 128;
	return (exit_status);
}

static int	_exec_cmd(t_command_node *cmd, unsigned char *exit_status,
int fd_in, int fd_out)
{
	pid_t	pid;
	char	*program;

	program = NULL;
	// if (is_builtin(cmd->program_argv[0]))
	// 	return (_exec_builtin());
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
			(free(program), exit(EXIT_FAILURE));
		if (execve(program, cmd->program_argv, NULL))
			(free(program), exit(127));
	}
	*exit_status = _get_exit_status(pid);
	return (free(program), EXIT_SUCCESS);
}

static int	_exec_node(t_ast_node *node, unsigned char *exit_status,
int fdin, int fdout)
{
	int		pipefd[2];

	if (node == NULL)
		return (EXIT_FAILURE);
	if (node->type == NODE_TYPE_COMMAND)
	{
		if (_exec_cmd(node->data.command_node, exit_status, fdin, fdout))
			return (EXIT_FAILURE);
	}
	else if (node->type == NODE_TYPE_PIPE)
	{
		pipe(pipefd);
		_exec_node(node->data.pipe_node->left, exit_status, fdin, pipefd[1]);
		close(pipefd[1]);
		_exec_node(node->data.pipe_node->right, exit_status, pipefd[0], fdout);
		close(pipefd[0]);
	}
	return (EXIT_SUCCESS);
}

int	executor(t_ast_node **tree, unsigned char *exit_status, char **envp)
{
	(void)envp;
	if (!tree || !*tree)
		return (EXIT_FAILURE);
	if (_exec_node(*tree, exit_status, STDIN_FILENO, STDOUT_FILENO))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
