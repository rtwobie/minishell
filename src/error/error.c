/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rha-le <rha-le@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 17:46:01 by rha-le            #+#    #+#             */
/*   Updated: 2025/07/31 15:21:37 by rha-le           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "error.h"
#include "libft.h"

char	*_lookup_err(int err)
{
	if (err == ERR_SYNTAX)
		return ("syntax error");
	else if (err == ERR_TOOMANY_ARGS)
		return ("too many arguments");
	return ("error");
}

void	print_error(int err)
{
	ft_putstr_fd("-minishell: ", STDERR_FILENO);
	ft_putstr_fd(_lookup_err(err), STDERR_FILENO);
	write(STDERR_FILENO, "\n", 1);
}

void	print_err(int err, char *location, char *strerror)
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
		ft_putstr_fd(strerror, STDERR_FILENO);
	write(STDERR_FILENO, "\n", 1);
}
