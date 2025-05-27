/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rha-le <rha-le@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:39:23 by rha-le            #+#    #+#             */
/*   Updated: 2025/05/27 16:00:25 by rha-le           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "run.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

int	run_minishell(void)
{
	char *rl;

	while (1)
	{
		rl = readline(PROMPT);
		add_history(rl);
		printf("%s\n", rl);
		free(rl);
	}
}
