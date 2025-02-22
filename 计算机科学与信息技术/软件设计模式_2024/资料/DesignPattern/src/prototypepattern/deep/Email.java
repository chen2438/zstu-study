package prototypepattern.deep;

import java.io.*;

public class Email implements Serializable 
{
	private Attachment attachment=null;
	
	public Email()
	{
		this.attachment = new Attachment();
	}
	
	public Object deepClone() throws IOException, ClassNotFoundException, OptionalDataException
	{
		ByteArrayOutputStream bao = new ByteArrayOutputStream();
		ObjectOutputStream oos = new ObjectOutputStream(bao);
		oos.writeObject(this);
		
		ByteArrayInputStream bis = new ByteArrayInputStream(bao.toByteArray());
		ObjectInputStream ois = new ObjectInputStream(bis);
		return(ois.readObject());
	}
	
	public Attachment getAttachment()
	{
		return this.attachment;
	}
	
	public void display()
	{
		System.out.println("²é¿´ÓÊ¼þ");	
	}
	
}