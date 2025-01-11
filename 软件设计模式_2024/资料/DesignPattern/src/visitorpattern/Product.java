package visitorpattern;

public interface Product
{
	void accept(Visitor visitor);
}