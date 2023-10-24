/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:26:16 by fduzant           #+#    #+#             */
/*   Updated: 2023/10/24 12:32:10 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "colors.h"
# include "exec.h"
# include "lexer.h"
# include "library.h"
# include "parser.h"
# include "signal.h"
# include "token.h"
# include "utils.h"

enum e_error
{
	EXIT_MINISHELL = 2,
	EMPTY_COMMANDE = 1,
	NO_ERROR = 0
};

void		init_signal(void);
void		init_signal2(void);

#endif