/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapricot <aapricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 14:08:37 by aapricot          #+#    #+#             */
/*   Updated: 2020/09/30 22:36:16 by aapricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int						init_param(t_param *p)
{
	if (!(p->mlx_ptr = mlx_init()))
		return (-1);
	if (!(p->win_ptr = mlx_new_window(p->mlx_ptr, WIDTH, HEIGHT, "fractol")))
		return (-1);
	p->img.img_ptr = mlx_new_image(p->mlx_ptr, WIDTH, HEIGHT);
	p->img.addr = mlx_get_data_addr(p->img.img_ptr, &p->img.bpp,
					&p->img.size_line, &p->img.endian);
	p->check = 0;
	p->minre = -2.;
	p->maxre = 2.0;
	p->maxim = 1.4;
	p->minim = p->maxim - (p->maxre - p->minre) * HEIGHT / WIDTH;
	p->new_minre = -2.;
	p->new_maxre = 2.0;
	p->new_maxim = 1.4;
	p->new_minim = p->maxim - (p->maxre - p->minre) * HEIGHT / WIDTH;
	p->iter = 0;
	p->zoom = 1.0;
	p->color = 0;
	return (0);
}

void					set_args(t_kernel *k, t_param *p)
{
	k->kernel = clCreateKernel(k->program, "fractol", &k->ret);
	k->ret = clSetKernelArg(k->kernel, 0, sizeof(cl_mem),
							(void *)&k->img_mem_buf);
	k->ret = clSetKernelArg(k->kernel, 1, sizeof(cl_int), &p->check);
	k->ret = clSetKernelArg(k->kernel, 2, sizeof(cl_double), &p->new_minre);
	k->ret = clSetKernelArg(k->kernel, 3, sizeof(cl_double), &p->new_maxre);
	k->ret = clSetKernelArg(k->kernel, 4, sizeof(cl_double), &p->new_maxim);
	k->ret = clSetKernelArg(k->kernel, 5, sizeof(cl_double), &p->new_minim);
	k->ret = clSetKernelArg(k->kernel, 6, sizeof(cl_double), &p->c_im);
	k->ret = clSetKernelArg(k->kernel, 7, sizeof(cl_double), &p->c_re);
	k->ret = clSetKernelArg(k->kernel, 8, sizeof(cl_int), &p->iter);
	k->ret = clSetKernelArg(k->kernel, 9, sizeof(cl_char), &p->fractal);
	k->ret = clSetKernelArg(k->kernel, 10, sizeof(cl_int), &p->color);
}

void					init_kernel(t_kernel *k, t_param *p)
{
	size_t				global_item_size;
	size_t				local_item_size;

	global_item_size = WIDTH * HEIGHT;
	local_item_size = 250;
	k->platform_id = NULL;
	k->device_id = NULL;
	k->ret = clGetPlatformIDs(1, &k->platform_id, &k->ret_num_platforms);
	k->ret = clGetDeviceIDs(k->platform_id, CL_DEVICE_TYPE_DEFAULT, 1,
							&k->device_id, &k->ret_num_devices);
	k->context = clCreateContext(NULL, 1, &k->device_id, NULL, NULL, &k->ret);
	k->command_queue = clCreateCommandQueue(k->context, k->device_id, 0,
											&k->ret);
	k->img_mem_buf = clCreateBuffer(k->context, CL_MEM_READ_ONLY,
					WIDTH * HEIGHT * sizeof(int), NULL, &k->ret);
	k->ret = clEnqueueWriteBuffer(k->command_queue, k->img_mem_buf, CL_TRUE, 0,
				WIDTH * HEIGHT * sizeof(int), p->img.addr, 0, NULL, NULL);
	k->program = clCreateProgramWithSource(k->context, 1,
	(const char **)&p->source_str, (const size_t *)&p->source_size, &k->ret);
	k->ret = clBuildProgram(k->program, 1, &k->device_id, NULL, NULL, NULL);
	set_args(k, p);
	k->ret = clEnqueueNDRangeKernel(k->command_queue, k->kernel, 1, NULL,
						&global_item_size, &local_item_size, 0, NULL, NULL);
	k->ret = clEnqueueReadBuffer(k->command_queue, k->img_mem_buf, CL_TRUE, 0,
					WIDTH * HEIGHT * sizeof(int), p->img.addr, 0, NULL, NULL);
}

void					close_kernel(t_kernel *k)
{
	k->ret = clFlush(k->command_queue);
	k->ret = clFinish(k->command_queue);
	k->ret = clReleaseKernel(k->kernel);
	k->ret = clReleaseProgram(k->program);
	k->ret = clReleaseMemObject(k->img_mem_buf);
	k->ret = clReleaseCommandQueue(k->command_queue);
	k->ret = clReleaseContext(k->context);
}

int						main(int ac, char **av)
{
	t_kernel			k;
	t_param				p;
	int					fp;

	if (ac != 2)
		output(1);
	fp = open("./srcs/fractol.cl", O_RDONLY);
	if (!fp)
		output(2);
	if (!ft_strcmp(av[1], "Julia"))
		p.fractal = 1;
	else if (!ft_strcmp(av[1], "Mandelbrot"))
		p.fractal = 2;
	else if (!ft_strcmp(av[1], "Cathedral"))
		p.fractal = 3;
	else
		output(1);
	p.source_str = (char *)malloc(MAX_SOURCE_SIZE);
	p.source_size = read(fp, p.source_str, MAX_SOURCE_SIZE);
	close(fp);
	main_2(&p, &k);
	hot_keys(&p);
	mlx_loop(p.mlx_ptr);
}
