/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rha-le <rha-le@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:24:56 by rha-le            #+#    #+#             */
/*   Updated: 2025/07/04 20:01:26 by rha-le           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "builtin.h"
#include "libft.h"
#include "parser.h"

static int	_is_builtin(t_command *cmd)
{
	if (!ft_strcmp(cmd->program, "echo"))
		return (1);
	else if (!ft_strcmp(cmd->program, "cd"))
		return (1);
	else if (!ft_strcmp(cmd->program, "pwd"))
		return (1);
	else if (!ft_strcmp(cmd->program, "export"))
		return (1);
	else if (!ft_strcmp(cmd->program, "unset"))
		return (1);
	else if (!ft_strcmp(cmd->program, "env"))
		return (1);
	else if (!ft_strcmp(cmd->program, "exit"))
		return (1);
	return (0);
}

static int	_execute_builtin(t_command *cmd, t_list **cmd_list)
{
	if (!ft_strcmp(cmd->program, "echo"))
		return (1);
	else if (!ft_strcmp(cmd->program, "cd"))
		return (1);
	else if (!ft_strcmp(cmd->program, "pwd"))
		return (1);
	else if (!ft_strcmp(cmd->program, "export"))
		return (1);
	else if (!ft_strcmp(cmd->program, "unset"))
		return (1);
	else if (!ft_strcmp(cmd->program, "env"))
		return (1);
	else if (!ft_strcmp(cmd->program, "exit"))
		return (builtin_exit(cmd->argc, cmd->argv, cmd_list));
	return (EXIT_SUCCESS);
}

static int	_execute_cmd(t_list *current_cmd, t_list **cmd_list, int *err)
{
	if (_is_builtin(current_cmd->content))
	{
		printf("EXECUTING BUILTIN...\n");
		*err = _execute_builtin(current_cmd->content, cmd_list);
		if (*err)
			return*(err);
	}
	else
		printf("EXECUTING NON-BUILTIN...\n");
	return (EXIT_SUCCESS);
}

int	executor(t_list **cmd_list)
{
	int		err;
	t_list	*current;

	current = *cmd_list;
	err = 0;
	if (_execute_cmd(current, cmd_list, &err))
		return (err);
	return (EXIT_SUCCESS);
}
