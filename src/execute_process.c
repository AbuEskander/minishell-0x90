/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abueskander <abueskander@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 21:10:52 by amsaleh           #+#    #+#             */
/*   Updated: 2024/12/30 15:10:09 by abueskander      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>


int	execute_process(t_minishell *mini)
{
	//char *path;
	if(check_if_batata_path(mini->operations[0]->cmd))
	{
		if (check_if_cmd_exist(mini->operations[0]->cmd))
		{
			int pid = fork();
			if (!pid)
				execve(mini->operations[0]->cmd, mini->operations[0]->args, 0);
			wait(0);
			return (1);
		}
		perror(mini->operations[0]->cmd);
		return (0);
	}
	// }else
	// {
	// 	path = search_for_path(mini->operations[0]->cmd);
	// }
	return (EXIT_SUCCESS);
}
