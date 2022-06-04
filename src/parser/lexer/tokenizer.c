/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 16:14:05 by mazhari           #+#    #+#             */
/*   Updated: 2022/06/04 21:46:11 by mazhari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*is_wspace(t_list *list, char *line)
{
	while (*line && ft_strchr(" \t", *line))
		line++;
	push_back(list, WSPACE, " ");
	return (line);
}

static char	*is_sing(t_list *list, char *line)
{
	line++;
	if (*line == '?')
	{
		push_back(list, EXIT_STATUS, "$?");
		line++;
	}
	else if (*line == '{' && ft_strchr(line + 1, '}'))
	{
		push_back(list, SIGN, "$");
		line = is_word(list, line + 1, "}");
		line++;
	}
	else
	{
		push_back(list, SIGN, "$");
		line = is_word(list, line, " \t!\"$%'()*+,-./:;<=>?@[\\]^`{|}~");
	}
	return (line);
}

static char	*is_dquote(t_list *list, char *line)
{
	line = is_word(list, line + 1, "\"$~");
	if (*line == '$')
	{	
		line = is_sing(list, line);
		if (*line != '"')
			line =  is_word(list, line, "\"");
	}
	else if (*line == '~')
	{
		push_back(list, SIGN, "$");
		push_back(list, WORD, "HOME");
		line++;
	}
	return (line);	
}

static char	*is_quote(t_list *list, char *line)
{
	if (*line == '"')
	{
		if (ft_strchr(line + 1, '"'))
			line = is_dquote(list, line);
		else
			printf("minishell: unclosed double quotes\n");
	}
	else
	{	
		if (ft_strchr(line + 1, '\''))
			line = is_word(list, line + 1, "'");
		else
			printf("minishell: unclosed singel quotes\n");
	}
	line++;
	return (line);
}

t_list	*tokenizer(char *line)
{
	t_list	*list;

	list = new_list();
	while (*line)
	{
		if (ft_strchr(" \t", *line))
			line = is_wspace(list, line);
		else if (*line == '\'' || *line == '"')
			line = is_quote(list, line);
		else if (*line == '$')
			line = is_sing(list, line);
		else if (ft_strchr("|<>", *line))
		 	line = is_metacharacters(list, line);
		else if (*line == '~')
		{
			push_back(list, SIGN, "$");
			push_back(list, WORD, "HOME");
			line++;
		}
		else
			line = is_word(list, line, " \t\v\f\r\"'$|<>");
	}
	return (list);
}