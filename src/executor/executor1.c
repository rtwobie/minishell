/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwobie <student@42>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 15:58:33 by rtwobie           #+#    #+#             */
/*   Updated: 2025/08/22 13:19:27 by rtwobie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#include "builtin.h"
#include "executor_internal.h"
#include "run.h"

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
	if (!ft_strcmp(cmd->argv[0], "cd")
		|| !ft_strcmp(cmd->argv[0], "pwd")
		|| !ft_strcmp(cmd->argv[0], "env"))
		status = cd(cmd->argv, data, -1);
	if (!ft_strcmp(cmd->argv[0], "echo"))
		status = echo(cmd->argv);
	else if (!ft_strcmp(cmd->argv[0], "exit"))
		status = exit_(cmd->argv, data);
	return ((unsigned char)status);
}
