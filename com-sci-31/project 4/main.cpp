#include <iostream>
#include <string>
#include <cassert>
using namespace std;

int locateMaximum(const string array[], int n);
bool hasNoDuplicates(const string array[], int n);
int countXPairs(const string array[], int n, int x);
int findSecondToLastOccurrence(const string array[], int n, string target);
int countPunctuation(const string array[], int n);
int flipAround(string array[], int n);
int moveToEnd(string array[], int n, int pos);

int main()
{
	string a[6] = { "123", "456", "789", "gamma", "beta", "delta" };
	assert(locateMaximum(a, 6) == 3);
	assert(hasNoDuplicates(a, 6) == true);
	assert(countPunctuation(a, 6) == 0);
	assert(flipAround(a, 6) == 3);
	for (int i = 0; i < 6; i++)
	{
		cout << a[i] << " ";
	}
	cout << endl;
	string b[6] = { "7", "3", "10", "8", "5", "6" };
	assert(countXPairs(b, 6, 13) == 3);
	assert(moveToEnd(b, 6, 3) == 3);
	// expect 7 3 10 5 6 8
	for (int i = 0; i < 6; i++)
	{
		cout << b[i] << " ";
	}
	cout << endl;
	cerr << "All tests succeeded" << endl;
	return (0);
}

int locateMaximum(const string array[], int n)
{
	if (n <= 0)
	{
		return (-1);
	}
	else
	{
		int index = 0;
		string max = array[0];
		for (int i = 0; i < n; i++)
		{
			if (array[i] > max)
			{
				index = i;
				max = array[i];
			}
		}
		return (index);
	}
}
bool hasNoDuplicates(const string array[], int n)
{
	if (n < 0)
	{
		return (false);
	}
	else if (n == 0)
	{
		return (true);
	}
	else
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = i + 1; j < n; j++)
			{
				if (array[j] == array[i])
				{
					return (false);
				}
			}
		}
		return (true);
	}
}
int countXPairs(const string array[], int n, int x)
{
	if (n <= 0)
	{
		return (-1);
	}
	else
	{
		int count = 0;
		for (int i = 0; i < n; i++)
		{
			for (int j = i + 1; j < n; j++)
			{
				int sum = std::stoi(array[i]) + std::stoi(array[j]);
				if (sum == x)
				{
					count++;
				}
			}
		}
		return (count);
	}
}
int findSecondToLastOccurrence(const string array[], int n, string target)
{
	if (n <= 0)
	{
		return (-1);
	}

	int index = -1;
	int nextIndex = -1;
	for (int i = 0; i < n; i++)
	{
		if (array[i] == target)
		{
			index = nextIndex;
			nextIndex = i;
		}
	}

	if (index == -1)
	{
		return (-1);
	}
	else
	{
		return (index);
	}
}
int countPunctuation(const string array[], int n)
{
	if (n <= 0)
	{
		return (-1);
	}
	else
	{
		int count = 0;
		for (int i = 0; i < n; i++)
		{
			for (size_t j = 0; j < array[i].length(); j++)
			{
				if (array[i].at(j) == '.' || array[i].at(j) == ',' || array[i].at(j) == '!' ||
					array[i].at(j) == ';' || array[i].at(j) == '\'' || array[i].at(j) == '-' ||
					array[i].at(j) == '/' || array[i].at(j) == ':' || array[i].at(j) == '?' ||
					array[i].at(j) == '"')
				{
					count++;
				}
			}
		}
		return (count);
	}
}
int flipAround(string array[], int n)
{
	int count = 0;
	for (int i = 0; i < n / 2; i++)
	{
		string temp = array[i];
		array[i] = array[n - 1 - i];
		array[n - 1 - i] = temp;
		count++;
	}
	return (count);
}
int moveToEnd(string array[], int n, int pos)
{
	if (n <= 0)
	{
		return (-1);
	}
	else if (pos < 0 || pos > n - 1)
	{
		return (-1);
	}
	else
	{
		string atPos = array[pos];
		for (int i = pos + 1; i < n; i++)
		{
			array[i - 1] = array[i];
		}
		array[n - 1] = atPos;
		return (pos);
	}
}
