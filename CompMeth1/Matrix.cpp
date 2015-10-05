#include "Matrix.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <cmath>
#include <functional>
#define TIME 5.0

Matrix::Matrix(int row, int col)
{
		
}

Matrix::Matrix()
{
	this->dt = 0.5*(dx / u);
	if ((dt / dx) >= 1.0)
	{
		std::cout << "dt: " << dt << " is lower than dx/u - solution may be not stable." << std::endl;
	}
}

Matrix::~Matrix()
{

}

double Matrix::sign(double x)
{
	double res;
	if (x == 0.)
	{
		return 0.0;
	}
	res = abs(x) / x;
	return res;
}

double Matrix::f0_num(double x)
{	
	if ( ( (x > -40.0) && (x < 40.0) ) )
	{
		double result = (1.0 / 2.0)*((sign(x) + 1.0));
		std::cout << result << " " << std::endl;
		return result;
	}else 
	
	if ( (x == -40.0)  )
	{
		return 0.0;
	}else 
	
	if ( (x == 40.0)  )
	{
		return 1.0;
	}else
	return 0.;	
}
void Matrix::upwind_scheme_F0()
{		
	//in working version try to change constant values in 'for' loops
	double tmpArr[100];
	double nxtArr[100];
	double x = -40.0;
	std::cout.precision(5);

	std::cout << "tmpArr is calculating \n" << std::endl;
	for (int i = 0; i < 100; i++)
	{
		tmpArr[i] = f0_num(x);
		x = (-40.0) + i * dx;
	}
	std::cout << (dt / dx) << std::endl;

	memcpy(nxtArr, tmpArr, sizeof(nxtArr));
	for (double time = 1; time <= 5; time += dt)
	{
		std::cout << "nxtArr is calculating \n" << std::endl;		
		x = -40.0 + dx;

		for (int i = 1; i < 100; i++)
		{
			x = (-40.0) + i * dx;
			nxtArr[i] = tmpArr[i] - (dt / dx)*(tmpArr[i] - tmpArr[i - 1]);
			std::cout << nxtArr[i] << " " ;
		}
		x = -40.0;
		memcpy(tmpArr, nxtArr, sizeof(nxtArr));
		
	}

	//save results to file
	std::ofstream file;
	file.open("results_f0_numerical.txt");
	for (int i = 0; i < 100; i++)
	{		
		file << nxtArr[i] << std::endl;
	}
	file.close();

}
double Matrix::f0_analytical(double x, double t)
{
	double result = 0;
	result = (1. / 2.)*sign(x - t) + 1.;
	return result;
}
void Matrix::upwind_scheme_f0_analytic()
{
	//in working version try to change constant values in 'for' loops
	double tmpArr[100];
	double nxtArr[100];
	double x = -40.0;
	std::cout.precision(5);

	std::cout << "tmpArr is calculating \n" << std::endl;
	for (int i = 0; i < 100; i++)
	{
		tmpArr[i] = f0_analytical(x,0);
		x = (-40.0) + i * dx;
	}
	std::cout << (dt / dx) << std::endl;

	memcpy(nxtArr, tmpArr, sizeof(nxtArr));
	for (double time = 1; time <= 5; time += dt)
	{
		std::cout << "nxtArr is calculating \n" << std::endl;
		x = -40.0 + dx;

		for (int i = 1; i < 100; i++)
		{
			x = (-40.0) + i * dx;
			nxtArr[i] = tmpArr[i] - (dt / dx)*(tmpArr[i] - tmpArr[i - 1]);
			std::cout << nxtArr[i] << " ";
		}
		x = -40.0;
		memcpy(tmpArr, nxtArr, sizeof(nxtArr));
	}

	//save results to file
	std::ofstream file;
	file.open("results_f0_analytical.txt");
	for (int i = 0; i < 100; i++)
	{
		file << nxtArr[i] << std::endl;
	}
	file.close();
}


double Matrix::f1_num(double x)
{
	if (((x > -40.0) && (x < 40.0)))
	{		
		double tmp = x*x*(-1.0);		
		double result = (1. / 2.)*(exp(tmp));
		std::cout << result << " " << std::endl;
		return result;
	}
	else

	if ((x == -40.0))
	{
		return 0.0;
	}
	else

	if ((x == 40.0))
	{
		return 1.0;
	}
	else
		return 0.;
}
void Matrix::upwind_scheme_F1(func_ptr func)
{
	//in working version try to change constant values in 'for' loops
	double tmpArr[100];
	double nxtArr[100];
	double x = -40.0;	
	this->function_pointer = func;

	std::cout << "tmpArr is calculating \n" << std::endl;
	for (int i = 0; i < 100; i++)
	{
		//tmpArr[i] = f1_num(x);
		tmpArr[i] = (this->*function_pointer)(x);
		x = (-40.0) + i * dx;
	}
	std::cout << (dt / dx) << std::endl;

	memcpy(nxtArr, tmpArr, sizeof(nxtArr));
	for (double time = 1; time <= 5; time += dt)
	{
		std::cout << "nxtArr is calculating \n" << std::endl;
		x = -40.0 + dx;

		for (int i = 1; i < 100; i++)
		{
			x = (-40.0) + i * dx;
			nxtArr[i] = tmpArr[i] - (dt / dx)*(tmpArr[i] - tmpArr[i - 1]);
			std::cout << nxtArr[i] << " ";
		}
		x = -40.0;
		memcpy(tmpArr, nxtArr, sizeof(nxtArr));

	}

	//save results to file
	std::ofstream file;
	file.open("results_f1_numerical.txt");
	for (int i = 0; i < 100; i++)
	{
		file << nxtArr[i] << std::endl;
	}
	file.close();
}
double Matrix::f1_analytical(double x, double t)
{
	double result = 0;
	result = (1. / 2.)*exp(-((x - t)*(x - t)));
	return result;
}
void Matrix::upwind_scheme_f1_analytic()
{
	//in working version try to change constant values in 'for' loops
	double tmpArr[100];
	double nxtArr[100];
	double x = -40.0;
	std::cout.precision(5);

	std::cout << "tmpArr is calculating \n" << std::endl;
	for (int i = 0; i < 100; i++)
	{
		tmpArr[i] = f0_analytical(x, 0);
		x = (-40.0) + i * dx;
	}
	std::cout << (dt / dx) << std::endl;

	memcpy(nxtArr, tmpArr, sizeof(nxtArr));
	for (double time = 1; time <= 5; time += dt)
	{
		std::cout << "nxtArr is calculating \n" << std::endl;
		x = -40.0 + dx;

		for (int i = 1; i < 100; i++)
		{
			x = (-40.0) + i * dx;
			nxtArr[i] = tmpArr[i] - (dt / dx)*(tmpArr[i] - tmpArr[i - 1]);
			std::cout << nxtArr[i] << " ";
		}
		x = -40.0;
		memcpy(tmpArr, nxtArr, sizeof(nxtArr));
	}

	//save results to file
	std::ofstream file;
	file.open("results_f1_analytical.txt");
	for (int i = 0; i < 100; i++)
	{
		file << nxtArr[i] << std::endl;
	}
	file.close();
}