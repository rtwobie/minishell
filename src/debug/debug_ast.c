/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwobie <student@42>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 15:37:37 by rtwobie           #+#    #+#             */
/*   Updated: 2025/08/26 16:48:37 by rtwobie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdio.h>
#include "debug.h"
#include "parser.h"

static void	print_indent(int level)
{
	int	i;

	i = 0;
	while (i < level)
	{
		printf("    ");
		++i;
	}
}

static void	_print_redir_node(void *content)
{
	t_redir_node	*data;

	data = (t_redir_node *)content;
	printf("  %s, %s\n", token_type_to_string(data->type), data->filename);
}

static void	_print_redir(t_list **lst, int level)
{
	t_list	*current;

	current = *lst;
	printf("%s[redirects]\n", GREEN);
	if (!current)
	{
		print_indent(level);
		printf("  (null)\n");
		printf("%s\n", END);
		return ;
	}
	while (current)
	{
		print_indent(level);
		_print_redir_node(current->content);
		current = current->next;
	}
	printf("%s\n", END);
}

void	print_command_node(t_command_node *cmd, int level)
{
	size_t	i;

	i = 0;
	print_indent(level);
	printf("%s[program] %s\n%s", CYAN, cmd->argv[0], END);
	print_indent(level);
	printf("%s[argv]\n%s", CYAN, END);
	while (cmd->argv[i])
	{
		print_indent(level);
		printf("%s  %s\n%s", CYAN, cmd->argv[i], END);
		++i;
	}
	print_indent(level);
	_print_redir(&cmd->redir, level);
}

void	print_ast(t_ast_node *ast, int level)
{
	if (!ast)
		return ;
	if (ast->type == NODE_TYPE_COMMAND)
	{
		if (ast->data.command && ast->data.command->argv)
			print_command_node(ast->data.command, level);
		else
			printf("(Empty Command)\n");
	}
	else if (ast->type == NODE_TYPE_PIPE)
	{
		print_indent(level);
		printf("[PIPE]\n");
		print_indent(level);
		printf("├── LEFT:\n");
		print_ast(ast->data.pipe->left, level + 1);
		print_indent(level);
		printf("└── RIGHT:\n");
		print_ast(ast->data.pipe->right, level + 1);
	}
}
