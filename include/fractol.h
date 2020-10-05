/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapricot <aapricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/13 15:43:09 by aapricot          #+#    #+#             */
/*   Updated: 2020/09/30 22:52:44 by aapricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <mlx.h>
# include <Opencl/opencl.h>

# define KEY_A 0
# define KEY_B 11
# define KEY_C 8
# define KEY_D 2
# define KEY_E 14
# define KEY_F 3
# define KEY_G 5
# define KEY_H 4
# define KEY_I 34
# define KEY_J 38
# define KEY_K 40
# define KEY_L 37
# define KEY_M 46
# define KEY_N 45
# define KEY_O 31
# define KEY_P 35
# define KEY_Q 12
# define KEY_R 15
# define KEY_S 1
# define KEY_T 17
# define KEY_U 32
# define KEY_V 9
# define KEY_W 13
# define KEY_X 7
# define KEY_Y 16
# define KEY_Z 6
# define KEY_ZERO 29
# define KEY_ONE 18
# define KEY_TWO 19
# define KEY_THREE 20
# define KEY_FOUR 21
# define KEY_FIVE 23
# define KEY_SIX 22
# define KEY_SEVEN 26
# define KEY_EIGHT 28
# define KEY_NINE 25
# define KEY_UP 126
# define KEY_LEFT 123
# define KEY_DOWN 125
# define KEY_RIGHT 124
# define KEY_PLUS 24
# define KEY_MINUS 27
# define KEY_MULTI 67
# define KEY_SPACE 49
# define KEY_ENTER 36
# define KEY_ESC 53

# define WIDTH 1500
# define HEIGHT 1000
# define MAX_SOURCE_SIZE 0x100000

typedef struct s_kernel	t_kernel;
typedef struct s_param	t_param;
typedef struct s_image	t_image;

struct					s_image
{
	void				*img_ptr;
	char				*addr;
	int					bpp;
	int					size_line;
	int					endian;
};

struct					s_param
{
	void				*mlx_ptr;
	void				*win_ptr;
	t_image				img;
	char				*source_str;
	size_t				source_size;
	cl_int				check;
	cl_int				fractal;
	cl_double			minre;
	cl_double			maxre;
	cl_double			maxim;
	cl_double			minim;
	cl_double			new_minre;
	cl_double			new_maxre;
	cl_double			new_minim;
	cl_double			new_maxim;
	cl_int				iter;
	double				mouse_x;
	double				mouse_y;
	double				zoom;
	cl_double			c_im;
	cl_double			c_re;
	double				re_factor;
	double				im_factor;
	cl_int				color;
};

struct					s_kernel
{
	cl_int				ret;
	cl_platform_id		platform_id;
	cl_uint				ret_num_platforms;
	cl_device_id		device_id;
	cl_uint				ret_num_devices;
	cl_context			context;
	cl_command_queue	command_queue;
	cl_mem				img_mem_buf;
	cl_program			program;
	cl_kernel			kernel;
	cl_mem				array;
};

int						key_event(int keycode, t_param *pr);
int						mouse_press(int keycode, int x, int y, t_param *pr);
void					init_kernel(t_kernel *k, t_param *p);
void					close_kernel(t_kernel *k);
int						mouse_move(int x, int y, t_param *pr);
void					mouse1(t_kernel *k, t_param *pr);
void					mouse2(t_kernel *k, t_param *pr);
void					mouse3(t_kernel *k, t_param *pr);
void					mouse4(t_kernel *k, t_param *pr);
void					switch_key3(int keycode, t_param *p, t_kernel *k);
void					switch_key4(int keycode, t_param *p, t_kernel *k);
void					switch_key5(int keycode, t_param *p, t_kernel *k);
void					switch_key6(int keycode, t_param *p, t_kernel *k);
void					output(int nerror);
void					main_2(t_param *p, t_kernel *k);
int						init_param(t_param *p);
void					hot_keys(t_param *p);
int						ft_strcmp(const char *s1, const char *s2);

#endif
