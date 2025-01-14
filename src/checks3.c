/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 12:31:51 by amsaleh           #+#    #+#             */
/*   Updated: 2025/01/10 00:38:40 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	check_env_sep(char c)
{
	if (c == ' ' || c == '*' || c == '$' || c == '?' || c == '"' || c == '\'')
		return (1);
	return (0);
}

int	check_str_wildcard(char *s, t_list *quotes_range)
{
	t_list	*lst;
	size_t	*range;
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '*')
		{
			if (!quotes_range)
				return (1);
			lst = quotes_range;
			while (lst)
			{
				range = ((t_qr *)lst->content)->arr;
				if (!(i >= range[0] && i <= range[1]))
					return (1);
				lst = lst->next;
			}
		}
		i++;
	}
	return (0);
}

int	check_if_builtin(char *token)
{
	if (!ft_strcmp(token, "exit"))
		return (1);
	if (!ft_strcmp(token, "cd"))
		return (1);
	if (!ft_strcmp(token, "export"))
		return (1);
	if (!ft_strcmp(token, "unset"))
		return (1);
	if (!ft_strcmp(token, "pwd"))
		return (1);
	if (!ft_strcmp(token, "env"))
		return (1);
	if (!ft_strcmp(token, "echo"))
		return (1);
	return (0);
}

int	check_expander_if_split(t_tok_expander *tok_exp)
{
	if (tok_exp->split_se.start == tok_exp->split_se.end
		&& tok_exp->mode != ENV_MODE)
		return (0);
	return (1);
}

int	check_env_end(char *s, t_tok_expander *tok_exp)
{
	if ((check_env_sep(s[tok_exp->split_se.end])) && check_env_mode(tok_exp))
		return (1);
	return (0);
}
