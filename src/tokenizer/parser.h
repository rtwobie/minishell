/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rha-le <rha-le@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 18:33:35 by rha-le            #+#    #+#             */
/*   Updated: 2025/07/02 16:19:50 by rha-le           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "structs.h"

typedef struct s_command
{
	char	*program;
	char	**args;
	enum	e_token_type output;
}	t_command;

void	free_args(char **args);
void	free_cmd(void *command_struct);

#endif // !PARSER_H
