/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgorlich <fgorlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 17:09:07 by rtwobie           #+#    #+#             */
/*   Updated: 2025/09/10 18:10:45 by fgorlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H

# include "tokenizer.h"

# define HDOCDIR "./minihdoc_"

int	heredoc(t_token **tokens, unsigned char *exit_status, char **envp);
int	cleanup_hdoc(t_token **tokens);
int	hdoc_envvar(char **input, unsigned int skip, unsigned char *exit_status,
		char **envp);

#endif // !HEREDOC_H
