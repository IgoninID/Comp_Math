#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

double f(double x)
{
	return -4 * pow(x, 3) + 3 * pow(x, 2) - 5 * x + 4;
}

double df(double x)
{
	return -12 * pow(x, 2) + 6 * x - 5;
}

double ddf(double x)
{
	return -24 * x + 6;
}

double halfy(double a, double b, double e, int &iter)
{
	iter = 0;
	while (b - a > 2 * e)
	{
		iter += 1;
		double c = (a + b) / 2;
		if (f(a) * f(c) < 0)
		{
			b = c;
		}
		else
		{
			if (f(b) * f(c) < 0)
			{
				a = c;
			}
			else
			{
				return (a + b) / 2;
			}
		}
	}
	return (a + b) / 2;
}

double chord(double a, double b, double e, int &iter)
{
	iter = 0;
	double c_old = 0;
	double c_new = (a * f(b) - b * f(a)) / (f(b) - f(a));
	if ((f(a) * f(c_new)) < 0)
	{
		c_old = b;
		b = c_new;
	}
	else
	{
		c_old = a;
		a = c_new;
	}
	while (abs(c_old - c_new) > e)
	{
		iter += 1;
		c_old = c_new;
		c_new = (a * f(b) - b * f(a)) / (f(b) - f(a));
		if ((f(a) * f(c_new)) < 0)
		{
			b = c_new;
		}
		else
		{
			a = c_new;
		}
	}
	return (a * f(b) - b * f(a)) / (f(b) - f(a));
}

double tango(double a, double b, double e, int &iter)
{
	iter = 0;
	double d_old = 0;
	double d_new = 0;
	if ((f(a) * ddf(a)) > 0)
	{
		d_old = a;
	}
	else
	{
		if ((f(b) * ddf(b)) > 0)
		{
			d_old = b;
		}
	}
	bool t = true;
	while (t == true)
	{
		iter += 1;
		if ((f(a) * ddf(a)) > 0)
		{
			d_new = a - f(a) / df(a);
			a = d_new;
		}
		else
		{
			if ((f(b) * ddf(b)) > 0)
			{
				d_new = b - f(b) / df(b);
				b = d_new;
			}
		}
		t = (abs(d_old - d_new) > e);
		d_old = d_new;
	}
	return d_new;
}

double comba(double a, double b, double e, int &iter)
{
	iter = 0;
	double c = 0;
	double d = 0;
	while ((b - a) > (2 * e))
	{
		iter += 1;
		c = (a * f(b) - b * f(a)) / (f(b) - f(a));
		if ((f(a) * ddf(a)) > 0)
		{
			d = a - f(a) / df(a);
			a = d;
			b = c;
		}
		else
		{
			if ((f(b) * ddf(b)) > 0)
			{
				d = b - f(b) / df(b);
				b = d;
				a = c;
			}
		}
	}
	return (a + b) / 2;
}

int main()
{
	int iter = 0;
	cout << fixed << setprecision(5) << halfy(-2, 2, 0.0001, iter) << " | iter: " << iter << "\n";
	cout << fixed << setprecision(5) << chord(-2, 2, 0.0001, iter) << " | iter: " << iter << "\n";
	cout << fixed << setprecision(5) << tango(-2, 2, 0.0001, iter) << " | iter: " << iter << "\n";
	cout << fixed << setprecision(5) << comba(-2, 2, 0.0001, iter) << " | iter: " << iter << "\n";
	return 0;
}