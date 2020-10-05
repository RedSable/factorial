/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapricot <aapricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 18:18:43 by aapricot          #+#    #+#             */
/*   Updated: 2020/09/30 20:15:14 by aapricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		mouse1(t_kernel *k, t_param *pr)
{
	pr->zoom = 0.0;
	pr->check = 0;
	pr->new_minre = -2.;
	pr->new_maxre = 2.0;
	pr->new_maxim = 1.4;
	pr->new_minim = pr->maxim - (pr->maxre - pr->minre) * HEIGHT / WIDTH;
	init_kernel(k, pr);
	close_kernel(k);
	mlx_put_image_to_window(pr->mlx_ptr, pr->win_ptr, pr->img.img_ptr, 0, 0);
	hot_keys(pr);
}

void		mouse2(t_kernel *k, t_param *pr)
{
	float		lengh;
	float		lengh2;
	double		wind;
	float		tmp;

	tmp = pr->new_maxre - pr->new_minre;
	wind = (double)WIDTH / (double)HEIGHT;
	lengh = pr->new_maxre - pr->new_minre;
	pr->new_minre += ((tmp - lengh / 1.2) * pr->re_factor);
	pr->new_maxre = pr->new_minre + lengh / 1.2;
	lengh2 = pr->new_maxim - pr->new_minim;
	pr->new_maxim -= ((tmp / wind - (lengh / 1.2) / wind) * pr->im_factor);
	pr->new_minim = pr->new_maxim - lengh2 / 1.2;
	pr->zoom *= 0.8;
	init_kernel(k, pr);
	close_kernel(k);
	mlx_put_image_to_window(pr->mlx_ptr, pr->win_ptr, pr->img.img_ptr, 0, 0);
	hot_keys(pr);
}

void		mouse3(t_kernel *k, t_param *pr)
{
	float		lengh;
	float		lengh2;
	double		wind;
	float		tmp;

	tmp = pr->new_maxre - pr->new_minre;
	wind = (double)WIDTH / (double)HEIGHT;
	lengh = pr->new_maxre - pr->new_minre;
	pr->new_minre += ((tmp - lengh * 1.2) * pr->re_factor);
	pr->new_maxre = pr->new_minre + lengh * 1.2;
	lengh2 = pr->new_maxim - pr->new_minim;
	pr->new_maxim -= ((tmp / wind - (lengh * 1.2) / wind) * pr->im_factor);
	pr->new_minim = pr->new_maxim - lengh2 * 1.2;
	pr->zoom *= 0.8;
	init_kernel(k, pr);
	close_kernel(k);
	mlx_put_image_to_window(pr->mlx_ptr, pr->win_ptr, pr->img.img_ptr, 0, 0);
	hot_keys(pr);
}

void		mouse4(t_kernel *k, t_param *pr)
{
	pr->new_minre = pr->minre;
	pr->new_maxre = pr->maxre;
	pr->new_maxim = pr->maxim;
	pr->new_minim = pr->minim;
	init_kernel(k, pr);
	close_kernel(k);
	mlx_put_image_to_window(pr->mlx_ptr, pr->win_ptr, pr->img.img_ptr, 0, 0);
	hot_keys(pr);
}
