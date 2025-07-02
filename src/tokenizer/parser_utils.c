/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rha-le <rha-le@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 16:13:59 by rha-le            #+#    #+#             */
/*   Updated: 2025/07/02 16:19:58 by rha-le           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdlib.h>

void	free_args(char **args)
{
	size_t	i;

	i = 0;
	while (args[i])
	{
		free(args[i]);
		++i;
	}
	free(args);
}

void	free_cmd(void	*command_struct)
{
	t_command	*cmd;

	cmd = (t_command *)command_struct;
	free(cmd->program);
	free_args(cmd->args);
	free(cmd);
}
