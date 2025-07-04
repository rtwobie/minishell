/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rha-le <rha-le@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 17:46:01 by rha-le            #+#    #+#             */
/*   Updated: 2025/07/04 19:59:41 by rha-le           ###   ########.fr       */
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
	ft_putstr_fd(_lookup_err(err), STDERR_FILENO);
	write(STDERR_FILENO, "\n", 1);
}
