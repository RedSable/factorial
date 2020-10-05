/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapricot <aapricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 19:18:01 by aapricot          #+#    #+#             */
/*   Updated: 2020/09/30 20:18:51 by aapricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	output(int nerror)
{
	if (nerror == 1)
	{
		write(1,
		"Bad arguments. Try \"./fractol Julia/Mandelbrot/Cathedral\".\n", 59);
		exit(1);
	}
	if (nerror == 2)
	{
		write(1, "Failed to load kernel.\n", 23);
		exit(0);
	}
}

void	main_2(t_param *p, t_kernel *k)
{
	init_param(p);
	init_kernel(k, p);
	close_kernel(k);
	mlx_hook(p->win_ptr, 2, 0, key_event, p);
	mlx_hook(p->win_ptr, 4, 0, mouse_press, p);
	mlx_hook(p->win_ptr, 6, 0, mouse_move, p);
	mlx_put_image_to_window(p->mlx_ptr, p->win_ptr, p->img.img_ptr, 0, 0);
}

void	hot_keys(t_param *p)
{
	mlx_string_put(p->mlx_ptr, p->win_ptr, 20, 20,
	0x000000, "zoom: mouse scroll");
	mlx_string_put(p->mlx_ptr, p->win_ptr, 20, 40, 0x000000, "iterations: +/-");
	mlx_string_put(p->mlx_ptr, p->win_ptr, 20, 60, 0x000000, "fractols: J/M/C");
	mlx_string_put(p->mlx_ptr, p->win_ptr, 20, 80, 0x000000, "colors: 1/2/3/4");
}
