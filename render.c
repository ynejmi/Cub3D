/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynejmi <ynejmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 17:34:22 by ynejmi            #+#    #+#             */
/*   Updated: 2021/03/04 17:34:23 by ynejmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "c3d.h"

int		raycast(t_struct *j)
{
	j->r[j->k].ra = normalize(j->r[j->k].ra);
	j->r[j->k].c = cos(j->d.pa - j->r[j->k].ra);
	j->r[j->k].s = sin(j->d.pa - j->r[j->k].ra);
	j->r[j->k].t = tan(j->d.pa - j->r[j->k].ra);
	j->r[j->k].ns = (j->r[j->k].c > 0) * 2 - 1;
	j->r[j->k].we = (j->r[j->k].s > 0) * 2 - 1;
	vert(j);
	horz(j);
	j->r[j->k].e = (!j->r[j->k].vh || (j->r[j->k].hh && (j->r[j->k].dh <=
	j->r[j->k].dv)));
	j->r[j->k].rx = j->r[j->k].vx;
	j->r[j->k].ry = j->r[j->k].vy;
	j->t.offsx = (int)j->r[j->k].rx % TS;
	if (j->r[j->k].e && (j->r[j->k].rx = j->r[j->k].hx))
	{
		j->r[j->k].ry = j->r[j->k].hy;
		j->t.offsx = (int)j->r[j->k].ry % TS;
	}
	j->r[j->k].d = (j->r[j->k].dh * j->r[j->k].e) + (j->r[j->k].dv *
	!(j->r[j->k].e));
	j->c = sphandle(j);
	edrender(j);
	return (0);
}

double	dist(double x1, double y1, double x2, double y2)
{
	return (sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2)));
}

int		vert(t_struct *j)
{
	j->r[j->k].ry = TS * floor(j->d.py / TS) + TS * (j->r[j->k].ns < 0);
	j->r[j->k].rx -= (j->d.py - j->r[j->k].ry) * j->r[j->k].t;
	j->r[j->k].vh = 0;
	while (iswall(j, (j->r[j->k].ry - (j->r[j->k].ns > 0)) / TS, j->r[j->k].rx /
	TS) < 2)
	{
		if (iswall(j, (j->r[j->k].ry - (j->r[j->k].ns > 0)) / TS, j->r[j->k].rx
		/ TS))
		{
			j->r[j->k].vh = 1;
			j->r[j->k].vx = j->r[j->k].rx;
			j->r[j->k].vy = j->r[j->k].ry;
			break ;
		}
		j->r[j->k].ry -= TS * j->r[j->k].ns;
		j->r[j->k].rx -= TS * j->r[j->k].t * j->r[j->k].ns;
	}
	j->r[j->k].rx = j->d.px;
	j->r[j->k].ry = j->d.py;
	j->r[j->k].dv = dist(j->d.px, j->d.py, j->r[j->k].vx, j->r[j->k].vy);
	return (0);
}

int		horz(t_struct *j)
{
	j->r[j->k].rx = TS * floor(j->r[j->k].rx / TS) + TS * (j->r[j->k].we < 0);
	j->r[j->k].ry -= (j->d.px - j->r[j->k].rx) / j->r[j->k].t;
	j->r[j->k].hh = 0;
	while (iswall(j, j->r[j->k].ry / TS, (j->r[j->k].rx - (j->r[j->k].we > 0))
	/ TS) < 2)
	{
		if (iswall(j, j->r[j->k].ry / TS, (j->r[j->k].rx - (j->r[j->k].we > 0))
		/ TS))
		{
			j->r[j->k].hh = 1;
			j->r[j->k].hx = j->r[j->k].rx;
			j->r[j->k].hy = j->r[j->k].ry;
			break ;
		}
		else
		{
			j->r[j->k].rx -= TS * j->r[j->k].we;
			j->r[j->k].ry -= TS / j->r[j->k].t * j->r[j->k].we;
		}
	}
	j->r[j->k].rx = j->d.px;
	j->r[j->k].ry = j->d.py;
	j->r[j->k].dh = dist(j->d.px, j->d.py, j->r[j->k].hx, j->r[j->k].hy);
	return (0);
}

int		iswall(t_struct *j, double y, double x)
{
	if (x <= 0 || y <= 0 || x >= j->d.xmap || y >= j->d.ymap)
		return (2);
	if (ft_strchr("1 ", j->d.jmap[(int)y][(int)x]) > -1)
		return (1);
	return (0);
}
