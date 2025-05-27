/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmagrin <mmagrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 18:34:23 by mmagrin           #+#    #+#             */
/*   Updated: 2025/05/27 17:01:49 by mmagrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exe.h"

t_env	*ft_create_node(void *content)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->key = ft_extract_key(content);
	new_node->value = ft_extract_value(content);
	new_node->next = NULL;
	return (new_node);
}

t_env	**ft_init_env(char *envp[])
{
	int		i;
	t_env	**env;
	t_env	*new;

	env = malloc(sizeof(t_env *));
	if (!env)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		new = ft_create_node(envp[i]);
		if (!new)
			return (NULL);
		ft_env_add_back(env, new);
		i++;
	}
	return (env);
}
