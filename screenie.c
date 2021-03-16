/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenie.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynejmi <ynejmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 17:35:20 by ynejmi            #+#    #+#             */
/*   Updated: 2021/03/04 17:35:25 by ynejmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "c3d.h"

static	int		create_file(void)
{
	int	fd;

	if (!((fd = open("screenshot.bmp", O_WRONLY | O_CREAT |
	O_TRUNC, S_IRUSR | S_IWUSR)) > 0))
		ft_error("could not create .bmp file\n");
	return (fd);
}

static void		create_header(t_struct *j, t_bmp *bmp)
{
	bmp->byte_type[0] = 0x42;
	bmp->byte_type[1] = 0x4D;
	bmp->byte_size = (j->d.res[0] *
					j->d.res[1] * 4) + 54;
	bmp->byte_reserved = 0x00000000;
	bmp->byte_offset = 0x36;
	bmp->header_size = 40;
	bmp->image_width = j->d.res[0];
	bmp->image_height = -j->d.res[1];
	bmp->color_planes = 1;
	bmp->bits_per_pixel = 32;
	bmp->compression = 0;
	bmp->image_size = (j->d.res[0] * j->d.res[1] * 4);
	bmp->bits_xpels_per_meter = 2835;
	bmp->bits_xpels_per_meter = 2835;
	bmp->total_colors = 0;
	bmp->important_colors = 0;
}

static void		write_header(int fd, t_bmp bmp)
{
	int			r;

	r = 0;
	r = write(fd, &bmp.byte_type, 2);
	r = write(fd, &bmp.byte_size, 4);
	r = write(fd, &bmp.byte_reserved, 4);
	r = write(fd, &bmp.byte_offset, 4);
	r = write(fd, &bmp.header_size, 4);
	r = write(fd, &bmp.image_width, 4);
	r = write(fd, &bmp.image_height, 4);
	r = write(fd, &bmp.color_planes, 2);
	r = write(fd, &bmp.bits_per_pixel, 2);
	r = write(fd, &bmp.compression, 4);
	r = write(fd, &bmp.image_size, 4);
	r = write(fd, &bmp.bits_xpels_per_meter, 4);
	r = write(fd, &bmp.bits_ypels_per_meter, 4);
	r = write(fd, &bmp.total_colors, 4);
	r = write(fd, &bmp.important_colors, 4);
}

static void		write_file(t_struct *j, int fd, int imagesize)
{
	char		*pixel_array;
	int			i;
	int			k;

	if (!(pixel_array = malloc(sizeof(char) * imagesize)))
		ft_error("malloc err\n");
	i = 0;
	k = 0;
	while (i < imagesize)
	{
		pixel_array[k++] = j->i.addr[i++];
		pixel_array[k++] = j->i.addr[i++];
		pixel_array[k++] = j->i.addr[i++];
		pixel_array[k++] = j->i.addr[i++];
	}
	k = write(fd, pixel_array, imagesize);
	free(pixel_array);
}

void			bmp_exporter(t_struct *j)
{
	t_bmp		bmp;
	int			fd;

	ft_memset(&bmp, 0, sizeof(t_bmp));
	fd = create_file();
	create_header(j, &bmp);
	write_header(fd, bmp);
	write_file(j, fd, bmp.image_size);
	close(fd);
	j->j = 1;
	exit(0);
}
