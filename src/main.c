/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwobie <student@42>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 15:32:20 by rtwobie           #+#    #+#             */
/*   Updated: 2025/08/18 20:23:16 by fgroo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "run.h"

int main(int argc, char *argv[], char *envp[])
{
	(void)argc;
	(void)argv;
	if (run_minishell(envp))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
