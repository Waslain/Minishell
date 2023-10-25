/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 11:35:41 by obouhlel          #+#    #+#             */
/*   Updated: 2023/10/25 13:55:29 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <unistd.h>
# include <stdlib.h>
# include "library.h"
# include "struct.h"

//libft.c
size_t		ft_strlen(const char *str);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strnstr(const char *str, const char *to_find, size_t len);
char		*ft_strdup(const char *src);
char		*ft_substr(char const *s, unsigned int start, size_t len);

//libft1.c
void		ft_bzero(void *s, size_t n);
void		*ft_calloc(size_t nmemb, size_t size);
int			ft_strcmp(char *s1, char *s2);
size_t		ft_strlcpy(char *dest, const char *src, size_t size);
int			ft_isalpha(int c);

//ft_split.c
char		**ft_split(char const *str, char charset);

//utils.c
void		ft_free(void **ptr);
void		free_array(char **tab);
void		freeall(char **cmd, char **paths, char *bin);
int			get_envp(t_data *data, char **envp);
void		ft_error(const char *str);

void		ft_memcpy(void *dst, const void *src, size_t n);
void		free_key_value(char *key, char *value);
#endif