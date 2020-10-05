__kernel void		fractol(__global int *img_addr, int c, double minr,
							double maxr, double maxi, double mini, double ci, double cr, int iter,
							char frac, int color)
{
	int			gid = get_global_id(0);
	double		x = gid % 1500;
	double		y = gid / 1500;
	double		MinRe = minr;
	double		MaxRe = maxr;
	double		MaxIm = maxi;
	double		MinIm = mini;

	double		Re_factor = (MaxRe - MinRe) / (1500 - 1);
	double		Im_factor = (MaxIm - MinIm) / (1000 - 1);
	
	int			MaxIter = 10 + iter;
	int			count = 0;

	double		c_im;
	double		c_re;
	double		z_im;
	double		z_re;
	double 		t = 0;
	double		r = 0;
	double		g = 0;
	double		b = 0;

	if (frac == 1)
	{
		c_re = 0.3;
		c_im = -0.01;
		z_re = MinRe + x * Re_factor;
		z_im = MaxIm - y * Im_factor;
		if (c > 0)
		{
			c_im = ci;
			c_re = cr;
			z_re = MinRe + x * Re_factor;
			z_im = MaxIm - y * Im_factor;
		}
	}

	if (frac == 2 || frac == 3)
	{
		c_im = MaxIm - y * Im_factor;
		c_re = MinRe + x * Re_factor;
		z_im = c_im;
		z_re = c_re;
	}
	bool		isInside = true;

	while (count < MaxIter)
	{
		double	z_re2 = z_re * z_re;
		double	z_im2 = z_im * z_im;
		if (z_re2 + z_im2 > 10)
		{
			isInside = false;
			break;
		}
		if (frac == 3)
		{
			z_im = 2 * z_re * z_im + tan(2 * z_re * z_im);
			z_re = z_re2 - z_im2 + tan(z_re2 - z_im2);
		}
		else if (frac == 2 || frac == 1)
		{
			z_im = 2 * z_re * z_im + c_im;
			z_re = z_re2 - z_im2 + c_re;
		}
		count = count + 1;
	}
	if (color == 0 || color == 1)
		t = count + 1 - log(log(sqrt(z_re * z_re + z_im * z_im)) / log(5.0)) / log(2.0);
	else if (color == 2 || color == 3)
		t = count + 1 - (((z_re * z_re + z_im * z_im)) / (5.0)) / (2.0);
	if (count == MaxIter)
	{
		img_addr[gid] = 0x000000;
	}
	else
	{
		if (color == 1 || color == 3)
		{
			r = (sin(.29 * t + 1) * 100 + 100) * 0.1;
			g = (sin(0.16 * t + 2) * 100 + 100) * 1.0;
			b = 255 * 0.8;
		}
		else if (color == 0 || color == 2)
		{
			r = sin(.29 * t + 1) * 100 + 100;
			b = (sin(0.16 * t + 2) * 100 + 100);
			g = r;
		}
		img_addr[gid] = ((((int)r << 16) & 0x00ff0000) | (((int)g << 8) & 0x0000ff00) | ((int)b & 0x000000ff));
	}
}