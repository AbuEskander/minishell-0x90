/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_prep_utils3.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abueskander <abueskander@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 11:50:44 by amsaleh           #+#    #+#             */
/*   Updated: 2024/12/30 15:12:09 by abueskander      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	set_redirection_data(t_redirect *redirect, t_list *lst)
{
	redirect->type = op_type_to_redirection(lst);
	redirect->name = ((t_token *)lst->next->content)->token_word;
}

int	op_prep_args(t_operation *operation, t_list *lst)
{
	ssize_t	parenthesis_count;
	size_t	n_args;

	parenthesis_count = 0;
	n_args = 0;
	while (check_op_prep_condition(lst, parenthesis_count))
	{
		if (((t_token *)lst->content)->type == OPEN_PARENTHESIS)
			parenthesis_count++;
		else if (((t_token *)lst->content)->type == CLOSE_PARENTHESIS)
			parenthesis_count--;
		if (((t_token *)lst->content)->type == ARGUMENT && !parenthesis_count)
			n_args++;
		lst = lst->next;
	}
	if (n_args)
		operation->args = ft_calloc(n_args + 2, sizeof(char *));
	if (n_args && !operation->args)
		return (0);
	if (operation->args)
		operation->args[0] = operation->cmd;
	return (1);
}

void	op_get_args(t_operation *operation, t_list *lst)
{
	ssize_t	parenthesis_count;
	size_t	i;

	parenthesis_count = 0;
	i = 1;
	while (check_op_prep_condition(lst, parenthesis_count))
	{
		if (((t_token *)lst->content)->type == OPEN_PARENTHESIS)
			parenthesis_count++;
		else if (((t_token *)lst->content)->type == CLOSE_PARENTHESIS)
			parenthesis_count--;
		if (((t_token *)lst->content)->type == ARGUMENT && !parenthesis_count)
		{
			operation->args[i] = ((t_token *)lst->content)->token_word;
			i++;
		}
		lst = lst->next;
	}
}