/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rha-le <rha-le@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:59:27 by rha-le            #+#    #+#             */
/*   Updated: 2025/07/04 17:24:06 by rha-le           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

void	builtin_exit(char **argv)
{
	char	*endptr;
	int		status;
	long	val;


	if (!argv[0])
	{
		printf("exit\n");
		exit(0);
	}
	status = 0;
	val = strtol(argv[0], &endptr, 10); // TODO: CHANGE TO CUSTOM STRTOL
	if (*endptr == '\0' && val >= 0 && val <= 255)
		status = (int)val;
	else
		status = 2;
	// TODO: do cleanup
	printf("exit\n");
	exit(status);
}
