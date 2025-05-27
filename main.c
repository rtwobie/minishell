/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmagrin <mmagrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 15:32:20 by rha-le            #+#    #+#             */
/*   Updated: 2025/05/27 17:09:05 by mmagrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "run.h"
#include "minishell_exe.h"

void	ft_print_env_list(t_env *env)
{
	while (env)
	{
		if (env->key && env->value)
			printf("%s=%s\n", env->key, env->value);
		else if (env->key)
			printf("%s=\n", env->key);
		env = env->next;
	}
}

int main(int argc, char *argv[], char *envp[])
{
	t_env	**env;

	if (argc < 0)
		return 1;
	if (argv[0][0] == 'a')
		return 1;
	env = ft_init_env(envp);
	ft_print_env_list(*env);
	return (0);
}
