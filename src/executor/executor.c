/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgroo <student@42.eu>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 14:07:47 by admin             #+#    #+#             */
/*   Updated: 2025/08/08 00:10:09 by fgroo            ###   ########.fr       */
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
#include "builtin.h"
#include "run.h"

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

static int	_exec_builtin(t_data *data, t_command_node *cmd,
int fd_io[2], char **envp)
{
	int	status;

	printf("EXECUTING BUILTIN...\n"); // debug
	status = 0;
	if (redirect_io(cmd, fd_io[0], fd_io[1]))
		return (EXIT_FAILURE);
	if (!ft_strcmp(cmd->program_argv[0], "cd")
		|| !ft_strcmp(cmd->program_argv[0], "pwd")
		|| !ft_strcmp(cmd->program_argv[0], "env"))
			status = cd(cmd->program_argv, envp, -1);
	if (!ft_strcmp(cmd->program_argv[0], "echo"))
		status = echo(cmd->program_argv);
	else if  (!ft_strcmp(cmd->program_argv[0], "exit"))
		exit_(cmd->program_argv, data);
	return (status);
}

static int	_exec_cmd(t_data *data, t_command_node *cmd,
int fd_io[2], char **envp)
{
	pid_t	pid;
	char	*program;
	int		status;

	program = NULL;
	if (is_builtin(cmd->program_argv[0]))
		return (_exec_builtin(data, cmd, fd_io, envp));
	if (cmd->program_argv[0])
	{
		status = search_program(cmd->program_argv[0], &program);
		if (status)
			return (status);
	}
	pid = fork();
	if (pid == -1)
		return (free(program), EXIT_FAILURE);
	else if (pid == 0)
	{
		rl_clear_history();
		if (redirect_io(cmd, fd_io[0], fd_io[1]))
			(free(program), exit(EXIT_FAILURE));
		if (execve(program, cmd->program_argv, envp))
			(free(program), exit(127));
	}
	return (free(program), _get_exit_status(pid));
}

static int	_handle_pipe(t_data *data, t_ast_node *node,
int fd_io[2], char **envp);

static int	_exec(t_data *data, t_ast_node *node, int fd_io[2], char **envp)
{
	if (node == NULL)
		return (EXIT_FAILURE);
	if (node->type == NODE_TYPE_COMMAND)
		return (_exec_cmd(data, node->data.command, fd_io, envp));
	else if (node->type == NODE_TYPE_PIPE)
		return (_handle_pipe(data, node, fd_io, envp));
	return (EXIT_FAILURE);
}

static int	_handle_pipe(t_data *data, t_ast_node *node,
int fd_io[2], char **envp)
{
	pid_t	pid[2];
	int		pipefd[2];

	if (pipe(pipefd))
		return (EXIT_FAILURE);
	pid[0] = fork();
	if (pid[0] < 0)
		return (close(pipefd[0]), close(pipefd[1]), EXIT_FAILURE);
	else if (pid[0] == 0)
	{
		(close(pipefd[0]), fd_io[1] = pipefd[1], rl_clear_history());
		exit(_exec(data, node->data.pipe->left, fd_io, envp));
	}
	pid[1] = fork();
	if (pid[1] < 0)
		return (close(pipefd[0]), close(pipefd[1]), waitpid(pid[0], NULL, 0),
			EXIT_FAILURE);
	else if (pid[1] == 0)
	{
		(close(pipefd[1]), fd_io[0] = pipefd[0], rl_clear_history());
		exit(_exec(data, node->data.pipe->right, fd_io, envp));
	}
	(close(pipefd[0]), close(pipefd[1]));
	return (waitpid(pid[0], NULL, 0), _get_exit_status(pid[1]));
}

int	executor(t_data *data, unsigned char *exit_status, char **envp)
{
	if (!data || !data->tree)
		return (EXIT_FAILURE);
	*exit_status = (unsigned char)_exec(data, data->tree, data->stdfd, envp);
	if (dup2(data->restorefd[0], STDIN_FILENO) < 0
	|| dup2(data->restorefd[1], STDOUT_FILENO) < 0)
	{
		(close(data->restorefd[0]), close(data->restorefd[1]));
		return (perror("dup2 failed"), EXIT_FAILURE);
	}
	return (close(data->restorefd[0]), close(data->restorefd[1]), *exit_status);
}
