/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwobie <student@42>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 16:52:08 by rtwobie           #+#    #+#             */
/*   Updated: 2025/08/20 18:05:06 by rtwobie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "builtin.h"
#include "error.h"
#include "executor.h"
#include "executor_internal.h"
#include "run.h"
#include "signals.h"

static unsigned char	_exec_pipeline(t_data *data, t_ast_node *node, \
int fd_io[2]);

static unsigned char	_exec_cmd(t_data *data, t_command_node *cmd,
int fd_io[2])
{
	char	*program;
	int		status;

	if (redirect_io(cmd, fd_io[0], fd_io[1]))
		return (_restore_stdfd(data->restorefd), EXIT_FAILURE);
	if (!cmd->argv || !*cmd->argv)
		return (EXIT_SUCCESS);
	if (is_builtin(cmd->argv[0]))
		return (_exec_builtin(data, cmd));
	program = NULL;
	status = search_program(cmd->argv[0], &program);
	if (status)
		return (cleanup_data(data), (unsigned char)status);
	set_noninteractive_mode();
	execve(program, cmd->argv, data->envp);
	perror(program);
	free(program);
	cleanup_data(data);
	return (127);
}

/**
 * NOTE:
 * The third fd is the pipe end to close,
 * it's an identical copy of either fd[0] or fd[1].
 */
static int	_handle_fork(t_data *data, t_ast_node *node, pid_t *pid, int fd[3])
{
	*pid = fork();
	if (*pid == -1)
		return (close(fd[0]), close(fd[1]), EXIT_FAILURE);
	else if (*pid == 0)
	{
		close(fd[2]);
		exit(_exec_pipeline(data, node, fd));
	}
	set_ignore_mode();
	return (EXIT_SUCCESS);
}

static unsigned char	_exec_pipeline(t_data *data, t_ast_node *node,
int fd_io[2])
{
	pid_t		pid[2];
	int			pfd[2];
	t_ast_node	*l;
	t_ast_node	*r;

	if (node == NULL)
		return (EXIT_FAILURE);
	if (node->type == NODE_TYPE_PIPE)
	{
		l = node->data.pipe->left;
		r = node->data.pipe->right;
		if (pipe(pfd))
			return (EXIT_FAILURE);
		if (_handle_fork(data, l, &pid[0], (int [3]){fd_io[0], pfd[1], pfd[0]}))
			return (close_fds(pfd), EXIT_FAILURE);
		if (_handle_fork(data, r, &pid[1], (int [3]){pfd[0], fd_io[1], pfd[1]}))
			return (close_fds(pfd), waitpid(pid[0], NULL, 0), EXIT_FAILURE);
		close_fds(pfd);
		return (waitpid(pid[0], NULL, 0), _get_exit_status(pid[1]));
	}
	else if (node->type == NODE_TYPE_COMMAND)
		return (_exec_cmd(data, node->data.command, fd_io));
	else
		return (print_err(ERR_INVAL_NODE, "executor"), EXIT_FAILURE);
	return (EXIT_FAILURE);
}

static unsigned char	_single_cmd(t_data *data, t_command_node *cmd,
int fd[2])
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (EXIT_FAILURE);
	else if (pid == 0)
		exit(_exec_cmd(data, cmd, fd));
	set_ignore_mode();
	return (_get_exit_status(pid));
}

int	executor(t_data *data, t_ast_node *tree, unsigned char *exit_status)
{
	t_command_node	*cmd;

	if (!data || !data->tree)
		return (EXIT_FAILURE);
	cmd = tree->data.command;
	if (data->tree->type == NODE_TYPE_COMMAND)
	{
		if (cmd->argv && *cmd->argv && !is_builtin(cmd->argv[0]))
			*exit_status = _single_cmd(data, cmd, data->stdfd);
		else
			*exit_status = _exec_cmd(data, cmd, data->stdfd);
	}
	else if (data->tree->type == NODE_TYPE_PIPE)
		*exit_status = _exec_pipeline(data, tree, data->stdfd);
	else
		(print_err(ERR_INVAL_NODE, "executor"), *exit_status = EXIT_FAILURE);
	if (*exit_status == 131)
		write(STDERR_FILENO, "Quit (core dumped)\n", 20);
	if (_restore_stdfd(data->restorefd))
		*exit_status = EXIT_FAILURE;
	close_fds(data->restorefd);
	return (*exit_status);
}
