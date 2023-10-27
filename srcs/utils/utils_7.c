/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_7.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 20:13:05 by obouhlel          #+#    #+#             */
/*   Updated: 2023/10/27 20:13:43 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_array_size(void **array, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		ft_free((void **)&array[i]);
		i++;
	}
	free(array);
}
