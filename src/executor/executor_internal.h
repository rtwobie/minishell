/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_internal.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwobie <student@42>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 21:54:52 by rtwobie           #+#    #+#             */
/*   Updated: 2025/08/22 13:19:34 by rtwobie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_INTERNAL_H
# define EXECUTOR_INTERNAL_H

# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>

# include "parser.h"
# include "run.h"

// redirect.c
int				redirect_io(t_command_node *cmd, int input_fd, int output_fd);

// search_program.c
int				search_program(char *lookup, char **program);

// executor1.c
unsigned char	_exec_builtin(t_data *data, t_command_node *cmd);
int				_restore_stdfd(int restorefd[2]);

#endif // !EXECUTOR_INTERNAL_H
