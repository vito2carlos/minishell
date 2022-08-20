/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:32:25 by mazhari           #+#    #+#             */
/*   Updated: 2022/08/20 16:55:29 by mazhari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_status(void)
{
	if (g_data.status == 3)
	{
		ft_putstr_fd("Quit: 3\n", 2);
		g_data.status = 131;
	}
	else if (g_data.status == 2)
	{
		write(2, "\n", 1);
		g_data.status = 130;
	}
	else if (g_data.status == 126 || g_data.status == 127)
		return ;
	else
		g_data.status = WEXITSTATUS(g_data.status);
}

static int	is_list(t_list *list)
{
	t_node	*tmp;

	if (!list)
		return (0);
	tmp = list->head;
	while (tmp)
	{
		if (tmp->val[0] == 0)
			tmp = tmp->next;
		else
			return (1);
	}
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_list	*list;
	t_cmd	*cmd;
	char	*line;

	(void)ac;
	(void)av;
	g_data.status = 0;
	init_envv(env);
	while (1)
	{
		line = prompt();
		if (!line)
			continue ;
		list = lexer(line);
		if (is_list(list))
		{
			cmd = paser(list, new_cmd());
			clear_list(list);
			execute(cmd);
			free_cmd(cmd);
		}
		free(line);
	}
	ft_freearr(g_data.env);
	return (0);
}
