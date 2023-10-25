/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 12:50:16 by obouhlel          #+#    #+#             */
/*   Updated: 2023/10/25 13:58:00 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*dst_cpy;
	char	*src_cpy;

	dst_cpy = (char *)dst;
	src_cpy = (char *)src;
	while (n--)
		*dst_cpy++ = *src_cpy++;
}

void	free_key_value(char *key, char *value)
{
	ft_free((void **)&key);
	ft_free((void **)&value);
}
