#include <iostream>
#include <string>
using namespace std;

int main() {
	// Declaring variables
	string movie;
	string temp; // Used to evaluate what value the variables should contain for yes/no questions
	int theme;
	double actor;
	int taste;
	double thumbsUp;
	double thumbsDown;

	cout << "What movie is to be rated? ";
	getline(cin, movie);
	cout << "On a scale of 1-10, how much do you like movies with a similar theme? ";
	cin >> theme;
	cin.ignore(10000, '\n');
	if (theme < 1 || theme > 10)
	{
		cout << "Invalid theme value!";
		return(1);
	}
	cout << "Do you like movies starring the actor or actress that stars in this movie? ";
	getline(cin, temp);
	if (temp != "Yes" && temp != "No")
	{
		cout << "Invalid actor value!";
		return(1);
	}
	else if (temp == "Yes")
	{
		actor = 2.0;
	}
	else
	{
		actor = 0.0;
	}
	cout << "On a scale of 1-10, how much do users with tastes similar to yours like this movie? ";
	cin >> taste;
	cin.ignore(10000, '\n');
	if (taste < 1 || taste > 10)
	{
		cout << "Invalid taste value!";
		return(1);
	}
	cout << "Have you thumbed up this movie already? ";
	getline(cin, temp);
	if (temp != "Yes" && temp != "No")
	{
		cout << "Invalid thumbed up value!";
		return(1);
	}
	else if (temp == "Yes")
	{
		thumbsUp = 2.0;
	}
	else
	{
		thumbsUp = 0.0;
	}
	cout << "Have you thumbed down this movie already? ";
	getline(cin, temp);
	if (temp != "Yes" && temp != "No")
	{
		cout << "Invalid thumbed down value!";
		return(1);
	}
	else if (temp == "Yes")
	{
		thumbsDown = -2.0;
	}
	else
	{
		thumbsDown = 0.0;
	}

	// Calculating recommendation value
	double recommendation = (0.3 * theme) + actor + (0.3 * taste) + thumbsUp + thumbsDown;
	// Magic Formula: Makes C++ print to 1 decimal value
	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout.precision(1);
	// Printing out recommendation value
	cout << "Our recommendation for you for the movie: " << movie << " is " << recommendation;
	return(0);
}