#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

double f(double x)
{
	return pow(2, x) - pow(x, 2);
}

double df(double x)
{
	return pow(2, x) * log(2) - 2 * x;
}

double ddf(double x)
{
	return pow(2, x) * pow(log(2), 2) - 2;
}

double halfy(double a, double b, double e, int &iter)
{
	while (b - a > 2 * e)
	{
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
		iter += 1;
	}
	return (a + b) / 2;
}

double chord(double a, double b, double e, int &iter)
{
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
		iter += 1;
	}
	return (a * f(b) - b * f(a)) / (f(b) - f(a));
}

double tango(double a, double b, double e, int &iter)
{
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
		iter += 1;
	}
	return d_new;
}

double comba(double a, double b, double e, int &iter)
{
	double c = 0;
	double d = 0;
	while ((b - a) > (2 * e))
	{
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
		iter += 1;
	}
	return (a + b) / 2;
}

int main()
{
	int iter1 = 0;
	int iter2 = 0;
	int iter3 = 0;
	int iter4 = 0;
	cout << fixed << setprecision(5) << halfy(3.7, 4.2, 0.0001, iter1) << " | iter: " << iter1 << "\n";
	cout << fixed << setprecision(5) << chord(3.7, 4.2, 0.0001, iter2) << " | iter: " << iter2 << "\n";
	cout << fixed << setprecision(5) << tango(3.7, 4.2, 0.0001, iter3) << " | iter: " << iter3 << "\n";
	cout << fixed << setprecision(5) << comba(3.7, 4.2, 0.0001, iter4) << " | iter: " << iter4 << "\n";
	return 0;
}