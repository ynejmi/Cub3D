/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynejmi <ynejmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 17:33:37 by ynejmi            #+#    #+#             */
/*   Updated: 2021/03/04 17:33:38 by ynejmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "c3d.h"

int		edrender(t_struct *j)
{
	double	wh;
	int		y;

	wh = TS * j->pp / j->r[j->k].d;
	wh /= cos(j->r[j->k].ra);
	y = j->d.res[1] / 2 - (int)wh / 2;
	j->t.tp = y;
	y *= (y > 0);
	j->t.bp = j->d.res[1] - y;
	cffill(j, y, 1);
	while (y < j->t.bp)
	{
		j->t.offsy = (y - j->t.tp) * (TS / wh);
		colass(j);
		small_pp(&j->i, j->k, y++);
	}
	cffill(j, y, 0);
	if (!(j->k + 1 - j->d.res[0]) && j->c++)
		sprender(j);
	if (j->k + 1 < j->d.res[0])
		j->r[j->k + 1].ra = j->r[j->k].ra + FOV / j->d.res[0];
	return (0);
}

int		colass(t_struct *j)
{
	if (j->r[j->k].e && (j->r[j->k].rx - j->d.px < 0))
		j->i.col = j->t.we[j->t.offsy * TS + j->t.offsx];
	else if (j->r[j->k].e)
		j->i.col = j->t.ea[j->t.offsy * TS + j->t.offsx];
	else if ((j->r[j->k].ry - j->d.py < 0))
		j->i.col = j->t.no[j->t.offsy * TS + j->t.offsx];
	else
		j->i.col = j->t.so[j->t.offsy * TS + j->t.offsx];
	return (0);
}

void	mapscan(t_struct *j)
{
	int			i;
	int			k;
	int			f;

	k = 0;
	f = 0;
	i = 0;
	while (k < j->d.ymap)
	{
		if (j->d.jmap[k][i] == '2' && (j->s[f].x = j->i.x + TS / 2))
			j->s[f++].y = j->i.y + TS / 2;
		else if (ft_strchr("NEWS", j->d.jmap[k][i]) + 1)
		{
			plang(j, j->d.jmap[k][i]);
			j->d.jmap[k][i] = '0';
			j->d.px = j->i.x + TS / 2;
			j->d.py = j->i.y + TS / 2;
		}
		if (++i >= j->d.xmap && !(i = 0))
			j->i.y = TS * ++k;
		j->i.x = i * TS;
	}
}

int		txt(t_struct *j)
{
	int		k;
	void	*add;

	if (!(add = mlx_xpm_file_to_image(j->m, j->d.west, &k, &k)))
		ft_error("wrong texture path\n");
	j->t.we = (int *)mlx_get_data_addr(add, &k, &k, &k);
	if (!(add = mlx_xpm_file_to_image(j->m, j->d.east, &k, &k)))
		ft_error("wrong texture path\n");
	j->t.ea = (int *)mlx_get_data_addr(add, &k, &k, &k);
	if (!(add = mlx_xpm_file_to_image(j->m, j->d.north, &k, &k)))
		ft_error("wrong texture path\n");
	j->t.no = (int *)mlx_get_data_addr(add, &k, &k, &k);
	if (!(add = mlx_xpm_file_to_image(j->m, j->d.south, &k, &k)))
		ft_error("wrong texture path\n");
	j->t.so = (int *)mlx_get_data_addr(add, &k, &k, &k);
	if (!(add = mlx_xpm_file_to_image(j->m, j->d.sprite, &k, &k)))
		ft_error("wrong texture path\n");
	j->t.sp = (int *)mlx_get_data_addr(add, &k, &k, &k);
	j->pp = j->d.res[0] / 2 / tan(FOV / 2);
	return (1);
}

void	vssort(t_struct *j)
{
	int			i;
	int			k;
	t_sprite	tmp;

	i = -1;
	k = -1;
	while (++k < j->d.spno)
		if (j->s[k].v)
			j->vs[++i] = j->s[k];
	i = 0;
	while (i < j->v - 1)
	{
		k = i + 1;
		while (k < j->v)
		{
			if (j->vs[i].d < j->vs[k].d)
			{
				tmp = j->vs[i];
				j->vs[i] = j->vs[k];
				j->vs[k] = tmp;
			}
			k++;
		}
		i++;
	}
}
