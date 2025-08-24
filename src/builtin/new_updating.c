/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_updating.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 21:25:50 by fgroo             #+#    #+#             */
/*   Updated: 2025/08/24 14:57:58 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "error.h"
#include "libft.h"
#include <asm-generic/errno-base.h>
#include <errno.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	update_lst(t_data *data, size_t i, size_t j)
{
	char	cwd[1024];
	char	*old_envp_i;
	char	*old_envp_j;

	if (!getcwd(cwd, sizeof(cwd)))
		return ;
	ft_lstadd_back(&data->env_history, ft_lstnew(ft_strdup(data->envp[i])));
	old_envp_i = data->envp[i];
	old_envp_j = data->envp[j];
	data->envp[i] = ft_strjoin("OLD", data->envp[j]);
	data->envp[j] = ft_strjoin("PWD=", cwd);
	if (old_envp_i)
		free(old_envp_i);
	if (old_envp_j)
		free(old_envp_j);
}

int	add_entry(char *type, t_data *data, size_t nb, int flag)
{
	char	*join;
	char	**newenvp;
	char	**old_envp;
	char	cwd[1024];
	char	*entry;

	join = ft_strjoin(type, "=");
	if (!join)
		return (EXIT_FAILURE);
	if (!flag && !getcwd(cwd, sizeof(cwd)))
		return (free(join), perror("getcwd"), EXIT_FAILURE);
	else if (flag && (free(join), 1) && ft_memset(cwd, 0, sizeof(cwd)))
		join = ft_substr(type, 0, ft_strlen(type));
	entry = ft_strjoin(join, cwd);
	if (free(join), 1 && !entry)
		return (EXIT_FAILURE);
	newenvp = malloc(sizeof(char *) * (nb + 2));
	if (!newenvp)
		return (free(entry), EXIT_FAILURE);
	newenvp[nb] = entry;
	newenvp[nb + 1] = NULL;
	while (nb--)
		newenvp[nb] = data->envp[nb];
	old_envp = data->envp;
	return (data->envp = newenvp, free(old_envp), EXIT_SUCCESS);
}

int	check_entries(t_data *data)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (data->envp[i] && ft_strncmp(data->envp[i], "OLDPWD=", 7))
		++i;
	if (!data->envp[i] && add_entry("OLDPWD", data, i, 0) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	j = 0;
	while (data->envp[j] && ft_strncmp(data->envp[j], "PWD=", 4))
		++j;
	if (!data->envp[j] && add_entry("PWD", data, j, 0) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	i = 0;
	while (data->envp[i] && ft_strncmp(data->envp[i], "OLDPWD=", 7))
		++i;
	j = 0;
	while (data->envp[j] && ft_strncmp(data->envp[j], "PWD=", 4))
		++j;
	update_lst(data, i, j);
	return (EXIT_SUCCESS);
}
