#include <iostream>
#include <string>
using namespace std;

#include "Enums.h"
#include "MealPlan.h"

MealPlan::MealPlan()
{
	mPlan = UNDEFINED;
}

void MealPlan::pickPlan(plan p)
{
	mPlan = p;
}

plan MealPlan::getPlan()
{
	return mPlan;
}

double MealPlan::cost()
{
	if (mPlan == 1)
	{
		return (4646.64);
	}
	else if (mPlan == 2)
	{
		return (5018.28);
	}
	else if (mPlan == 3)
	{
		return (5107.20);
	}
	else if (mPlan == 4)
	{
		return (5570.04);
	}
	else if (mPlan == 5)
	{
		return (5278.20);
	}
	else if (mPlan == 6)
	{
		return (5898.20);
	}
	else
	{
		return (0);
	}
}

int MealPlan::mealsEachWeek()
{
	if (mPlan == 1 || mPlan == 2)
	{
		return (11);
	}
	else if (mPlan == 3 || mPlan == 4)
	{
		return (14);
	}
	else if (mPlan == 5 || mPlan == 6)
	{
		return (19);
	}
	else
	{
		return (0);
	}
}

bool MealPlan::unusedMealsCarryOver()
{
	if (mPlan == 1 || mPlan == 3 || mPlan == 5)
	{
		return (false);
	}
	else if (mPlan == 2 || mPlan == 4 || mPlan == 6)
	{
		return (true);
	}
	else
	{
		return (false);
	}
}
