/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybiouss <aybiouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 15:27:08 by aybiouss          #+#    #+#             */
/*   Updated: 2022/11/04 07:35:26 by aybiouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1000
#endif

char	*kept_one(char **str, int newline)
{
	int		l;
	char	*tmp;

	l = ft_strlen(*str);
	tmp = ft_substr(*str, newline, l);
	free(*str);
	*str = NULL;
	return (tmp);
}

char	*returned_line(char **line, char **all, int newline)
{
	*line = ft_substr(*all, 0, newline + 1);
	*all = kept_one(all, newline + 1);
	return (*line);
}

int	check_newline(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*get_next_line(int fd)
{
	char		buf[BUFFER_SIZE + 1];
	static char	*all[OPEN_MAX];
	char		*line;
	ssize_t		length;
	int			newline;

	length = read(fd, buf, BUFFER_SIZE);
	if (!all[fd] && length >= 0)
		all[fd] = ft_strdup("");
	while (length >= 0)
	{
		buf[length] = 0;
		all[fd] = ft_strjoin(all[fd], buf);
		if (!length && !all[fd][0])
			break ;
		newline = check_newline(all[fd]);
		if (newline != -1)
			return (returned_line(&line, &all[fd], newline));
		else if (!length)
			return (kept_one(&all[fd], 0));
		length = read(fd, buf, BUFFER_SIZE);
	}
	free(all[fd]);
	all[fd] = NULL;
	return (NULL);
}
