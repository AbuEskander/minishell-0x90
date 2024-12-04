/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_tokenizer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 15:29:59 by amsaleh           #+#    #+#             */
/*   Updated: 2024/12/04 19:13:07 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	check_sep(char *line)
{
	if (!ft_strncmp(line, "&&", 2))
		return (2);
	if (!ft_strncmp(line, "||", 2))
		return (2);
	if (!ft_strncmp(line, "<<", 2))
		return (2);
	if (!ft_strncmp(line, ">>", 2))
		return (2);
	if (!ft_strncmp(line, "<>", 2))
		return (2);
	if (*line == '|' || *line == '(' || *line == ')')
		return (1);
	if (*line == '<' || *line == '>')
		return (1);
	return (0);
}

size_t	skip_spaces(char *line)
{
	size_t	i;

	i = 0;
	while (*(line + i) == ' ')
		i++;
	return (i);
}

void	line_tokenizer(t_minishell *mini)
{
	t_tokens_split	tokens_split;
	char			*line;

	ft_bzero(&tokens_split, sizeof(t_tokens_split));
	line = mini->line_read;
	while (line[tokens_split.end])
	{
		tokens_split.start += skip_spaces(line + tokens_split.start);
		tokens_split.end = tokens_split.start;
		while (check_sep(line + tokens_split.end))
			add_sep_tokens(mini, &tokens_split, line);
		tokens_split.start += skip_spaces(line + tokens_split.start);
		tokens_split.end = tokens_split.start;
		if (line[tokens_split.end] && !check_sep(line + tokens_split.end))
			add_token(mini, &tokens_split);
	}
	while (mini->line_tokens)
	{
		ft_printf("%s\n", mini->line_tokens->content);
		mini->line_tokens = mini->line_tokens->next;
	}
}
