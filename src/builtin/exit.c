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

#include <stdio.h>
#include <readline/readline.h>
#include <stdlib.h>

#include "run.h"
#include "libft.h"

void	exit_(char **argv, t_data *data)
{
	unsigned char	status;

	status = 0;
	if (argv[1])
		status = (unsigned char)ft_strtol(argv[1], NULL, 10);
	rl_clear_history();
	cleanup_data(data);
	ft_lstclear(&data->env_history, free);
	free_args(data->envp);
	printf("exit\n");
	exit(status);
}
