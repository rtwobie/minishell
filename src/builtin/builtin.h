/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgroo <student@42.eu>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:23:34 by rtwobie           #+#    #+#             */
/*   Updated: 2025/08/26 13:56:49 by fgroo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include <stdlib.h>
# include "run.h"

int		exit_(char **argv, t_data *data);
int		echo(char *argv[]);
int		is_builtin(char *program);
int		cd(char **av, t_data *data, ssize_t i);

// new_updating
int		check_entries(t_data *data);
int		add_entry(char *type, t_data *data, size_t nb, int flag);
void	update_lst(t_data *data, size_t i, size_t j);

// export

int		delete_entry(char *type, t_data *data, int *flag);
int		_unset(const char *target, size_t tlen, t_data *data, int *flag);
int		_export(char **av, t_data *data, int exit_status);

#endif // !BUILTIN_H
