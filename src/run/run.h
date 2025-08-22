/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgroo <student@42.eu>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:38:42 by rtwobie           #+#    #+#             */
/*   Updated: 2025/08/18 23:47:44 by fgroo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RUN_H
# define RUN_H

# define PROMPT "minishell$ "

# include "parser.h"

typedef struct s_data
{
	char		**envp;
	t_token		*tokens;
	t_ast_node	*tree;
	int			restorefd[2];
	int			stdfd[2];
	t_list		*env_history;
}	t_data;

char	**cpy_envp(char	**envp);
int		run_minishell(char **envp);

//cleanup.c
void	free_redir(void *content);
void	free_args(char **args);
void	free_command_node(t_command_node *node);
void	free_token(t_token *token);
void	free_tokens(t_token **lst);
void	cleanup_ast(t_ast_node **ast);
void	cleanup_data(t_data *data);
void	close_fds(int fds[2]);

#endif // !RUN_H
