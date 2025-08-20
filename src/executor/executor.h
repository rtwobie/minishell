/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgroo <student@42.eu>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 14:13:10 by fgroo             #+#    #+#             */
/*   Updated: 2025/08/20 17:58:39 by rtwobie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "parser.h"
# include "run.h"

int	executor(t_data *data, t_ast_node *tree, unsigned char *exit_status);

#endif // !EXECUTOR_H
