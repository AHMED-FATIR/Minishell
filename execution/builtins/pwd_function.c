/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_function.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatir <afatir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 21:06:29 by souledla          #+#    #+#             */
/*   Updated: 2023/10/19 11:26:48 by afatir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	pwd(int outfile, char **generated_old_pwd)
{
	char	old_pw[1024];

	if (getcwd(old_pw, sizeof(old_pw)) == NULL)
	{
		g_exit_status = 1;
		write(2, "error\n", 6);
	}
	*generated_old_pwd = ft_strdup(old_pw);
	write(outfile, old_pw, ft_strlen(old_pw));
	write(outfile, "\n", 1);
}
