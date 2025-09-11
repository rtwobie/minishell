/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwobie <student@42>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 16:00:46 by rtwobie           #+#    #+#             */
/*   Updated: 2025/09/11 16:01:03 by rtwobie          ###   ########.fr       */
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
	int		status;
	size_t	i;

	status = 0;
	if (!ft_strcmp(cmd->argv[0], "cd")
		|| !ft_strcmp(cmd->argv[0], "pwd")
		|| !ft_strcmp(cmd->argv[0], "env"))
		status = cd(cmd->argv, data, -1);
	else if (!ft_strcmp(cmd->argv[0], "echo"))
		status = echo(cmd->argv);
	else if (!ft_strcmp(cmd->argv[0], "export"))
		status = _export(cmd->argv, data, 0);
	else if (!ft_strcmp(cmd->argv[0], "unset"))
	{
		i = 0;
		while (cmd->argv[++i])
			status = _unset(cmd->argv[i],
					ft_strlen(cmd->argv[i]), data, &(int){0});
	}
	else if (!ft_strcmp(cmd->argv[0], "exit"))
		status = exit_(cmd->argv, data);
	return ((unsigned char)status);
}
