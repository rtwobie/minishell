/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rha-le <rha-le@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 17:03:40 by rha-le            #+#    #+#             */
/*   Updated: 2025/08/06 17:18:28 by rha-le           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#include "libft.h"

int	is_builtin(char *program)
{
	if (!ft_strcmp(program, "echo"))
		return (1);
	return (0);
}

int	echo(char *argv[])
{
	size_t	i;
	bool	newline;

	if (!argv || !argv[1])
		return (ft_putstr_fd("\n", STDOUT_FILENO), EXIT_SUCCESS);
	i = 1;
	newline = true;
	if (!ft_strcmp("-n", argv[1]))
	{
		newline = false;
		++i;
	}
	while (argv[i])
	{
		ft_putstr_fd(argv[i], STDOUT_FILENO);
		++i;
		if (argv[i])
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
	if (newline)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
