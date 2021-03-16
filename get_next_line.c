/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynejmi <ynejmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 17:35:05 by ynejmi            #+#    #+#             */
/*   Updated: 2021/03/04 17:35:06 by ynejmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "c3d.h"

int		nl(char *map)
{
	int		i;

	i = 0;
	while (*map++)
		if (*map == '\n' || !*map)
			i++;
	return (i);
}

ssize_t	nx(char *str)
{
	int		i;
	char	*s;

	s = (char *)str;
	i = 0;
	while (s[i] != '\n')
	{
		if (s[i])
			i++;
		else
			return (-1);
	}
	return (i);
}

int		ffre(char **buf, char **jake, int i)
{
	free(*jake);
	free(*buf);
	return (i);
}

int		check_erread(int fd, char **buf, char **jake, int i)
{
	if (jake[0] != NULL)
		ft_split(jake[0], buf, jake, ft_strlen(jake[0]));
	else
	{
		if (!(buf[0] = malloc(sizeof(char) * 513)))
			return (-1);
		if ((i = read(fd, buf[0], 512)) < 1)
			return (ffre(buf, jake, i));
		buf[0][i] = '\0';
	}
	return (1);
}

int		get_next_line(int fd, char **line)
{
	char		*buf;
	int			i;
	static char *jake;

	*line = ft_strdup("");
	while (nx(*line) < 0 || (buf = NULL))
	{
		if ((i = check_erread(fd, &buf, &jake, i)) < 1)
			return (i);
		if ((i = nx(buf)) >= 0 && (ft_split(buf, &buf, &jake, i)) &&
		(*line = ft_strjoin(*line, 0, buf)))
			break ;
		else
			*line = ft_strjoin(*line, 0, buf);
	}
	return (1);
}
