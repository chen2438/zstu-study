package adapterpattern;

public class BirdAdapter extends Bird implements Robot
{
	public void cry()
	{
		System.out.print("������ģ�£�");
		super.tweedle();
	}
	
	public void move()
	{
		System.out.print("������ģ�£�");
		super.fly();
	}
}