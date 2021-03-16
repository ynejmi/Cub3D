/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c3d.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynejmi <ynejmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 17:33:56 by ynejmi            #+#    #+#             */
/*   Updated: 2021/03/04 17:33:57 by ynejmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef C3D_H

# define C3D_H

# include <mlx.h>
# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

# define FOV 1.047197551196597631
# define TS 64

int g_res;
int g_flo;
int g_cei;
int g_spr;
int g_wes;
int g_nor;
int g_sou;
int g_eas;
int g_map;

typedef struct	s_mlx {
	int				x;
	int				y;
	int				ll;
	int				bpp;
	int				col;
	int				enn;
	void			*img;
	char			*addr;
}				t_mlx;

typedef struct	s_ray {
	double			rx;
	double			ry;
	double			vx;
	double			vy;
	double			d;
	double			dv;
	double			hx;
	double			hy;
	double			dh;
	double			ra;
	int				e;
	double			c;
	double			s;
	double			t;
	int				ns;
	int				we;
	int				hh;
	int				vh;
}				t_ray;

typedef struct	s_map {
	int				fd;
	int				gg;
	double			px;
	double			py;
	double			pa;
	int				tx;
	int				ty;
	int				mv;
	int				lr;
	int				rt;
	int				f[4];
	int				c[4];
	int				ymap;
	int				xmap;
	int				spno;
	char			*map;
	char			*west;
	char			*east;
	char			*north;
	char			*south;
	char			**jmap;
	int				res[2];
	char			*sprite;
}				t_map;

typedef struct	s_texture {
	int				offsx;
	int				offsy;
	int				*we;
	int				*ea;
	int				*no;
	int				*so;
	int				*sp;
	int				tp;
	int				bp;
	int				a;
	int				wh;
}				t_texture;

typedef struct	s_sprite {
	double			x;
	double			y;
	int				v;
	double			d;
	double			ang;
	int				tp;
	int				bp;
	int				offsx;
	int				offsy;
}				t_sprite;

typedef struct	s_struct {
	t_mlx			i;
	t_map			d;
	t_ray			*r;
	t_texture		t;
	t_sprite		*s;
	t_sprite		*vs;
	int				v;
	int				c;
	int				k;
	int				j;
	double			lsx;
	double			rsx;
	double			prspdim;
	double			pp;
	double			pd;
	void			*m;
	void			*w;
}				t_struct;

typedef struct	s_bmp
{
	char			byte_type[2];
	unsigned int	byte_size;
	unsigned int	byte_reserved;
	unsigned int	byte_offset;
	unsigned		header_size;
	int				image_width;
	int				image_height;
	unsigned short	color_planes;
	unsigned short	bits_per_pixel;
	unsigned int	compression;
	unsigned int	image_size;
	int				bits_xpels_per_meter;
	int				bits_ypels_per_meter;
	unsigned int	total_colors;
	unsigned int	important_colors;
}				t_bmp;

void			ginit(void);
ssize_t			nx(char *str);
int				nl(char *map);
int				ft_exit(void);
int				blank(char *str);
int				txt(t_struct *j);
int				vert(t_struct *j);
int				horz(t_struct *j);
int				ft_isdigit(int n);
int				frwd(t_struct *j);
int				ft_strlen(char *s);
void			sinit(t_map *data);
int				shift_bit(int col);
void			vssort(t_struct *j);
void			ft_error(char *err);
int				colass(t_struct *j);
void			mapscan(t_struct *j);
int				raycast(t_struct *j);
double			normalize(double ang);
int				edrender(t_struct *j);
int				sprender(t_struct *j);
int				sphandle(t_struct *j);
char			*ft_strdup(char *src);
int				next_map(t_struct *j);
int				check_list(t_map *data);
void			bmp_exporter(t_struct *j);
int				ft_atoi(char *str, char c);
void			plang(t_struct *j, char c);
int				ft_strchr(char *str, char c);
int				check_map(t_map *data, int j);
int				map(t_map *data, char *mapstr);
void			cffill(t_struct *j, int k, int c);
int				data_set(t_map *data, char *line);
int				get_next_line(int fd, char **line);
void			small_pp(t_mlx *data, int x, int y);
int				txtr(t_map *data, char *path, int c);
char			*fillblank(char *str, char c, int l);
int				key_pressed(int keycode, t_struct *j);
int				ft_strncmp(char *s1, char *s2, int n);
char			*ft_strjoin(char *s1, int c, char *s2);
int				key_released(int keycode, t_struct *j);
int				read_file(char *filename, t_map	*data);
void			*ft_memset(void *b, int c, size_t len);
int				iswall(t_struct *j, double y, double x);
int				next_step(t_struct *j, double a, int d);
int				win_res(t_map *data, char *restr, int j);
int				flooor(t_map *data, char *colstr, int j);
int				win_res(t_map *data, char *restr, int j);
int				ceiling(t_map *data, char *colstr, int j);
int				argfill(int argv, char **argc, t_struct *j);
int				filler_func(t_map *data, char *line, int i);
void			sprendloop(t_struct *j, int x, int y, int i);
double			dist(double x1, double y1, double x2, double y2);
int				ft_split(char *src, char **d1, char **d2, int spx);
char			*ft_substr(char *s, unsigned int start, size_t len);
#endif
