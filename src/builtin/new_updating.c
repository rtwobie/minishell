#include "error.h"
#include "libft.h"
#include "builtin.h"
#include <asm-generic/errno-base.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdbool.h>


void	update_lst(char **envp, size_t i, size_t j)
{
	char			cwd[1024];
	t_list			*lst;

	if (!getcwd(cwd, sizeof(cwd)))
		return ;
	lst = NULL;
	ft_lstadd_back(&lst, ft_lstnew(envp[i]));
	envp[i] = ft_strjoin("OLD", envp[j]);
	envp[j] = ft_strjoin("PWD=", cwd);
}

int	add_entry(char *type, char ***envp, size_t nb)
{
	char		*join;
	char		**newenvp;
	char		cwd[1024];
	char		*entry;

	join = ft_strjoin(type, "=");
	if (!join)
		return (EXIT_FAILURE);
	if (!getcwd(cwd, sizeof(cwd)))
		return (perror("getcwd"), EXIT_FAILURE);
	entry = ft_strjoin(join, cwd);
	if (!entry)
		return (EXIT_FAILURE);
	newenvp = malloc(sizeof(char *) * (nb + 2));
	if (!newenvp)
		return (EXIT_FAILURE);
	newenvp[nb] = entry;
	newenvp[nb + 1] = NULL;
	while (nb--)
		newenvp[nb] = (*envp)[nb];
	*envp = newenvp;
	return (EXIT_SUCCESS);
}

int	check_entries(char ***envp)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while ((*envp)[i] && ft_strncmp((*envp)[i], "OLDPWD=", 7))
		++i;
	if (!(*envp)[i] && add_entry("OLDPWD", envp, i) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	while ((*envp)[j] && ft_strncmp((*envp)[j], "PWD=", 4))
		++j;
	if (!(*envp)[j] && add_entry("PWD", envp, j) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	update_lst((*envp), i, j);
	return (EXIT_SUCCESS);
}
