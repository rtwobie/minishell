/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rha-le <rha-le@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:23:34 by rha-le            #+#    #+#             */
/*   Updated: 2025/08/06 19:04:25 by rha-le           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

int	builtin_exit(int argc, char **argv);
int	echo(char *argv[]);
int	is_builtin(char *program);

#endif // !BUILTIN_H
