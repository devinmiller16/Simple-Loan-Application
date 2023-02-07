//<Programming Assignment 1> -- This program creates an Amortization schedule based on your principle, interest rate, and term
//CSIS 112-<D01>
//<Citations if necessary> -- Error checking code was used from C++ programming Assignment Instructions document

#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

double CalcPayment(double principle, double monthlyInterestRate, int term);
void Amortize(int currentPeriod, int totalPeriods, double paymentAmount, double monthlyInterestRate, double currentBalance, double principle);

int main()
{
	cout << "Devin Miller - Assignment #1" << endl << endl;
	cout << "Loan Application - Amortization Schedule" << endl << endl;

	int term, totalPeriods, currentPeriod;
	double principle, paymentAmount, monthlyInterestRate, currentBalance;
	currentPeriod = 0;
	
	//Asks user to enter the principle amount ***********************************************************************************************************************************************************
	cout << "Enter the principle amount: ";
	cin >> currentBalance;
	
	//Ensures the user can only enter in an expected value
	while (cin.fail() || currentBalance < 0)
	{
		cout << "You must enter a number, and that number must be positive. Please try again. " << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> currentBalance;
	}

	//Asks user to enter the annual interest rate *******************************************************************************************************************************************************
	cout << "Enter the annual interest rate: ";
	cin >> monthlyInterestRate;

	//Ensures the user can only enter in an expected value
	while (cin.fail() || monthlyInterestRate < 0)
	{
		cout << "You must enter a number, and that number must be positive. Please try again. " << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> monthlyInterestRate;
	}

	//Asks user to enter the term of the loan ***********************************************************************************************************************************************************
	cout << "Enter the term of the loan (10, 15, or 30 years): ";
	cin >> term;
	
	//Ensures the user can only enter in 10, 15, or 30 years
	while ((cin.fail()) || ((term != 10) && (term != 15) && (term != 30)))
	{
		cout << "You must enter a valid loan term of 10, 15, or 30 years. Please try again. " << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> term;
	}

	totalPeriods = term * 12; //Calculates the total period
	monthlyInterestRate = ((monthlyInterestRate / 100) / 12); //Converts the percentage the user enters in into decimal format
	principle = monthlyInterestRate * currentBalance; //Calculates the principle amount
	paymentAmount = CalcPayment(currentBalance, monthlyInterestRate, term); //Calculates your monthly payment using the CalcPayment function
	cout << setw(5) << "Payment" << setw(15) << "Amount" << setw(15) << "Interest" << setw(15) << "Principle" << setw(15) << "Balance" << endl;
	cout << setw(67) << currentBalance << endl;
	Amortize(currentPeriod, totalPeriods, paymentAmount, monthlyInterestRate, currentBalance, principle); //Creates an amoritization schedule using the Amoritize schedule
	return 0;
}

double CalcPayment(double principle, double monthlyInterestRate, int term) //Function that calculates the monthly payment and returns it to the main function
{
	double monthlyPayment, x;
	term = term * 12;
	x = 1 + monthlyInterestRate;
	cout << fixed << showpoint << setprecision(2);
	monthlyPayment = (principle * (monthlyInterestRate * (pow(x, term))) / (pow(x, term) - 1));
	cout << "Monthly payment: $" << monthlyPayment << endl << endl;
	return monthlyPayment;
}

void Amortize(int currentPeriod, int totalPeriods, double paymentAmount, double monthlyInterestRate, double currentBalance, double principle) //Function that prints an Amoritization schedule using a recursive function
{
	currentPeriod++;
	double interest;
	interest = currentBalance * monthlyInterestRate; //Calculates your new interest 
	principle = paymentAmount - interest; //Calculates your new principle amount
	currentBalance = currentBalance - principle; //Calculates your new balance
	
	if (currentPeriod <= totalPeriods)
	{
		cout << setw(7) << currentPeriod << setw(15) << paymentAmount << setw(15) << interest << setw(15) << principle << setw(15) << currentBalance << endl;
		return Amortize(currentPeriod, totalPeriods, paymentAmount, monthlyInterestRate, currentBalance, principle); //Re-invokes the Amoritize function to calculate your next months payments
	}
}
