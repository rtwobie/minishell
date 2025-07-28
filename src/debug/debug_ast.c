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

void	print_command_node(t_command_node *cmd, int level)
{
	size_t	i;

	i = 0;
    print_indent(level);
	printf("%s[program] %s\n%s", CYAN, cmd->program_argv[0], END);
    print_indent(level);
	printf("%s[argv]\n%s", CYAN, END);
    print_indent(level);
	while (cmd->program_argv[i])
	{
		print_indent(level);
		printf("%s  %s\n%s", CYAN, cmd->program_argv[i], END);
		++i;
	}
}

void print_ast(t_ast_node *ast, int level) // Added 'level' parameter
{
    if (!ast) {
        return; // Important: handle NULL nodes gracefully
    }

    if (ast->type == NODE_TYPE_COMMAND) {
        if (ast->data.command_node && ast->data.command_node->program_argv) {
			print_command_node(ast->data.command_node, level);
        } else {
             printf("(Empty Command)\n");
        }
    } else if (ast->type == NODE_TYPE_PIPE) {
        print_indent(level);
        printf("[PIPE]\n");

        // Print left child with increased indentation
        print_indent(level);
        printf("├── LEFT:\n"); // A simple line to indicate left child
        print_ast(ast->data.pipe_node->left, level + 1); // Recurse with increased level

        // Print right child with increased indentation
        print_indent(level);
        printf("└── RIGHT:\n"); // A simple line to indicate right child
        print_ast(ast->data.pipe_node->right, level + 1); // Recurse with increased level
    }
    // Add more else if blocks for other node types as needed (e.g., REDIRECTION_NODE)
}
