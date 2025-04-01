#include <iostream>
#include "Eigen/Eigen"
#include <iomanip>

using namespace std;
using namespace Eigen;

// Create a function that solves a linear system using PALU decomposition
Vector2d PALU_solver(const Matrix2d& M,const Vector2d& v)
{
	PartialPivLU<Matrix2d> palu(M);
	Vector2d solution_palu = palu.solve(v);
	return solution_palu;
}

// Create a function that solves a linear system using QR decomposition
Vector2d QR_solver(const Matrix2d& M,const Vector2d& v)
{
	HouseholderQR<Matrix2d> QR(M);
	Vector2d solution_QR = QR.solve(v);
	return solution_QR;	
}

// Create a function to compute the relative error between the exact solution and the numeric provided one 
double Error(const Vector2d& exact_solution,const Vector2d& numeric_solution)
{
	double relative_Error;
	double Error =  (numeric_solution - exact_solution).norm() / exact_solution.norm();
	return Error;
}

// Create a function to print the solution provided in both PALU and QR methods and the relative error
void Analysis(const Matrix2d& M,const Vector2d& v,const Vector2d& exact_solution,const int& n)
{
	cout << "-System number " << n << ":" << endl;
	cout << "the solution with the PALU method is: [" << PALU_solver(M, v).transpose() << "]" << endl;
	cout << "the relative error is: " << Error(exact_solution, PALU_solver(M, v)) << endl;
	cout << "the solution with the QR method is: [" << QR_solver(M, v).transpose() << "]" << endl;
	cout << "the relative error is: " << Error(exact_solution, QR_solver(M, v)) << endl;
}

int main()
{
	Matrix2d A_1, A_2, A_3;
	Vector2d b_1, b_2, b_3, x;
	
	//exaxt solution (exptected)
	
	x << -1.0e+0, -1.0e+00;
	
	// system 1:
	
	A_1 << 5.547001962252291e-01, -3.770900990025203e-02,
		 8.320502943378437e-01, -9.992887623566787e-01;
		 
	b_1 << -5.169911863249772e-01, 1.672384680188350e-01;
	
	// system 2:
	
	A_2 << 5.547001962252291e-01, -5.540607316466765e-01,
	     8.320502943378437e-01, -8.324762492991313e-01;
		 
	b_2 << -6.394645785530173e-04, 4.259549612877223e-04;
	
	// system 3:
	
	A_3 << 5.547001962252291e-01, -5.547001955851905e-01,
	     8.320502943378437e-01, -8.320502947645361e-01;
	
		 
	b_3 << -6.400391328043042e-10, 4.266924591433963e-10;
	
	cout << scientific << setprecision(16);
	
	Analysis(A_1, b_1, x, 1);
	Analysis(A_2, b_2, x, 2);
	Analysis(A_3, b_3, x, 3);
	
    return 0;
}
