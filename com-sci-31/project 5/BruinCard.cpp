#include <iostream>
#include <string>
using namespace std;

#include "Enums.h"
#include "MealPlan.h"
#include "BruinCard.h"

BruinCard::BruinCard()
{
	MealPlan m;
	mPlan = m;

	mBoughtAMealPlan = false;

	hasEatenBreakfast = false;
	hasEatenBrunch = false;
	hasEatenLunch = false;
	hasEatenDinner = false;

	howManyMealsLeft = 0;
}

void BruinCard::purchaseMealPlan(MealPlan plan)
{
	mPlan = MealPlan(plan);
}
bool BruinCard::hasPurchasedMealPlan()
{
	if (mPlan.getPlan() != UNDEFINED)
	{
		return (true);
	}
	else
	{
		return (false);
	}
}
plan BruinCard::getPlan()
{
	return (mPlan.getPlan());
}

bool BruinCard::eat(meal m)
{
	if (mPlan.getPlan() == REGULAR11 || mPlan.getPlan() == REGULAR14 || mPlan.getPlan() == REGULAR19)
	{
		if (m == BREAKFAST)
		{
			// check if that meal has already been eaten
			if (hasEatenBreakfast == true)
			{
				return (false);
			}
			else
			{
				hasEatenBreakfast = true;
				howManyMealsLeft--;
				return (true);
			}
		}
		else if (m == WEEKENDBRUNCH)
		{
			if (hasEatenBrunch == true)
			{
				return (false);
			}
			else
			{
				hasEatenBrunch = true;
				howManyMealsLeft--;
				return (true);
			}
		}
		else if (m == LUNCH)
		{
			if (hasEatenLunch == true)
			{
				return (false);
			}
			else
			{
				hasEatenLunch = true;
				howManyMealsLeft--;
				return (true);
			}
		}
		else if (m == DINNER)
		{
			if (hasEatenDinner == true)
			{
				return (false);
			}
			else
			{
				hasEatenDinner = true;
				howManyMealsLeft--;
				return (true);
			}
		}
		else
		{
			return (false);
		}
	}
	else if (mPlan.getPlan() == PREMIER11 || mPlan.getPlan() == PREMIER14 || mPlan.getPlan() == PREMIER19)
	{
		if (howManyMealsLeft > 0)
		{
			howManyMealsLeft--;
			return (true);
		}
		else
		{
			return (false);
		}
	}
	else
	{
		return (false);
	}
}

void BruinCard::startQuarter()
{
	if (mPlan.getPlan() == PREMIER11)
	{
		howManyMealsLeft = 11 * 11;
	}
	else if (mPlan.getPlan() == PREMIER14)
	{
		howManyMealsLeft = 11 * 14;
	}
	else if (mPlan.getPlan() == PREMIER19)
	{
		howManyMealsLeft = 11 * 19;
	}
	else
	{
		howManyMealsLeft = 0;
	}
}
void BruinCard::newWeek()
{
	if (mPlan.getPlan() == REGULAR11)
	{
		howManyMealsLeft = 11;
	}
	else if (mPlan.getPlan() == REGULAR14)
	{
		howManyMealsLeft = 14;
	}
	else if (mPlan.getPlan() == REGULAR19)
	{
		howManyMealsLeft = 19;
	}
}
void BruinCard::newDay()
{
	hasEatenBreakfast = false;
	hasEatenBrunch = false;
	hasEatenLunch = false;
	hasEatenDinner = false;
}
int BruinCard::mealsLeftThisWeek()
{
	return (howManyMealsLeft);
}
