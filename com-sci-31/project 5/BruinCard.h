#ifndef BruinCard_h
#define BruinCard_h

#include "MealPlan.h"

class BruinCard
{
	private:
		MealPlan mPlan;
		bool mBoughtAMealPlan;

		bool hasEatenBreakfast;
		bool hasEatenLunch;
		bool hasEatenDinner;
		bool hasEatenBrunch;

		int howManyMealsLeft;

	public:
		BruinCard();

		void purchaseMealPlan(MealPlan plan);
		bool hasPurchasedMealPlan();
		plan getPlan();

		bool eat(meal m);

		void startQuarter();
		void newWeek();
		void newDay();
		int mealsLeftThisWeek();
};

#endif
