/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynejmi <ynejmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 17:34:14 by ynejmi            #+#    #+#             */
/*   Updated: 2021/03/04 17:34:15 by ynejmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "c3d.h"

void	small_pp(t_mlx *img, int x, int y)
{
	char	*dst;

	dst = img->addr + (x * img->bpp / 8 + y * img->ll);
	*(unsigned int*)dst = img->col;
}

int		shiftbit(int col)
{
	if (col > 0x00ffff)
		col -= (0x00ff00);
	else if (col > 0x0000ff)
		col -= (0x0000ff);
	return (col);
}

double	normalize(double ang)
{
	while (ang >= 2 * M_PI || ang < 0)
	{
		if (ang < 0)
			ang += 4 * M_PI;
		ang -= 2 * M_PI;
	}
	return (ang);
}

int		ft_exit(void)
{
	exit(0);
}

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*ptr;
	int				i;

	if (!len)
		return (b);
	i = -1;
	ptr = b;
	while (len--)
		ptr[++i] = (unsigned char)c;
	return (b);
}
