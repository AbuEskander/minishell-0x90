/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inbuilt_cmds_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 23:01:58 by amsaleh           #+#    #+#             */
/*   Updated: 2024/11/23 23:03:49 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	compare_cmd_name(char *arg1, char *cmd_name)
{
	if (ft_strlen(arg1) == ft_strlen(cmd_name))
		if (!ft_strncmp(arg1, cmd_name, ft_strlen(cmd_name)))
			return (1);
	return (0);
}