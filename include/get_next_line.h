/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sobouatt <sobouatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 14:49:53 by sobouatt          #+#    #+#             */
/*   Updated: 2021/02/08 21:23:46 by sobouatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

int		ft_strlen(char *str);
int		check_end(char *str);
int		where(char *str);
void	save_space(char **save, char **line);
int		get_next_line(int fd, char **line);
char	*ft_strdup(char *str);
char	*ft_substr(char const *s, unsigned int start, int len, int f);
char	*ft_strjoin(char *s1, char *s2);

#endif