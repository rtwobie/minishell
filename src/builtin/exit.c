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

#include <stdio.h>
#include <readline/readline.h>
#include <stdlib.h>

#include "run.h"

void	exit_(char **argv, t_data *data)
{
	unsigned char	status;

	status = 0;
	(void)argv;
	cleanup_data(data);
	rl_clear_history();
	printf("exit\n");
	exit(status);
}
