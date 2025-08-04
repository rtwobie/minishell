/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rha-le <rha-le@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 17:46:01 by rha-le            #+#    #+#             */
/*   Updated: 2025/07/31 19:02:49 by rha-le           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <unistd.h>
#include <errno.h>

#include "error.h"
#include "libft.h"

char	*_lookup_err(int err)
{
	if (err == ERR_SYNTAX)
		return ("syntax error");
	else if (err == ERR_TOOMANY_ARGS)
		return ("too many arguments");
	else if (err == ERR_CMD_NOTFOUND)
		return ("command not found");
	return ("error");
}

void	print_error(int err)
{
	ft_putstr_fd("-minishell: ", STDERR_FILENO);
	ft_putstr_fd(_lookup_err(err), STDERR_FILENO);
	write(STDERR_FILENO, "\n", 1);
}

void	print_err(int err, char *location)
{
	if (err == 0)
		return ;
	if (err < 0)
		ft_putstr_fd("-minishell: ", STDERR_FILENO);
	ft_putstr_fd(location, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	if (err < 0)
		ft_putstr_fd(_lookup_err(err), STDERR_FILENO);
	else if (err > 0)
		strerror(err);
	write(STDERR_FILENO, "\n", 1);
}
