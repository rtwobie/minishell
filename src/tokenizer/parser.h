/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rha-le <rha-le@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 18:33:35 by rha-le            #+#    #+#             */
/*   Updated: 2025/07/04 17:02:05 by rha-le           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

enum e_output
{
	STD_OUT,
	PIPE_OUT,
	FILE_OUT,
	FILE_APPEND_OUT,
};

typedef struct s_command
{
	char			*program;
	char			**argv;
	int				argc;
	enum e_output	output;
}	t_command;

void	free_args(char **args);
void	free_cmd(void *command_struct);

#endif // !PARSER_H
