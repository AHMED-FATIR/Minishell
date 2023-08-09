/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_function.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatir <afatir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 21:06:29 by souledla          #+#    #+#             */
/*   Updated: 2023/08/09 08:54:45 by afatir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	pwd(int outfile, char **generated_old_pwd)
{
	char	old_pwd[1024];

	if (getcwd(old_pwd, sizeof(old_pwd)) == NULL)
	{
		g_exit_status = 1;
		write(2, "error\n", 6);
	}
	*generated_old_pwd = ft_strdup(old_pwd);
	write(outfile, old_pwd, ft_strlen(old_pwd));
	write(outfile, "\n", 1);
}
