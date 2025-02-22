package observerpattern;

import java.util.*;

public abstract class MySubject
{
	protected ArrayList observers = new ArrayList();
	
	//ע�᷽��
	public void attach(MyObserver observer)
	{
		observers.add(observer);
	} 
	
	//ע������
	public void detach(MyObserver observer)
	{
		observers.remove(observer);
	}
	
	public abstract void cry(); //����֪ͨ����
}