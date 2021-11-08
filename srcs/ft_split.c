/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sobouatt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 21:12:11 by sobouatt          #+#    #+#             */
/*   Updated: 2020/11/20 19:13:20 by sobouatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	wlen(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != c && s[i])
		i++;
	return (i);
}

int	wccount(char const *s, char c)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == '\0' || s[i + 1] == c))
			words++;
		i++;
	}
	return (words);
}

char	**fill(char const *s, char c, char **str, int words)
{
	int	i;
	int	j;
	int	len;

	i = -1;
	while (++i < words)
	{
		while (*s == c)
			s++;
		len = wlen(s, c);
		str[i] = malloc(sizeof(char) * len + 1);
		if (!str[i])
			return (NULL);
		j = 0;
		while (j < len)
			str[i][j++] = *s++;
		str[i][j] = '\0';
	}
	str[i] = NULL;
	return (str);
}

char	**ft_split(char *s, char c)
{
	char	**str;
	int		words;

	if (!s)
		return (NULL);
	words = wccount(s, c);
	str = malloc((words + 1) * sizeof(char *));
	if (!str)
		return (NULL);
	str = fill(s, c, str, words);
	return (str);
}
