/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   txtdraw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynejmi <ynejmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 17:34:26 by ynejmi            #+#    #+#             */
/*   Updated: 2021/03/04 17:34:27 by ynejmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "c3d.h"

int		txtr(t_map *data, char *path, int c)
{
	int		i;
	char	*x;

	i = 0;
	while (path && path[i])
	{
		if (path[i] > ' ')
		{
			if (!(x = ft_strdup(&path[i])))
				return (-1);
			if ((!c) && (++g_spr))
				data->sprite = x;
			else if ((c == 1) && (++g_wes))
				data->east = x;
			else if ((c == 2) && (++g_nor))
				data->south = x;
			else if ((c == 3) && (++g_sou))
				data->north = x;
			else if ((c == 4) && (++g_eas))
				data->west = x;
			return (ft_strlen(&path[i]));
		}
		i++;
	}
	return (-1);
}

void	ft_error(char *err)
{
	printf("Error\n");
	printf("%s", err);
	exit(1);
}

void	cffill(t_struct *j, int k, int c)
{
	int	i;

	i = 0;
	j->i.col = j->d.c[3];
	while (c && i < k)
		small_pp(&j->i, j->k, i++);
	i = k;
	j->i.col = j->d.f[3];
	while (!c && i < j->d.res[1])
		small_pp(&j->i, j->k, i++);
}

int		argfill(int argv, char **argc, t_struct *j)
{
	if (argv == 2)
		return (j->j = 1);
	if (argv == 3)
		if (!(ft_strncmp(argc[2], "--save", 7)))
			return (!(j->j = 0));
	return (0);
}

void	ginit(void)
{
	g_res = 0;
	g_flo = 0;
	g_cei = 0;
	g_spr = 0;
	g_wes = 0;
	g_nor = 0;
	g_sou = 0;
	g_eas = 0;
	g_map = 0;
}
