#include <vector>
#include <algorithm>
#include <iostream>
#include <conio.h>
#include <iomanip>
#define CRT_SECURE_NO_WARNINGS
using namespace std;

double Gr(double R) {
	double
		a = 0.0000560626,
		b = -0.00271426,
		c = 0.0877624,
		d = -3.77841,
		g = -0.00000042991,
		f = 708.989;
	double OUT = g * pow(R, 5) + a * pow(R, 4) + b * pow(R, 3) + c * pow(R, 2) + d * R + f;
	return OUT;
}

double Sigm(double R, double Tot, double GrR, double Lim)
{
	double OUT = (1 / (1 + exp((Tot - GrR)/Lim)) - 0.5) * Lim;
	return OUT;
}

int main() {
	vector <int> GrR(83);
	for (int i = 1; i < 83; i++)
		GrR[i] = round(Gr(i * 80 / 82));

	cout << "_____________________________________________________________________________________________________________________\n";
	cout << "|Sub:       |DB(/150)       |MP(/100)       |AL(/100)       |PS(/100)       |PM(/100)       |EP(/100)       |EC(/100)|\n";
	cout << "|Enter Grade (A, B, C, D or F)                                                                                       |\n";
	cout << "|Grade:     ";
	vector <int> Gon = { 150,100,100,100,100,100,100 };
	vector <char> G(7);
	for (int i = 0; i < 7; i++)
	{
		cout << "|";
		G[i] = _getch();
		if (G[i] < 'A' || G[i] > 'F' || G[i] == 'E')
		{
			cout << "Invalid Grade\n";
			return 0;
		}
		cout << G[i] << setw(15);
	}
	cout << setw(9) << "|\n";

	cout << "|Enter Classwork (enter -1 if not known) (After Bonus if any(like MP))                                               |\n";
	cout << "|Classwork:\n";
	vector <int> Con = { 60,40,40,40,40,40,30 };
	vector <int> C(7);
	for (int i = 0; i < 7; i++)
	{
		cout << "(?/" << Con[i] << "): ";
		cin >> C[i];
		if (C[i] > Con[i] || C[i] < -1)
		{
			cout << "Invalid Classwork\n";
			return 0;
		}
	}
	vector <pair<double, double>> R(7);
	for (int i = 0; i < 7; i++)
	{
		double& l = R[i].first, & u = R[i].second;
		switch (G[i])
		{
		case 'A':
			l = .85 * Gon[i];
			u = 1 * Gon[i];
			break;
		case 'B':
			l = .75 * Gon[i];
			u = .85 * Gon[i];
			break;
		case 'C':
			l = .65 * Gon[i];
			u = .75 * Gon[i];
			break;
		case 'D':
			l = .5 * Gon[i];
			u = .65 * Gon[i];
			break;
		case 'F':
			l = 0 * Gon[i];
			u = .5 * Gon[i];
			break;
		}
		if (Con[i] - C[i] > Gon[i] - u && C[i] != -1)
			u = Gon[i] - (Con[i] - C[i]);
	}
	double sumL = 0, sumU = 0;
	vector <string> Sub = { "DB","MP","AL","PS","PM","EP","EC" };
	cout << "[lower ------ Expected ------ upper]\n";
	for (int i = 0; i < 7; i++)
	{
		sumL += R[i].first;
		sumU += R[i].second;
		cout << Sub[i] << setw(7) << R[i].first << setw(10) << (R[i].first + R[i].second) / 2
			<< setw(10) << R[i].second << endl;
	}
	double Tot = (sumL + sumU) / 2;
	cout << "Tot" << setw(6) << sumL << setw(10) << Tot
		<< setw(10) << sumU << endl << endl;

	int Rank = 0;
	cout << "You can enter your Ranking(1-82) to hopefully get a more accurate estimate of the grades and total\n";
	do
	{
		cout << "\nRank: ";
		cin >> Rank;
	} while (Rank < 1 || Rank > 82);
	double Sh = Sigm(Rank, Tot, GrR[Rank], min(sumU - Tot, Tot - sumL));
	cout << "[lower ------ Expected ------ upper]\n";
	for (int i = 0; i < 7; i++)
	{
		cout << Sub[i] << setw(7) << R[i].first << setw(10) << ((R[i].first + R[i].second) / 2 + Sh * Gon[i] / 750)
			<< setw(10) << R[i].second << endl;
	}
	cout << "Tot" << setw(6) << sumL << setw(10) << Tot + Sh
		<< setw(10) << sumU << endl << endl;
}
