/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 19:56:08 by abueskander       #+#    #+#             */
/*   Updated: 2024/12/26 09:29:50 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	clear_env(void *content)
{
	t_env	*env;

	env = (t_env *)content;
	free(env->data);
	free(env->name);
	free(env);
}

void	clear_token(void *content)
{
	t_token	*token;

	token = (t_token *)content;
	free(token->token_word);
	free(token);
}

void	free_lst(t_list *lst)
{
	t_list	*temp;

	while (lst)
	{
		temp = lst->next;
		free(lst);
		lst = temp;
	}
}

void	free_tokens(void *tokens)
{
	if (((t_token *)tokens)->token_word)
		free(((t_token *)tokens)->token_word);
	free(tokens);
}

void	exit_handler(t_minishell *mini, int error)
{
	print_error(error);
	if (error > ERR_MALLOC_MINI)
	{
		rl_clear_history();
		free(mini->cwd);
		free(mini->line_read);
		ft_lstclear(&mini->env_lst, clear_env);
		if (error >= ERR_MALLOC_POSTLEXER)
			ft_lstclear(&mini->line_tokens, free_tokens);
		else
			ft_lstclear(&mini->line_tokens, free);
		free(mini);
	}
	if (error != NONE)
		exit(EXIT_FAILURE);
	exit(EXIT_SUCCESS);
}
