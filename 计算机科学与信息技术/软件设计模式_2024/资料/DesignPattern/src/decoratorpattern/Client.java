package decoratorpattern;

public class Client
{
	public static void main(String args[])
	{
		Transform camaro;
		camaro = new Car();
		camaro.move();
		System.out.println("-----------------------------");
		
		Robot robot1 = new Robot(camaro);
		robot1.move();
		robot1.say();
		/*
		Airplane airplane1 = new Airplane(robot1);
		airplane1.move();
		airplane1.fly();
		*/
	}
}