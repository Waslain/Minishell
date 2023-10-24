/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 11:36:24 by obouhlel          #+#    #+#             */
/*   Updated: 2023/10/24 12:26:03 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_lexer
{
	char				*str;
	int					type;
	struct s_lexer		*next;
}	t_lexer;

typedef struct s_cmd_tab
{
	char				*cmd;
	int					index;
	struct s_cmd_tab	*next;
}	t_cmd_tab;

typedef struct s_data
{
	char	*cmd;
	char	**envp;
	int		nb_cmd;
	int		nb_pipe;
	t_lexer	*lexer;
}	t_data;
#endif