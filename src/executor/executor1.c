/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwobie <student@42>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 15:58:33 by rtwobie           #+#    #+#             */
/*   Updated: 2025/08/20 17:57:55 by rtwobie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#include "builtin.h"
#include "executor_internal.h"
#include "run.h"

unsigned char	_get_exit_status(pid_t pid)
{
	int	status;

	status = 0;
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return ((unsigned char)WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return ((unsigned char)(WTERMSIG(status) + 128));
	return ((unsigned char)status);
}

int	_restore_stdfd(int restorefd[2])
{
	if (dup2(restorefd[0], STDIN_FILENO) < 0)
		return (close_fds(restorefd), perror("restore stdin"), EXIT_FAILURE);
	if (dup2(restorefd[1], STDOUT_FILENO) < 0)
		return (close_fds(restorefd), perror("restore stdout"), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

unsigned char	_exec_builtin(t_data *data, t_command_node *cmd)
{
	int	status;

	status = 0;
	if (!ft_strcmp(cmd->program_argv[0], "cd")
		|| !ft_strcmp(cmd->program_argv[0], "pwd")
		|| !ft_strcmp(cmd->program_argv[0], "env"))
		status = cd(cmd->program_argv, data->envp, -1);
	if (!ft_strcmp(cmd->program_argv[0], "echo"))
		status = echo(cmd->program_argv);
	else if (!ft_strcmp(cmd->program_argv[0], "exit"))
		exit_(cmd->program_argv, data);
	return ((unsigned char)status);
}
