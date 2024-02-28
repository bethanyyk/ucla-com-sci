#include <string>
using namespace std;

#include "Enums.h"

#ifndef MealPlan_h
#define MealPlan_h

class MealPlan
{
	private:
		plan mPlan;
	public:
		MealPlan();

		void pickPlan(plan p);
		plan getPlan();
		double cost();
		int mealsEachWeek();
		bool unusedMealsCarryOver();
};

#endif
