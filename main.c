/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynejmi <ynejmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 17:34:19 by ynejmi            #+#    #+#             */
/*   Updated: 2021/03/04 17:34:20 by ynejmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "c3d.h"

int		main(int argv, char **argc)
{
	int			k;
	t_struct	j;

	if (!argfill(argv, argc, &j))
		ft_error("wrong arguments\n");
	k = read_file(argc[1], &j.d);
	if (k > -1)
	{
		j.m = mlx_init();
		j.w = mlx_new_window(j.m, j.d.res[0], j.d.res[1], "Cub3D");
		j.i.img = mlx_new_image(j.m, j.d.res[0], j.d.res[1]);
		j.i.addr = mlx_get_data_addr(j.i.img, &j.i.bpp, &j.i.ll, &j.i.enn);
		txt(&j);
		j.s = malloc(sizeof(t_sprite) * j.d.spno);
		j.r = malloc(sizeof(t_ray) * j.d.res[0]);
		mapscan(&j);
		mlx_loop_hook(j.m, &next_map, &j);
		mlx_loop(j.m);
		printf("%d\n", k);
	}
}

int		next_map(t_struct *j)
{
	mlx_hook(j->w, 2, 1L << 0, key_pressed, j);
	mlx_hook(j->w, 3, 1L << 0, key_released, j);
	mlx_hook(j->w, 17, 0L, &ft_exit, 0);
	j->d.pa += 2 * j->d.rt * M_PI / 180;
	j->d.pa = normalize(j->d.pa);
	next_step(j, M_PI_2 * j->d.lr + j->d.pa, 10 * j->d.mv);
	j->k = 0;
	j->r[j->k--].ra = -FOV / 2;
	mlx_destroy_image(j->m, j->i.img);
	j->i.img = mlx_new_image(j->m, j->d.res[0], j->d.res[1]);
	j->i.addr = mlx_get_data_addr(j->i.img, &j->i.bpp, &j->i.ll, &j->i.enn);
	while (++j->k < j->d.res[0])
	{
		j->r[j->k].rx = j->d.px;
		j->r[j->k].ry = j->d.py;
		raycast(j);
	}
	if (!j->j)
		bmp_exporter(j);
	mlx_put_image_to_window(j->m, j->w, j->i.img, 0, 0);
	return (1);
}

int		next_step(t_struct *j, double a, int d)
{
	if (j->d.jmap[(int)floor((j->d.py - d * cos(a)) / TS)][(int)floor(j->d.px /
	TS)] != '1')
		j->d.py -= 6 * j->d.mv * cos((M_PI_2 * j->d.lr) + j->d.pa);
	if (j->d.jmap[(int)floor(j->d.py / TS)][(int)floor((j->d.px - d * sin(a)) /
	TS)] != '1')
		j->d.px -= 6 * j->d.mv * sin((M_PI_2 * j->d.lr) + j->d.pa);
	return (1);
}

int		key_pressed(int keycode, t_struct *j)
{
	if (keycode == 53)
		exit(1);
	if (((keycode == 123) || (keycode == 124)) && (j->d.mv = 1))
		j->d.lr = -(((keycode - 123) * 2) - 1);
	if (!(keycode) || (keycode == 2))
		j->d.rt = -(keycode - 1);
	if ((keycode == 1) || (keycode == 13))
		j->d.mv = (keycode - 7) / 6;
	return (1);
}

int		key_released(int keycode, t_struct *j)
{
	if (((keycode == 123) || (keycode == 124)) && !(j->d.mv = 0))
		j->d.lr = 0;
	if (!(keycode) || (keycode == 2))
		j->d.rt = 0;
	if ((keycode == 1) || (keycode == 13))
		j->d.mv = 0;
	return (1);
}
