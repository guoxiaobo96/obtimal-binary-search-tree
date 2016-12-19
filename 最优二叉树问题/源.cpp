#include<iostream>
using namespace std;
const int MaxVal = 9999;
const int n = 5;
double p[n + 1] = { -1,0.15,0.1,0.05,0.1,0.2 };
double q[n + 1] = { 0.05,0.1,0.05,0.05,0.05,0.1 };
int root[n + 1][n + 1];
double w[n + 2][n + 2];
double e[n + 2][n + 2];
void OptimalBst(double *p, double *q, int n)
{
	for (int i = 1; i <= n + 1; i++)
	{
		e[i][i - 1] = q[i - 1];
		w[i][i - 1] = q[i - 1];
	}
	for (int len = 1; len <= n; len++)
	{
		for (int i = 1; i <= n - len + 1; i++)
		{
			int j = i + len - 1;
			e[i][j] = MaxVal;
			w[i][j] = w[i][j - 1] + p[j] + q[j];
			for (int r = i; r <= j; r++)
			{
				double t = e[i][r - 1] + e[r + 1][j] + w[i][j];
				if(t<e[i][j])
				{
					e[i][j] = t;
					root[i][j] = r;
				}
			}
		}
	}
}

void printRoot()
{
	cout << "各子树的根" << endl;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			cout << root[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void printOptimalBst(int i, int j, int r)
{
	int rootChild = root[i][j];
	if (rootChild==root[1][n])
	{
		cout << "k" << rootChild << "为根";
		printOptimalBst(i, rootChild - 1, rootChild);
		printOptimalBst(rootChild + 1, j, rootChild);
		return;
	}
	if (j < i - 1)
	{
		return;
	}
	else if (j == i - 1)
	{
		if (j < r)
		{
			cout << "d" << j << "是k" << r << "的左孩子" << endl;
		}
		else
		{
			cout << "d" << j << "是k" << r << "的右孩子" << endl;
		}
		return;
	}
	else
	{
		if (rootChild < r)
		{
			cout << "k" << rootChild << "是k" << r << "的左孩子" << endl;
		}
		else
		{
			cout << "k" << rootChild << "是k" << r << "的左孩子" << endl;
		}
	}
	printOptimalBst(i, rootChild - 1, rootChild);
	printOptimalBst(rootChild + 1, j, rootChild);
}

int main()
{
	OptimalBst(p, q, n);
	printRoot();
	printOptimalBst(1, n, -1);
}