/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rha-le <rha-le@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 15:32:20 by rha-le            #+#    #+#             */
/*   Updated: 2025/06/23 20:45:43 by rha-le           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "run.h"
#include "lexer.h"


#include <readline/readline.h>
int main(void)
{
	// run_minishell();
	char *input;
	input = readline("lexer test: ");
	printf("%i\n", lexer(input));
}
