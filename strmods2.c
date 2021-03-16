/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strmods2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynejmi <ynejmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 17:35:31 by ynejmi            #+#    #+#             */
/*   Updated: 2021/03/04 17:35:32 by ynejmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "c3d.h"

int		ft_strncmp(char *s1, char *s2, int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] == s2[i] && s1[i] && s2[i] && (i + 1 < n))
		i++;
	return (s1[i] - s2[i]);
}

int		ft_strchr(char *str, char c)
{
	int		i;
	char	*s;

	s = (char *)str;
	i = 0;
	while (s[i] != c)
	{
		if (s[i])
			i++;
		else
			return (-1);
	}
	return (i);
}

int		ft_atoi(char *str, char c)
{
	int	a;
	int i;
	int l;

	a = 0;
	i = 0;
	l = 0;
	if (!ft_isdigit(str[i]))
		return (-1);
	while (str[i] == '0')
		i++;
	while (ft_isdigit(str[i]))
	{
		l++;
		if (l < 6)
			a = a * 10 + (str[i] - '0');
		i++;
	}
	if ((str[i] && str[i] != c))
		return (-1);
	return (a);
}

int		ft_isdigit(int n)
{
	if ((n >= '0' && n <= '9'))
		return (1);
	return (0);
}

void	sinit(t_map *data)
{
	data->fd = 0;
	data->gg = 1;
	data->px = 0;
	data->py = 0;
	data->mv = 0;
	data->rt = 0;
	data->lr = 0;
	data->map = 0;
	data->east = 0;
	data->west = 0;
	data->north = 0;
	data->south = 0;
	data->f[0] = -1;
	data->f[1] = -1;
	data->f[2] = -1;
	data->f[3] = -1;
	data->c[0] = -1;
	data->c[1] = -1;
	data->c[2] = -1;
	data->c[3] = -1;
	data->res[0] = 0;
	data->res[1] = 0;
	data->sprite = 0;
}
