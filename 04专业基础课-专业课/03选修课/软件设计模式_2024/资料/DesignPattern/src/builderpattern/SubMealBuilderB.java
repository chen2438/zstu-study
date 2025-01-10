package builderpattern;

public class SubMealBuilderB extends MealBuilder
{
	public void buildFood()
	{
		meal.setFood("Ò»¸ö¼¦Èâ¾í");
	}
	
	public void buildDrink()
	{
		meal.setDrink("Ò»±­Ñ©±Ì");
	}
}