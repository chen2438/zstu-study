package proxypattern;

public class RealPermission implements AbstractPermission
{	
	public void modifyUserInfo()
	{
		System.out.println("�޸��û���Ϣ��");
	}

	public void viewNote()
	{   
		System.out.println("�鿴���ӣ�");
	}
	
	public void publishNote()
	{
		System.out.println("����������");
	}
	
	public void modifyNote()
	{
		System.out.println("�޸ķ������ݣ�");
	}
	
	public void setLevel(int level)
	{	
	}
}