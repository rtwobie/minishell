/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rha-le <rha-le@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:59:27 by rha-le            #+#    #+#             */
/*   Updated: 2025/07/04 20:00:48 by rha-le           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include "parser.h"
#include "error.h"

int	builtin_exit(int argc, char **argv)
{
	char	*endptr;
	int		status;
	long	val;

	if (argc == 1)
	{
		printf("exit\n");
		exit(0);
	}
	else if (argc > 2)
		return (ERR_TOOMANY_ARGS);
	status = 0;
	val = strtol(argv[0], &endptr, 10); // TODO: CHANGE TO CUSTOM STRTOL
	if (*endptr == '\0' && val >= 0 && val <= 255)
		status = (int)val;
	else
		status = 2;
	// TODO: do cleanup
	rl_clear_history();
	printf("exit\n");
	exit(status);
}
