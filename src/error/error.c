/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rha-le <rha-le@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 17:46:01 by rha-le            #+#    #+#             */
/*   Updated: 2025/06/25 17:58:29 by rha-le           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

void	print_errror(char *err)
{
	if (err)
	{
		while (err)
			write(stderr, err++, 1);
		write(stderr, "\n", 1);
	}
	else
		write(stderr, "error\n", 7);
}
