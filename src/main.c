/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 14:38:12 by amsaleh           #+#    #+#             */
/*   Updated: 2024/12/01 19:29:58 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	parse_line(t_minishell *minishell)
{
	execute_inbuilt_command(minishell);
	add_history(minishell->line_read);
	free(minishell->line_read);
}

static t_minishell	*minishell_prep(void)
{
	t_minishell	*minishell;
	extern char	**environ;

	minishell = ft_calloc(1, sizeof(t_minishell));
	if (!minishell)
		exit_handler(minishell, ERR_MALLOC);
	minishell->cwd = malloc(PATH_MAX + 1);
	if (!minishell->cwd)
		exit_handler(minishell, ERR_MALLOC2);
	if (*environ)
		prep_minishell_env(minishell, environ);
	return (minishell);
}

static void	start_shell(t_minishell *mini)
{
	while (1)
	{
		mini->line_read = readline("\e[33mminishell 0x90\e[0m> ");
		if (!mini->line_read)
			exit_handler(mini, NONE);
		if (*mini->line_read)
			parse_line(mini);
	}
}

int	main(void)
{
	t_minishell	*minishell;

	minishell = minishell_prep();
	signal_handler();
	if (terminals_config())
		exit_handler(minishell, EXIT_FAILURE);
	start_shell(minishell);
}
