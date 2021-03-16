/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treatmap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynejmi <ynejmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 17:34:33 by ynejmi            #+#    #+#             */
/*   Updated: 2021/03/04 17:34:34 by ynejmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "c3d.h"

int		check_map(t_map *data, int j)
{
	int		i;
	int		k;
	int		x;

	k = -1;
	x = 0;
	data->spno = 0;
	while (++k < j && (i = -1))
		while (data->jmap[k][++i])
		{
			if (data->jmap[k][i] == '2')
				data->spno++;
			if (((ft_strchr("WSNE102", data->jmap[k][i]) < 0) && (data->jmap[k][
			i] > ' ')) || ((ft_strchr("WSNE", data->jmap[k][i]) > -1) && x++))
				ft_error("Map syntax unrecognized\n");
			if ((ft_strchr("WSNE02", data->jmap[k][i]) > -1))
				if (!(k && i && (k < j) && (i < ft_strlen(data->jmap[k - 1])
				&& (i < ft_strlen(data->jmap[k + 1]) && (i <
				ft_strlen(data->jmap[k])) && (data->jmap[k][i + 1] > ' ') &&
				(data->jmap[k][i - 1] > ' ') && (data->jmap[k + 1][i] > ' ')
				&& (data->jmap[k - 1][i] > ' ')))))
					ft_error("Map syntax unrecognized\n");
		}
	return (x);
}

int		check_list(t_map *data)
{
	if (!(data->res[0] * data->res[1] * data->ymap) || !(data->north &&
	data->east && data->south && data->west && data->sprite) ||
	!((data->c[3] + 1) * (data->f[3] + 1)))
		return (0);
	return (1);
}

void	fillspace(t_map *data)
{
	int		j;
	int		i;

	g_map++;
	j = -1;
	i = 0;
	data->xmap = 0;
	while (++j < data->ymap || (j = 0))
		if (data->xmap < ft_strlen(data->jmap[j]))
			data->xmap = ft_strlen(data->jmap[j]);
	while (data->jmap[j][i] || (++j < data->ymap && !(i = 0)))
	{
		while (data->jmap[j][i] && data->jmap[j][i] <= ' ')
			data->jmap[j][i] = '1';
		if (!data->jmap[j][++i] && j < data->ymap && i < data->xmap)
			data->jmap[j] = fillblank(data->jmap[j], '1', data->xmap - i);
	}
}

int		map(t_map *data, char *mapstr)
{
	int		i;
	int		j;

	data->map = ft_strdup(mapstr);
	while (data->gg > 0)
	{
		data->gg = get_next_line(data->fd, &mapstr);
		data->map = ft_strjoin(data->map, 1, mapstr);
	}
	i = nl(data->map);
	j = i;
	data->jmap = malloc(sizeof(char *) * (i));
	while (i)
		ft_split(data->map, &data->jmap[j - i--], &data->map, nx(data->map));
	while (blank(data->jmap[j - 1]))
		free(data->jmap[--j]);
	while (j - i)
		if (!data->jmap[j - ++i][0])
			ft_error("empty line inside map\n");
	i = 0;
	if (!(check_map(data, j)))
		ft_error("player not found ?\n");
	data->ymap = j;
	fillspace(data);
	return (data->ymap);
}

int		blank(char *str)
{
	int		i;

	i = 0;
	if (!str[i] || str[i] == '\n')
		ft_error("empty line after map\n");
	while (str && str[i])
		if (str[i++] > ' ')
			return (0);
	return (1);
}
