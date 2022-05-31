/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 17:34:07 by mazhari           #+#    #+#             */
/*   Updated: 2022/05/25 15:26:43 by mazhari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "../libft/libft.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <termios.h>

# define WSPACE -1 // ' '
# define PIPE -2 // |
# define REDIN -3 // <
# define REDOUT -4 // >
# define APPEND -5// >>
# define HEREDOC -6 // <<
# define SQUOTES -7// '
# define DQUOTES -8// "
# define SIGN -9 // $
# define EXIT_STATUS -10 // $?
# define WORD -11 // 	

// typedef struct s_cmd
// {
//	char	*command;
// 	char	*program;
// 	char	**path;
// }				t_cmd;
typedef struct	s_node
{
	int				type;
	char			*val;
	struct s_node	*prev;
	struct s_node	*next;
}				t_node;

typedef struct	s_list
{
	int		n; // number of node;
	t_node	*head; // the beginning of the list
	t_node	*tail; // the end of the list
}				t_list;	

typedef struct	s_red
{
	int				type;
	char			*filename;
	struct s_red	*prev;
	struct s_red	*next;
}				t_red;

typedef struct s_cmd
{
	char			**args;
	t_list			*red;
	struct s_cmd	*prev;
	struct s_cmd	*next;
}				t_cmd;

// fnc of the prompt
char	*prompt(void); // display prompt and get commandline
void	sig_int_handler(int sig);
// fnc of the parser
t_list	*lexer(char *line, char **env); // lexical analyser
//fnc utils in tokenizer
t_list	*tokenizer(char *line);// converts the line into list of tokens 
//fnc utils in list
t_node	*new_node(int type, char *val);
t_node	*push_back(t_list *list, int type, char *val);
t_list	*new_list(void);
void	del_node(t_list *list, t_node *node);
//fnc exit

#endif