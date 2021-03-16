/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynejmi <ynejmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 17:35:28 by ynejmi            #+#    #+#             */
/*   Updated: 2021/03/04 17:35:29 by ynejmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "c3d.h"

int		sphandle(t_struct *j)
{
	int			k;

	k = -1;
	j->v = 0;
	while (++k < j->d.spno)
	{
		j->s[k].ang = j->d.pa - atan2(j->d.px - j->s[k].x, j->d.py - j->s[k].y);
		if (j->s[k].ang > M_PI)
			j->s[k].ang -= M_PI * 2;
		if (j->s[k].ang < -M_PI)
			j->s[k].ang += M_PI * 2;
		j->s[k].v = 0;
		if ((j->s[k].ang < FOV) && (j->s[k].ang > -FOV) && ((j->s[k].d =
		dist(j->s[k].x, j->s[k].y, j->d.px, j->d.py)) > 32) && ++j->v)
			j->s[k].v = 1;
	}
	if (j->vs)
		free(j->vs);
	j->vs = malloc(sizeof(t_sprite) * j->v);
	vssort(j);
	return (1);
}

int		sprender(t_struct *j)
{
	int		i;
	int		y;
	int		x;
	double	spheight;
	double	spwidth;

	i = -1;
	j->i.col = 0xff;
	while (++i < j->v)
	{
		spheight = TS * j->pp / j->vs[i].d;
		spwidth = spheight;
		j->prspdim = TS / spwidth;
		j->vs[i].tp = j->d.res[1] / 2 - (int)spheight / 2;
		y = j->vs[i].tp;
		y *= (y > 0);
		j->vs[i].bp = j->d.res[1] - y;
		j->lsx = j->d.res[0] / 2 - spwidth / 2 + tan(j->vs[i].ang) * j->pp;
		x = (j->lsx > 0) * j->lsx;
		j->rsx = j->lsx + spwidth;
		sprendloop(j, x, y, i);
	}
	return (0);
}

void	sprendloop(t_struct *j, int x, int y, int i)
{
	while (x < j->rsx)
	{
		j->vs[i].offsx = (x - j->lsx) * j->prspdim;
		j->vs[i].offsx *= (j->vs[i].offsx > 0);
		while (y < j->vs[i].bp)
		{
			if (x > 0 && x < j->d.res[0] && y > 0 && y < j->d.res[1])
			{
				j->vs[i].offsy = (y - j->vs[i].tp) * j->prspdim;
				j->i.col = j->t.sp[j->vs[i].offsy * TS + j->vs[i].offsx];
				if ((j->i.col != j->t.sp[0]) && j->vs[i].d < j->r[x].d)
					small_pp(&j->i, x, y);
			}
			y++;
		}
		y = j->vs[i].tp * (y > 0);
		x++;
	}
}

void	plang(t_struct *j, char c)
{
	if (c == 'N')
		j->d.pa = 0;
	else if (c == 'W')
		j->d.pa = M_PI_2;
	else if (c == 'S')
		j->d.pa = M_PI;
	else if (c == 'E')
		j->d.pa = M_PI_2 * 3;
}
