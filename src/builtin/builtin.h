/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgroo <student@42.eu>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:23:34 by rha-le            #+#    #+#             */
/*   Updated: 2025/08/20 17:07:59 by fgroo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

#include <stdlib.h>
#include "run.h"

void	exit_(char **argv, t_data *data);
int	echo(char *argv[]);
int	is_builtin(char *program);
int	cd(char **av, t_data *data, ssize_t i);


// new_updating

int check_entries(t_data *data);
int	add_entry(char *type, t_data *data, size_t nb, int flag);
void	update_lst(t_data *data, size_t i, size_t j);

// export

int	_export(char **av, t_data *data);


#endif // !BUILTIN_H
