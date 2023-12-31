/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 11:36:24 by obouhlel          #+#    #+#             */
/*   Updated: 2023/10/28 00:26:30 by obouhlel         ###   ########.fr       */
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

typedef struct s_cmds
{
	char		**cmd;
}	t_cmds;

typedef struct s_file
{
	char		*name_file;
	int			type;
}	t_file;

typedef struct s_redir
{
	int			nb_files;
	t_file		*files;
}	t_redir;

typedef struct s_parser
{
	t_cmds		*cmds;
	t_redir		*redir;
	int			size_redir;
}	t_parser;

typedef struct s_envp
{
	char		*key;
	char		*value;
}	t_envp;

enum e_pipes
{
	READ,
	WRITE
};

typedef struct s_heredoc
{
	char		*delimiter;
	char		*name_file;
	int			fd;
}	t_heredoc;

typedef struct s_save
{
	char	**envp;
	t_envp	*envp_s;
	int		size;
}	t_save;

typedef struct s_exec
{
	char	*to_free;
	t_envp	*envp_s;
	int		size;
	int		**pipes;
	int		id_child;
	pid_t	*pid;
	int		status;
}	t_exec;

typedef struct s_data
{
	char		**to_free;
	char		**envp;
	int			nb_cmd;
	int			nb_pipe;
	int			nb_redir;
	int			nb_heredoc;
	t_lexer		*lexer;
	t_heredoc	*heredoc;
	t_parser	parser;
	t_exec		exec;
}	t_data;

#endif