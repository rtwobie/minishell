/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rha-le <rha-le@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 15:37:37 by rha-le            #+#    #+#             */
/*   Updated: 2025/07/23 16:51:22 by rha-le           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdio.h>
#include "debug.h"
#include "parser.h"

static void print_indent(int level) {
    for (int i = 0; i < level; i++) {
        // You can use printf("    ") or write(1, "    ", 4);
        printf("    "); // 4 spaces per level
    }
}

static void _print_redir_node(void *content)
{
	t_redirection_node	*data;

	data = (t_redirection_node *)content;
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
	printf("%s[program] %s\n%s", CYAN, cmd->program_argv[0], END);
    print_indent(level);
	printf("%s[argv]\n%s", CYAN, END);
	while (cmd->program_argv[i])
	{
		print_indent(level);
		printf("%s  %s\n%s", CYAN, cmd->program_argv[i], END);
		++i;
	}
	print_indent(level);
	_print_redir(&cmd->redir, level);
}

void print_ast(t_ast_node *ast, int level) // Added 'level' parameter
{
    if (!ast)
        return;
    if (ast->type == NODE_TYPE_COMMAND)
	{
        if (ast->data.command && ast->data.command->program_argv)
			print_command_node(ast->data.command, level);
        else
             printf("(Empty Command)\n");
    } else if (ast->type == NODE_TYPE_PIPE) {
        print_indent(level);
        printf("[PIPE]\n");

        // Print left child with increased indentation
        print_indent(level);
        printf("├── LEFT:\n"); // A simple line to indicate left child
        print_ast(ast->data.pipe->left, level + 1); // Recurse with increased level

        // Print right child with increased indentation
        print_indent(level);
        printf("└── RIGHT:\n"); // A simple line to indicate right child
        print_ast(ast->data.pipe->right, level + 1); // Recurse with increased level
    }
    // Add more else if blocks for other node types as needed (e.g., REDIRECTION_NODE)
}
