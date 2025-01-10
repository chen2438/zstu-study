package bridgepattern;

public class Client
{
	public static void main(String a[])
	{
		Pen pen;
		Color color;
	
		pen = (Pen)XMLUtilPen.getBean("pen");
		color = (Color)XMLUtilPen.getBean("color");
		
		pen.setColor(color);
		pen.draw("œ ª®");
	}
}