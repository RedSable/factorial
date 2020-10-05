/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapricot <aapricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 16:42:00 by aapricot          #+#    #+#             */
/*   Updated: 2020/09/30 20:16:03 by aapricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int				mouse_move(int x, int y, t_param *pr)
{
	t_kernel	k;

	if (pr->check == 1)
	{
		pr->mouse_x = x;
		pr->mouse_y = y;
		pr->c_im = pr->maxim - pr->mouse_y * ((pr->maxim - pr->minim)
		/ (1000 - 1));
		pr->c_re = pr->minre + pr->mouse_x * ((pr->maxre - pr->minre)
		/ (1500 - 1));
		init_kernel(&k, pr);
		close_kernel(&k);
		mlx_put_image_to_window(pr->mlx_ptr, pr->win_ptr,
								pr->img.img_ptr, 0, 0);
		hot_keys(pr);
	}
	return (0);
}

int				mouse_press(int keycode, int x, int y, t_param *pr)
{
	t_kernel	k;

	pr->re_factor = (double)x / (double)(WIDTH - 1);
	pr->im_factor = (double)y / (double)(HEIGHT - 1);
	if (keycode == 1)
	{
		if (pr->check == 0 || pr->check == 2)
			pr->check = 1;
		else
			pr->check = 2;
	}
	else if (keycode == 2)
		mouse1(&k, pr);
	else if (keycode == 4)
		mouse2(&k, pr);
	else if (keycode == 5 && pr->new_minre > -2.)
		mouse3(&k, pr);
	else if ((keycode == 5 && pr->new_minre <= -2.) || keycode == 3)
		mouse4(&k, pr);
	return (0);
}

void			switch_key1(int keycode, t_param *p, t_kernel *k)
{
	if (keycode == KEY_ESC)
	{
		mlx_destroy_window(p->mlx_ptr, p->win_ptr);
		mlx_destroy_image(p->mlx_ptr, p->img.img_ptr);
		exit(0);
	}
	if (keycode == KEY_PLUS)
	{
		p->iter += 10;
		init_kernel(k, p);
		close_kernel(k);
		mlx_put_image_to_window(p->mlx_ptr, p->win_ptr, p->img.img_ptr, 0, 0);
	}
	if (keycode == KEY_MINUS)
	{
		p->iter -= 10;
		init_kernel(k, p);
		close_kernel(k);
		mlx_put_image_to_window(p->mlx_ptr, p->win_ptr, p->img.img_ptr, 0, 0);
	}
	hot_keys(p);
}

void			switch_key2(int keycode, t_param *p, t_kernel *k)
{
	if (keycode == KEY_LEFT)
	{
		p->new_minre -= (p->new_maxre - p->new_minre) * 0.005;
		p->new_maxre -= (p->new_maxre - p->new_minre) * 0.005;
		init_kernel(k, p);
		close_kernel(k);
		mlx_put_image_to_window(p->mlx_ptr, p->win_ptr, p->img.img_ptr, 0, 0);
	}
	if (keycode == KEY_RIGHT)
	{
		p->new_minre += (p->new_maxre - p->new_minre) * 0.005;
		p->new_maxre += (p->new_maxre - p->new_minre) * 0.005;
		init_kernel(k, p);
		close_kernel(k);
		mlx_put_image_to_window(p->mlx_ptr, p->win_ptr, p->img.img_ptr, 0, 0);
	}
	hot_keys(p);
}

int				key_event(int keycode, t_param *pr)
{
	t_param		*p;
	t_kernel	k;

	p = pr;
	switch_key1(keycode, p, &k);
	switch_key2(keycode, p, &k);
	switch_key3(keycode, p, &k);
	switch_key4(keycode, p, &k);
	switch_key5(keycode, p, &k);
	switch_key6(keycode, p, &k);
	return (0);
}
