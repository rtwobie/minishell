/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rha-le <rha-le@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:38:42 by rha-le            #+#    #+#             */
/*   Updated: 2025/06/23 18:03:47 by rha-le           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RUN_H
# define RUN_H

# define PROMPT "minishell$ "

# include "parser.h"

typedef struct s_data
{
	t_token		*tokens;
	t_ast_node	*tree;
	int			restorefd[2];
	int			stdfd[2];
}	t_data;

int	run_minishell(char **envp);

//cleanup.c
void	free_redir(void *content);
void	free_args(char **args);
void	free_command_node(t_command_node *node);
void	cleanup_ast(t_ast_node **ast);
void	cleanup_data(t_data *data);

#endif // !RUN_H
