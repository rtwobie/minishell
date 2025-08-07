/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgroo <student@42.de>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 14:07:47 by admin             #+#    #+#             */
/*   Updated: 2025/08/06 20:25:03 by rha-le           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>

#include "builtin.h"
#include "parser.h"
#include "executor_internal.h"
#include "executor.h"

static int	_get_exit_status(pid_t pid)
{
	int	status;

	status = 0;
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (WTERMSIG(status) + 128);
	return (status);
}

static int	_exec_builtin(t_command_node *cmd, int fd_in, int fd_out,
char **envp)
{
	int	status;

	(void)envp;
	printf("EXECUTING BUILTIN...\n"); // debug
	status = 0;
	if (redirect_io(cmd, fd_in, fd_out))
		return (EXIT_FAILURE);
	if (!ft_strcmp(cmd->program_argv[0], "echo"))
		status = echo(cmd->program_argv);
	return (status);
}

static int	_exec_cmd(t_command_node *cmd, int fd_in, int fd_out, char **envp)
{
	pid_t	pid;
	char	*program;

	program = NULL;
	if (is_builtin(cmd->program_argv[0]))
		return (_exec_builtin(cmd, fd_in, fd_out, envp));
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
	return (free(program), _get_exit_status(pid));
}

static int	_handle_pipe(t_ast_node *node, int fdin, int fdout, char **envp);

static int	_exec(t_ast_node *node, int fdin, int fdout, char **envp)
{
	if (node == NULL)
		return (EXIT_FAILURE);
	if (node->type == NODE_TYPE_COMMAND)
		return (_exec_cmd(node->data.command_node, fdin, fdout, envp));
	else if (node->type == NODE_TYPE_PIPE)
		return (_handle_pipe(node, fdin, fdout, envp));
	return (EXIT_FAILURE);
}

static int	_handle_pipe(t_ast_node *node, int fdin, int fdout, char **envp)
{
	pid_t	pid[2];
	int		pfd[2];
	int		st;

	if (pipe(pfd))
		return (EXIT_FAILURE);
	pid[0] = fork();
	if (pid[0] < 0)
		return (close(pfd[0]), close(pfd[1]), EXIT_FAILURE);
	else if (pid[0] == 0)
	{
		(close(pfd[0]), st = _exec(node->data.pipe_node->left, fdin, pfd[1], envp));
		(rl_clear_history(), exit(st));
	}
	pid[1] = fork();
	if (pid[1] < 0)
		return (close(pfd[0]), close(pfd[1]), EXIT_FAILURE);
	else if (pid[1] == 0)
	{
		(close(pfd[1]), st = _exec(node->data.pipe_node->right, pfd[0], fdout, envp));
		(rl_clear_history(), exit(st));
	}
	(close(pfd[0]), close(pfd[1]));
	return (waitpid(pid[0], NULL, 0), _get_exit_status(pid[1]));
}

int	executor(t_ast_node **tree, unsigned char *exit_status, char **envp)
{
	int	fd[2];

	if (!tree || !*tree)
		return (EXIT_FAILURE);
	fd[0] = dup(STDIN_FILENO);
	fd[1] = dup(STDOUT_FILENO);
	if (fd[0] < 0 || fd[1] < 0)
	{
		(close(fd[0]), close(fd[1]), perror("dup failed"));
		return (EXIT_FAILURE);
	}
	*exit_status = (unsigned char)_exec(*tree, STDIN_FILENO, STDOUT_FILENO, envp);
	if (dup2(fd[0], STDIN_FILENO) == -1 || dup2(fd[1], STDOUT_FILENO) == -1)
	{
		(close(fd[0]), close(fd[1]), perror("dup2 failed"));
		return (EXIT_FAILURE);
	}
	if (*exit_status != 0)
	{
		(close(fd[0]), close(fd[1]));
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
