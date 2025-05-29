/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rha-le <rha-le@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 20:32:09 by rha-le            #+#    #+#             */
/*   Updated: 2025/05/29 21:52:17 by rha-le           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "structs.h"
#include <stdlib.h>

/** Creates a node/token with the specified type and value.
 *
 *	@param type: 	The type of token. (see: --> structs.h)
 *	@param value:	The value of the token as a string.
 *
 *	@returns:		A pointer to a token.
 */
t_token	*create_token(enum e_token_type type, char *value)
{
	t_token *token;

	token = malloc(sizeof(*token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = value;
	token->right = NULL;
	token->left = NULL;
	return (token);
}

/** Creates a child node/token to the left of the parent with the given values.
 *
 *	@param root: 	The parent node.
 *	@param type: 	The type of token. (see: --> structs.h)
 *	@param value:	The value of the token as a string.
 *
 *	@returns:		A pointer to a the left of the parent node.
 */
t_token *insert_token_left(t_token *root, enum e_token_type type, char *value)
{
	root->left = create_token(type, value);
	return (root->left);
}

/** Creates a child node/token to the right of the parent with the given values.
 *
 *	@param root: 	The parent node.
 *	@param type: 	The type of token. (see: --> structs.h)
 *	@param value:	The value of the token as a string.
 *
 *	@returns:		A pointer to a the right of the parent node.
 */
t_token *insert_token_right(t_token *root, enum e_token_type type, char *value)
{
	root->right = create_token(type, value);
	return (root->right);
}

void	free_token_tree(t_token *root)
{
	if (root == NULL)
		return ;
	free_token_tree(root->left);
	free_token_tree(root->right);
	free(root);
	root = NULL;
}

void	in_order_traversal(t_token *root)
{
	if (root == NULL)
		return ;
	in_order_traversal(root->left);
	printf(
		"type = %s\tvalue = %s\n", \
		token_type_to_string(root->type), \
		root->value \
	);
	in_order_traversal(root->right);
}
