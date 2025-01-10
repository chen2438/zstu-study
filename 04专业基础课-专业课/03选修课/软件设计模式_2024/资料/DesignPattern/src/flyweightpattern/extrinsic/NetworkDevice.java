package flyweightpattern.extrinsic;

public interface NetworkDevice
{
	public String getType();
	public void use(Port port);
}