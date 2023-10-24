/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 11:45:41 by obouhlel          #+#    #+#             */
/*   Updated: 2023/10/24 11:47:04 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

enum e_token
{
	FILES_IN = 0,
	FILES_OUT = 1,
	HEREDOC = 2,
	PIPE = 3,
	CMD = 4,
	ARGS = 5,
	SIMPLE_QUOTE = 6,
	DOUBLE_QUOTE = 7,
	REDIR_IN = 8,
	REDIR_OUT = 9,
	APPEND_IN = 10,
	APPEND_OUT = 11
};

#endif