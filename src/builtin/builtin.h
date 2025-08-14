/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgroo <student@42.eu>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:23:34 by rha-le            #+#    #+#             */
/*   Updated: 2025/08/14 16:23:52 by fgroo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

#include <stdlib.h>

int	builtin_exit(int argc, char **argv);
int	echo(char *argv[]);
int	is_builtin(char *program);
int	cd(char **av,char **v, ssize_t i);


// new_updating

int check_entries(char ***envp);
int	add_entry(char *type, char ***envp, size_t nb);
void	update_lst(char **envp, size_t i, size_t j);


#endif // !BUILTIN_H
