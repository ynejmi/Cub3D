/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynejmi <ynejmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 17:34:01 by ynejmi            #+#    #+#             */
/*   Updated: 2021/03/04 17:34:02 by ynejmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "c3d.h"

int		filler_func(t_map *data, char *line, int i)
{
	if (!ft_strncmp(&line[i], "R ", 2) && !g_res)
		return (win_res(data, &line[i + 2], 0));
	else if (!ft_strncmp(&line[i], "F ", 2) && !g_flo)
		return (flooor(data, &line[i + 2], 0));
	else if (!ft_strncmp(&line[i], "C ", 2) && !g_cei)
		return (ceiling(data, &line[i + 2], 0));
	else if (!ft_strncmp(&line[i], "S ", 2) && !g_spr)
		return (txtr(data, &line[i + 2], 0));
	else if (!ft_strncmp(&line[i], "WE ", 3) && !g_wes)
		return (txtr(data, &line[i + 3], 1));
	else if (!ft_strncmp(&line[i], "NO ", 3) && !g_nor)
		return (txtr(data, &line[i + 3], 2));
	else if (!ft_strncmp(&line[i], "SO ", 3) && !g_sou)
		return (txtr(data, &line[i + 3], 3));
	else if (!ft_strncmp(&line[i], "EA ", 3) && !g_eas)
		return (txtr(data, &line[i + 3], 4));
	else if (line[i] == '1')
		return (map(data, line));
	else
		return (-1);
}

int		data_set(t_map *data, char *line)
{
	int		i;

	i = 0;
	while (line && line[i])
	{
		if (line[i] > ' ')
			return (filler_func(data, line, i));
		i++;
	}
	return (0);
}

int		read_file(char *filename, t_map *data)
{
	char	*line;
	int		i;

	sinit(data);
	ginit();
	i = 0;
	if (ft_strncmp(&filename[ft_strlen(filename) - 4], ".cub", 4))
		ft_error("Incorrect File Extension\n");
	if ((data->fd = open(filename, O_RDONLY)) < 1)
		ft_error("Incorrect File Name\n");
	while (data->gg > 0 && ++i)
	{
		data->gg = get_next_line(data->fd, &line);
		if (data_set(data, line) < 0)
			ft_error("file syntax unrecognized\n");
		free(line);
	}
	if (!check_list(data))
		ft_error("lacking information\n");
	return (i);
}

char	*fillblank(char *str, char c, int l)
{
	char	*s;
	int		i;

	s = malloc(sizeof(char) * (l + 1));
	i = 0;
	while (l--)
		s[i++] = c;
	s[i] = '\0';
	return (ft_strjoin(str, 0, s));
}
