/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgroo <student@42.de>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:23:34 by rha-le            #+#    #+#             */
/*   Updated: 2025/08/07 23:30:44 by fgroo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include <stdio.h>

# include "run.h"

int		echo(char *argv[]);
int		is_builtin(char *program);
int		cd(char **av,char **v, ssize_t i);
void	exit_(char **argv, t_data *data);

#endif // !BUILTIN_H
