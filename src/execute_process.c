/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 21:10:52 by amsaleh           #+#    #+#             */
/*   Updated: 2025/01/01 01:47:09 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	prep_redirections_helper2(t_operation *operation, char *line)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_strjoin(operation->heredoc_buffer, line);
	if (!tmp)
		return (0);
	free(operation->heredoc_buffer);
	operation->heredoc_buffer = tmp;
	tmp2 = ft_strjoin(operation->heredoc_buffer, "\n");
	if (!tmp2)
		return (0);
	free(operation->heredoc_buffer);
	operation->heredoc_buffer = tmp2;
	return (1);
}

int	prep_redirections_helper(t_minishell *mini, t_operation *operation, size_t j)
{
	char *line;

	while (1)
	{
		line = readline("> ");
		if (j == operation->n_in - 1 && !operation->heredoc_buffer)
		{
			operation->heredoc_buffer = ft_strdup("");
			if (!operation->heredoc_buffer)
				return (0);
		}
		if (line && !ft_strcmp(line, operation->in_redirects[j].name))
			break;
		if (line && j == operation->n_in - 1)
			if (!prep_redirections_helper2(operation, line))
				return (0);
		if (!line)
		{
			print_heredoc_warning(mini, operation, j);
			break ;
		}
		free(line);
	}
	return (1);
}

int	prep_redirections(t_minishell *mini, t_operation **operations)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (operations[i])
	{
		j = 0;
		if (operations[i]->operations)
			if (!prep_redirections(mini, operations[i]->operations))
				return (0);
		while (j < operations[i]->n_in)
		{
			if (operations[i]->in_redirects[j].type == REDIRECT_LIMITER)
				if (!prep_redirections_helper(mini, operations[i], j))
					return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	pre_execute_external_cmd(t_minishell *mini, t_operation *operation)
{
	char	*cmd_path;

	if (ft_strchr(operation->cmd, '/'))
		cmd_path = ft_strdup(operation->cmd);
	else
		cmd_path = get_exec_path(mini, operation->cmd);
	if (!cmd_path)
		return (-1);
	if (!*cmd_path)
	{
		perror(operation->cmd);
		free(cmd_path);
		mini->last_exit_code = 127;
		return (0);
	}
	if (access(cmd_path, X_OK))
	{
		perror(operation->cmd);
		free(cmd_path);
		mini->last_exit_code = 126;
		return (0);
	}
	operation->cmd_path = cmd_path;
	return (1);
}

int	execute_cmd(t_minishell *mini, t_operation *operation)
{
	int		pid;

	operation->env = env_lst_to_2d_arr(mini);
	if (!operation->env)
		return (EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		return (EXIT_FAILURE);
	if (!pid)
	{
		execve(operation->cmd_path, operation->args, operation->env);
		return (EXIT_SUCCESS);
	}
	wait(0);
	return (EXIT_SUCCESS);
}

int	execute_process(t_minishell *mini)
{
	size_t	i;
	int		status;

	if (!prep_redirections(mini, mini->operations))
		return (EXIT_FAILURE);
	i = 0;
	while (mini->operations[i])
	{
		if (mini->operations[i]->cmd)
		{
			status = pre_execute_external_cmd(mini, mini->operations[i]);
			if (status == -1)
				return (EXIT_FAILURE);
			if (status)
				execute_cmd(mini, mini->operations[i]);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
