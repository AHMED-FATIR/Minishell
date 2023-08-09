/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatir <afatir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 10:33:51 by afatir            #+#    #+#             */
/*   Updated: 2023/08/09 08:42:06 by afatir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_expande(char *cmd, int i, t_env **env, t_var *v)
{
	int		b;

	b = ++i;
	while ((cmd[i] && cmd[i] != '$' && not_sep(cmd[i])) && \
		((ft_isalnum(cmd[i]) || cmd[i] == '_') || cmd[i] == '?'))
	{
		if (cmd[i] == '?' && cmd[i - 1] == '$')
		{
			i++;
			break ;
		}
		i++;
	}
	v->str = ft_strndup(cmd, b, i--);
	v->str = get_env_str(v->str, env);
	if (v->str)
		v->c = dupping(v->c, v->str);
	return (i);
}

int	sep_case_double(char *cmd, int i, t_var *v, t_env **env)
{
	v->b = i;
	while (i <= v->j && cmd[i])
	{
		if (cmd[i] == '$' && ft_isdigit(cmd[i + 1]))
			i += 2;
		if (cmd[i] == '$' && cmd[i + 1] == '$')
			v->c = ft_strjoin_p(v->c, cmd[i++]);
		else if (cmd[i] == '$' && cmd[i + 1] && \
			(ft_isalnum(cmd[i + 1]) || cmd[i + 1] == '_' || cmd[i + 1] == '?'))
			i = get_expande(cmd, i, env, v);
		else
		{
			v->c = ft_strjoin_p(v->c, cmd[i]);
			v->b = i;
		}
		i++;
	}
	i--;
	return (i);
}

int	sep_case(char *cmd, int i, t_var *v, t_env **env)
{
	v->j = get_index(i, cmd);
	if (cmd[v->j] == '\"')
		i = sep_case_double(cmd, i, v, env);
	else
	{
		v->f = ft_strndup(cmd, i, v->j + 1);
		v->c = dupping(v->c, v->f);
		i = v->j;
	}
	return (i);
}

int	else_case_to(char *cmd, int i, t_var *v, t_env **env)
{
	if (cmd[i + 1] && cmd[i] == '$' && \
		((ft_isalpha(cmd[i + 1]) || cmd[i + 1] == '_') || cmd[i + 1] == '?'))
	{
		v->f = ft_strndup(cmd, v->b, i);
		v->c = dupping(v->c, v->f);
		i = get_expande(cmd, i, env, v);
	}
	else if (cmd[i] == '$' && is_sep(cmd[i + 1], 2))
		return (i);
	else
		v->c = ft_strjoin_p(v->c, cmd[i]);
	return (i);
}

int	else_case(char *cmd, int i, t_var *v, t_env **env)
{
	while (cmd[i] && !is_sep(cmd[i], 2))
	{
		v->b = i;
		if (cmd[i] == '$' && is_special(cmd[i + 1]))
			v->c = dupping(v->c, get_special(cmd[++i]));
		else if (cmd[i] == '$' && ft_isdigit(cmd[i + 1]))
			i++;
		else
			i = else_case_to(cmd, i, v, env);
		i++;
	}
	i--;
	return (i);
}
