/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapricot <aapricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 18:38:26 by aapricot          #+#    #+#             */
/*   Updated: 2020/09/30 20:16:39 by aapricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		switch_key3(int keycode, t_param *p, t_kernel *k)
{
	if (keycode == KEY_J)
	{
		p->fractal = 1;
		p->iter = 0;
		p->new_minre = p->minre;
		p->new_maxre = p->maxre;
		p->new_maxim = p->maxim;
		p->new_minim = p->minim;
		init_kernel(k, p);
		close_kernel(k);
		mlx_put_image_to_window(p->mlx_ptr, p->win_ptr, p->img.img_ptr, 0, 0);
	}
	if (keycode == KEY_M)
	{
		p->fractal = 2;
		p->iter = 0;
		p->new_minre = p->minre;
		p->new_maxre = p->maxre;
		p->new_maxim = p->maxim;
		p->new_minim = p->minim;
		init_kernel(k, p);
		close_kernel(k);
		mlx_put_image_to_window(p->mlx_ptr, p->win_ptr, p->img.img_ptr, 0, 0);
	}
	hot_keys(p);
}

void		switch_key4(int keycode, t_param *p, t_kernel *k)
{
	if (keycode == KEY_TWO)
	{
		p->color = 1;
		init_kernel(k, p);
		close_kernel(k);
		mlx_put_image_to_window(p->mlx_ptr, p->win_ptr, p->img.img_ptr, 0, 0);
	}
	if (keycode == KEY_THREE)
	{
		p->color = 2;
		init_kernel(k, p);
		close_kernel(k);
		mlx_put_image_to_window(p->mlx_ptr, p->win_ptr, p->img.img_ptr, 0, 0);
	}
	if (keycode == KEY_FOUR)
	{
		p->color = 3;
		init_kernel(k, p);
		close_kernel(k);
		mlx_put_image_to_window(p->mlx_ptr, p->win_ptr, p->img.img_ptr, 0, 0);
	}
	hot_keys(p);
}

void		switch_key5(int keycode, t_param *p, t_kernel *k)
{
	if (keycode == KEY_C)
	{
		p->fractal = 3;
		p->iter = 0;
		p->new_minre = p->minre;
		p->new_maxre = p->maxre;
		p->new_maxim = p->maxim;
		p->new_minim = p->minim;
		init_kernel(k, p);
		close_kernel(k);
		mlx_put_image_to_window(p->mlx_ptr, p->win_ptr, p->img.img_ptr, 0, 0);
	}
	if (keycode == KEY_DOWN)
	{
		p->new_minim -= (p->new_maxim - p->new_minim) * 0.005;
		p->new_maxim -= (p->new_maxim - p->new_minim) * 0.005;
		init_kernel(k, p);
		close_kernel(k);
		mlx_put_image_to_window(p->mlx_ptr, p->win_ptr, p->img.img_ptr, 0, 0);
	}
	hot_keys(p);
}

void		switch_key6(int keycode, t_param *p, t_kernel *k)
{
	if (keycode == KEY_ONE)
	{
		p->color = 0;
		init_kernel(k, p);
		close_kernel(k);
		mlx_put_image_to_window(p->mlx_ptr, p->win_ptr, p->img.img_ptr, 0, 0);
	}
	if (keycode == KEY_UP)
	{
		p->new_minim += (p->new_maxim - p->new_minim) * 0.005;
		p->new_maxim += (p->new_maxim - p->new_minim) * 0.005;
		init_kernel(k, p);
		close_kernel(k);
		mlx_put_image_to_window(p->mlx_ptr, p->win_ptr, p->img.img_ptr, 0, 0);
	}
	hot_keys(p);
}
