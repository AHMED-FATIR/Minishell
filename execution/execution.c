/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatir <afatir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 10:58:45 by souledla          #+#    #+#             */
/*   Updated: 2023/08/09 08:46:43 by afatir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*located_path_return(char *envp[])
{
	int		i;
	char	*p;
	char	*located_path;

	p = "PATH=";
	i = 0;
	while (envp[i])
	{
		if (ft_newstrchr(envp[i], p))
			located_path = ft_newstrchr(envp[i], p);
		i++;
	}
	if (!located_path)
		exit(1);
	return (located_path);
}

char	*ft_newstrchr(char *s, char *target)
{
	int	i;
	int	len;
	int	j;

	len = ft_strlen(s);
	i = 0;
	j = 0;
	if (!s)
		exit(1);
	while (s[i])
	{
		if (s[i] == target[j])
			j++;
		else if (target[j] == '\0')
			return (s + i);
		i++;
	}
	return (NULL);
}

char	*ft_join(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*p;

	i = 0;
	j = 0;
	if (!s2)
		return (NULL);
	p = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!p)
		return (NULL);
	while (s1[i])
	{
		p[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		p[i + j] = s2[j];
		j++;
	}
	p[i + j] = 0;
	return (s1 = NULL, p);
}

char	*checking_path(char *comm, t_env **envs, int *flag, int i)
{
	char	*located_path;
	char	**str;
	t_env	*head;

	located_path = NULL;
	head = *envs;
	if (ft_newstrchr(comm, "./") || ft_strchr(comm, '/'))
	{
		*flag = 1;
		return (comm);
	}
	located_path = while_loop_checking_path(located_path, head);
	if (!located_path)
		return (NULL);
	str = ft_split(located_path, ':');
	i = 0;
	while (str[i])
	{
		str[i] = ft_join(str[i], ft_join("/", comm));
		if (access(str[i], F_OK) == 0)
			return (str[i]);
		free(str[i]);
		i++;
	}
	return (free(str), NULL);
}

char	*while_loop_checking_path(char *located_path, t_env *head)
{
	located_path = NULL;
	while (head && head->next)
	{
		if (ft_strlen(head->cmd) == ft_strlen("PATH")
			&& ! ft_strncmp(head->cmd, "PATH", ft_strlen("PATH")))
			located_path = head->str;
		head = head->next;
	}
	return (located_path);
}
