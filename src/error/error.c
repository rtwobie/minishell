/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgroo <student@42.de>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 17:46:01 by rtwobie           #+#    #+#             */
/*   Updated: 2025/08/22 19:28:46 by rtwobie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <unistd.h>

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
	else if (err == ERR_ONLY_ONE_ARG)
		return ("wrong amount of arguments: needed one");
	else if (err == ERR_INVAL_NODE)
		return ("wrong node type in ast");
	return ("error");
}

void	print_hdoc_warning(char *eof)
{
	ft_putstr_fd("-minishell: ", STDERR_FILENO);
	ft_putstr_fd("warning: ", STDERR_FILENO);
	ft_putstr_fd("here-document delimited by end-of-file ", STDERR_FILENO);
	ft_putstr_fd("(wanted `", STDERR_FILENO);
	ft_putstr_fd(eof, STDERR_FILENO);
	ft_putstr_fd("')\n", STDERR_FILENO);
}

void	print_err_unexpected_tok(char *value)
{
	ft_putstr_fd("syntax error near token `", STDERR_FILENO);
	ft_putstr_fd(value, STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
}

void	print_err(int err, char *location)
{
	if (err == 0)
		return ;
	if (err < 0)
		ft_putstr_fd("-minishell: ", STDERR_FILENO);
	if (err == ERR_UNEXPECTED_TOK)
	{
		print_err_unexpected_tok(location);
		return ;
	}
	ft_putstr_fd(location, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	if (err < 0)
		ft_putstr_fd(_lookup_err(err), STDERR_FILENO);
	else if (err > 0)
		ft_putstr_fd(strerror(err), STDERR_FILENO);
	write(STDERR_FILENO, "\n", 1);
}
