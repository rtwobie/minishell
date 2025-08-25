/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgroo <student@42.eu>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:59:27 by rha-le            #+#    #+#             */
/*   Updated: 2025/08/18 21:29:48 by fgroo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdio.h>
#include <readline/readline.h>
#include <stdlib.h>

#include "error.h"
#include "run.h"
#include "libft.h"

int	exit_(char **argv, t_data *data)
{
	char			*endptr;
	unsigned char	status;

	status = 0;
	printf("exit\n");
	if (argv[1] && argv[2])
	{
		print_err(ERR_TOOMANY_ARGS, "exit");
		return (EXIT_FAILURE);
	}
	if (argv[1])
		status = (unsigned char)ft_strtol(argv[1], &endptr, 10);
	if (errno == ERANGE || (*endptr != '\0' && argv[1]))
	{
		print_err(ERR_NUM_ARG_REQUIRED, "exit");
		status = 2;
	}
	rl_clear_history();
	cleanup_data(data);
	ft_lstclear(&data->env_history, free);
	free_args(data->envp);
	exit(status);
}
