package builderpattern;

public class Client
{
	public static void main(String args[])
	{
	    MealBuilder mb = (MealBuilder)XMLUtil.getBean();
		KFCWaiter waiter = new KFCWaiter();
	    waiter.setMealBuilder(mb);
	    Meal meal = waiter.construct();
        
        System.out.println("�ײ���ɣ�");
        System.out.println(meal.getFood());
        System.out.println(meal.getDrink());
	}
}