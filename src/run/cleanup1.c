/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwobie <student@42>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 15:45:35 by rtwobie           #+#    #+#             */
/*   Updated: 2025/08/11 15:47:51 by rtwobie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#include "run.h"
#include "tokenizer.h"

void	free_token(t_token *token)
{
		free(token->value);
		free(token);
}

void	free_tokens(t_token **lst)
{
	t_token	*temp;

	while (*lst)
	{
		temp = *lst;
		*lst = temp->next;
		free_token(temp);
	}
	*lst = NULL;
}

void	close_fds(int fds[2])
{
	close(fds[0]);
	close(fds[1]);
}

void	cleanup_data(t_data *data)
{
	close(data->restorefd[0]);
	close(data->restorefd[1]);
	free_tokens(&data->tokens);
	cleanup_ast(&data->tree);
}
