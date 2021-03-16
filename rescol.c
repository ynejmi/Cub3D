/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rescol.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynejmi <ynejmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 17:34:10 by ynejmi            #+#    #+#             */
/*   Updated: 2021/03/04 17:34:11 by ynejmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "c3d.h"

int		win_res(t_map *data, char *restr, int j)
{
	int i;

	i = 0;
	g_res++;
	while (restr && restr[i] && j < 2)
	{
		if (restr[i] > ' ')
		{
			if (((data->res[j] = ft_atoi(&restr[i], ' ')) >= 100) && j < 2)
			{
				if (data->res[j] > 2560 - (1120 * j))
					data->res[j] = 2560 - (1120 * j);
				while (ft_isdigit(restr[i]))
					i++;
				if ((j == 1) && !restr[i])
					return (1);
				return (win_res(data, &restr[i], ++j));
			}
			else
				ft_error("resolution\n");
		}
		i++;
	}
	ft_error("resolution\n");
	return (-1);
}

int		flooor(t_map *data, char *colstr, int j)
{
	int i;

	i = 0;
	g_flo++;
	while ((colstr && colstr[i]))
	{
		if ((colstr[i++] > ' ' && i--))
		{
			if (colstr[i] == ',')
				i++;
			if (((data->f[j] = ft_atoi(&colstr[i], ',')) >= 0) &&
			(data->f[j] < 256))
			{
				while (ft_isdigit(colstr[i]))
					colstr++;
				return (flooor(data, &colstr[i], ++j));
			}
			else
				ft_error("floor color\n");
		}
	}
	if (j == 3)
		return (data->f[j] = (data->f[0] << 16 | data->f[1] << 8 | data->f[2]));
	ft_error("floor color\n");
	return (-1);
}

int		ceiling(t_map *data, char *colstr, int j)
{
	int i;

	i = 0;
	g_cei++;
	while ((colstr && colstr[i]))
		if ((colstr[i++] > ' ' && i--))
		{
			if (colstr[i] == ',')
				i++;
			if (((data->c[j] = ft_atoi(&colstr[i], ',')) >= 0) &&
			(data->c[j] < 256))
			{
				while (ft_isdigit(colstr[i]))
					colstr++;
				return (ceiling(data, &colstr[i], ++j));
			}
			else
				ft_error("ceiling color\n");
		}
	if (j == 3)
		return (data->c[j] = (data->c[0] << 16 | data->c[1] << 8 | data->c[2]));
	ft_error("ceiling color\n");
	return (-1);
}
