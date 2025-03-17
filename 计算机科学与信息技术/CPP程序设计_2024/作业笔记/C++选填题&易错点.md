# C++题目集

## 选填易错题

### 1.switch-case题目

下列程序的运行结果是（）。

```c++
int i;
for(i=0;i<3;i++)
   switch(i)
   {
        case 1:cout<<i;
        case 2:cout<<i;
        default:cout<<i;
   }
```

A.

012

B.

012020

C.

011122

D.

120

**答案**

输出结果：011122

进入for循环
当i为0时，进入switch语句，不等以1和2，所以执行default语句，输出0；

i自增1，为1，进入switch语句，等于1，所以执行case 1语句，输出1，但是case 1语句后没有break语句，所以还要执行case 2语句以及default语句，分别输出一个1，这一次总共输出3个1

i自增1，为2，进入switch语句，等于2，所以执行case 2语句，输出2，但是case 2后也没有break语句，所以还要执行default语句，又输出一个2。

所以最后结果就是011122



### 2.cout字符

分析以下程序：程序的输出结果是

```c++
#include <iostream>
using namespace std;
void fun(int num)
{
    cout << num << endl;
}
void fun(char ch)
{
    cout << (ch + 1) << endl;
}
int main()
{
    fun('A');
    return 0;
}
```

A.

65

B.

66

C.

A

D.

B

**答案**

B.66

输出为ascll码



### 3.detele函数

以下程序存在的问题是：

```
void fun()
{
 int *num1, *num2;
 num1 = new int[10];
 num2 = new int[20];
 num1[0] = 100;
 num2[0] = 300;
 num1 = num2;
 delete [] num1;
}
```

A.

num2不能给num1赋值

B.

num2最初指向的空间没有释放

C.

num1最初指向的空间没有释放

D.

程序没有问题

错选：A

正确答案：C



### 4.引用（1）

下列关于引用的说法，错误的是____。

A.

引用在定义时必须初始化

B.

引用在初始化时不能绑定常量值

C.

引用初始化后，可以通过更变来引用其他变量

D.

数组不能定义引用



错选：B

正确答案：C



### 5.引用（2）



下列哪一个说法是不正确的?

A.

某个变量的引用等价于这个变量,相当于该变量的一个别名

B.

定义引用时一定要将其初始化成引用某个变量

C.

初始化后,它就一直引用该变量不会再别引用别的变量了

D.

引用可以引用变量,也可以引用常量和表达式



错选：B

正确答案：D



### 6.引用代码

下列代码能正确执行的是（ ）

A.

```c++
char a='C';
const char* const p=&a;
```

B.

```c++
char a='C';
char* const p;
p=&a;
```

C.

```c++
char* p=&'C';
```

D.

```c++
char& p='C';
```



错选：C

正确答案：A







## 知识点

### 1.int a(10)

```c++
int a(10);	//int a=10;
while(--a)
{
     if(a==8)  break;
     if(a%2==0&&a%3==0)  continue;
     cout<<a<<endl;
 }
```

### 2.C++ 非常量引用的初始值必须是左值

- 左值和右值：

  在C++中，左值可以出现在赋值语句的左边和右边；右值只能出现在赋值语句的右边，不能出现在赋值语句的左边。**变量是左值，常量是右值**。

- 根本原因是什么？

**只允许将常量传递给常量引用，如果将常量传递给非常量引用，我们就有可能通过引用去修改常量。这显然是不能被允许的。**

而 `SqList*const & L`意味着声明了一个SqList指针类型的引用，而const在*后面，修饰&L，即&L不可改变，也就是不可以通过L修改它引用的内容。所以此时可以传递常量给它。

BTW，`const SqList*&L`以及 `SqList const*&L`中，const在*的前面，意味着const修饰的是 *&L，即 *&L的内容不可改变，也就是L引用的指针所指向的值不可改变。

同理。`SqList*const L`中，const是对L的修饰，意味着指针L的值不可改变，即L的指向不可改变。

`const SqList* L`中，const是对*L的修饰，意味着 *L的值不可改变，即L指向的内容的值不可改变。



### 3.返回数据类型

```c++
#include <iostream>
#include <typeinfo>
using namespace std;

int main()
{
    int* p;
    p = new int;
    cout << typeid(p).name();
    return 0;
}
```



### 4.字符串的类型区别



```cpp
#define _CRT_SECURE_NO_WARNINGS  1
#include <iostream>
using namespace std;

int main() {
    const char* s = "abcdf";
    char* d;
    cout << sizeof(s) << endl;	//8
    cout << sizeof(d) << endl;	//8
    cout << sizeof(*s) << endl;	//1
    cout << strlen(s) << endl;	//4
    return 0;
}
```

**在声明p指针指向char数组的时候 前面要加const 不然就会报错**

翻阅c++ primer plus（第六版 page112~113）是这样解释的：

总结成一句话就是：**字符串字面值是常量，以这种方式使用const意味着可以用p来访问字符串，但不能修改它**

详细解释：

对于输入而言使用数组名和指针是一样的。

但对于输入却情况不同：

只要输入比较短，能够被存储在数组中，则直接将值存在数组中将是安全的，使用指针输入值并不合适（对应我的代码就是直接将“laylay”这个值的地址传给指针是不行的）

原因：

-   有些编译器将字符串字面值视为只读常量，如果试图修改它们，将导致运行阶段错误。在C++中，字符串字面值都将被视为常量，但并不是所有的编译器都对以前的行为做了这样的修改。
-   有些编译器只使用字符串字面值的一个副本来表示程序中所有的该字面值。  
    下面讨论一下第二点。C++不能保证字符串字面值被唯一地存储。也就是说，如果在程序中多次使用字符串字面值“laylay”，则编译器将可能存储该字符串的多个副本，也可能只存储一个副本。如果是后面一种情况，则将p设置为指向一个“laylay”，将使它只是指向该字符串的唯一一个副本。将值读入一个字符串可能会影响被认为是独立的、位于其他地方的字符串。无论如何，由于p指被声明为const，因此编译器将禁止改变p指向的位置中的内容。



### 5.指针赋值



```c++
#define _CRT_SECURE_NO_WARNINGS  1
#include <iostream>
using namespace std;


int main() {
    int* p[6];
    for (int i = 0; i < 6; i++) {
        //*p[i] = i; //错误code，*p不能输入值
        p[i] = &i;
        cout << *p[i] << endl;//这样输出的才是正确的数值
        cout << p[i] << endl;//但输出的地址都是一样的，因为输入的都是变量i的地址
    }
    return 0;
}


```

在您的代码中，您创建了一个整型指针数组 `p`，其大小为 6。然后，在循环中，您试图将循环变量 `i` 的地址赋值给每个指针 `p[i]`。然而，您所观察到的是所有指针似乎指向同一个地址。

**问题在于，您实际上是在将循环变量 `i` 的地址赋给每个指针。在每次循环迭代中，`i` 是在栈上的一个变量，并且每次迭代时它都占用栈上的同一个位置**（除非编译器进行了优化，但这通常不会发生，特别是在调试模式下）。因此，`&i` 在每次迭代中给出的地址实际上是相同的地址，即当前循环变量 `i` 在栈上的地址。

此外，当循环结束后，尝试访问 `i` 的地址是不安全的，因为 `i` 已经不再处于其作用域内。这意味着 `p` 数组中的指针现在指向了一个不再有效的内存位置。

如果您想要每个指针指向一个不同的整数值，您应该动态分配内存或使用一个已经存在的整型数组来存储这些值，并让指针指向这些值。例如：

```cpp
#include <iostream>  
using namespace std;  
  
int main() {  
    int values[6]; // 一个整型数组  
    int* p[6];     // 一个整型指针数组  
    for (int i = 0; i < 6; i++) {  
        values[i] = i; // 将值赋给数组中的元素  
        p[i] = &values[i]; // 让指针指向数组中的元素  
        cout << p[i] << " -> " << *p[i] << endl; // 输出指针的地址和指向的值  
    }  
  
    return 0;  
}
```

在这个修正后的代码中，`values` 数组包含了六个整数，每个整数由 `p` 数组中的一个指针指向。这样，每个指针就会指向一个不同的内存地址，并且这些地址中存储着不同的整数值。











# 答题



1.代码中`exPtr`和`exRef`分别是什么类型？

exPtr是指针类型，exRef是引用类型



2.`modifyByPointer`函数和`modifyByReference`函数分别是如何修改对象`ex`的值的？

modifyByPointer：通过指针调用Example类的成员函数setValue，修改指针ex的值

modifyByReference：通过地址引用调用Example类的成员函数setValue，修改ex的值

3.程序的输出是什么？

Value: 20

Value: 30





解答：

1.如果取消注释`Derived`类中的`display`函数，会发生什么？

发生编译错误，final修饰的函数不允许。



2.`using Base::show;`在`Derived`类中有什么作用？

调用base中的虚函数show



3.程序的输出是什么？

"Derived show"

"Base display"







解答：

1. `ShapeManager`类中的静态成员变量`shapeCount`和`shapes`的作用是什么？

   shapeCount：作为vector向量容器的栈顶下标，记录入栈的shape的子类个数

   shapes：作为存放Shapes的容器vector，被用于存放成员函数addShape中的shape子类参数。

2. `Shape`类中的`draw`函数为什么要声明为虚函数？
   便于继承Shape类的Circle和Square重写并避免重复构造调用Shape构造函数

3. 程序的输出是什么？
   Total shapes: 2

   Drawing Circle
   Drawing Square







解答：



1. `Container`类模板的作用是什么？

   简化intContainer和stringContainer的类定义过程，便于书写

2. `auto`关键字在`display`函数中的作用是什么？
   自动判别接受的参数类型，使多种类型的参数都能够调用函数

3. 程序的输出是什么？

   1 2 3

   Hello world





解答：

1. `FileException`类的作用是什么？
   作为异常类，传递文件报错信息，且能正确通过编译，并在调用FileException类时终止程序运行
2. `writeFile`函数和`readFile`函数中如何处理文件操作异常？
   用ofstream流和ifstream流读写文件，当无法正常读写时，用throw抛出异常类FileException，停止读写
3. 程序的输出是什么？

Hello, World!

This is a test file.





解答：



Copy

```cpp
#include <iostream>
#include <string>
using namespace std;

class Book {
public:
    // 带缺省参数的构造函数
    Book(const string& title = "Unknown", const string& author = "Unknown", double price = 0.0) 
        : title(title), author(author), price(price) {
        bookCount++;
    }

    // 普通成员函数
    void display() const {
        cout << "Title: " << title << ", Author: " << author << ", Price: $" << price << endl;
    }

    void setPrice(double newPrice) {
        price = newPrice;
    }

    // 静态成员函数
    static int getBookCount() {
        return bookCount;
    }

private:
    string title;
    string author;
    double price;
    static int bookCount; // 静态成员变量
};

// 静态成员变量初始化
int Book::bookCount = 0;

int main() {
    // 创建Book对象
    Book book1;
    Book book2("1984", "George Orwell", 9.99);
    Book book3("To Kill a Mockingbird", "Harper Lee", 12.99);

    // 显示书籍信息
    book1.display();
    book2.display();
    book3.display();

    // 设置并显示新的价格
    book1.setPrice(5.99);
    book1.display();

    // 输出当前Book对象的数量
    cout << "Total number of books: " << Book::getBookCount() << endl;

    return 0;
}
```



1. 请补全上述代码中的`Book`类定义。
2. 请在`main`函数中创建多个`Book`对象，调用相关成员函数，并输出书籍信息和当前`Book`对象的数量。



解答

```cpp
#include <iostream>
#include <string>
using namespace std;

// 基类 Shape
class Shape {
public:
    // 带有虚函数的基类
    virtual void draw() const = 0;  // 纯虚函数
    virtual ~Shape() {}  // 虚析构函数
};

// 派生类 Circle
class Circle : public Shape {
public:
    Circle(double radius) : radius(radius) {}
    
    void draw() const override {
        cout << "Drawing a circle with radius: " << radius << endl;
    }
private:
    double radius;
};

// 派生类 Rectangle
class Rectangle : public Shape {
public:
    Rectangle(double width, double height) : width(width), height(height) {}
    
    void draw() const override {
        cout << "Drawing a rectangle with width: " << width << " and height: " << height << endl;
    }
private:
    double width;
    double height;
};

// 非派生类 Drawing
class Drawing {
public:
    Drawing(Shape* shape) : shape(shape) {}
    
    void drawShape() const {
        shape->draw();
    }
    
    ~Drawing() {
        delete shape;
    }
private:
    Shape* shape;
};

int main() {
    // 创建 Circle 对象
    Shape* circle = new Circle(5.0);
    // 创建 Drawing 对象并传递 Circle 对象
    Drawing drawing1(circle);
    drawing1.drawShape();  // 输出：Drawing a circle with radius: 5.0
    
    // 创建 Rectangle 对象
    Shape* rectangle = new Rectangle(4.0, 6.0);
    // 创建 Drawing 对象并传递 Rectangle 对象
    Drawing drawing2(rectangle);
    drawing2.drawShape();  // 输出：Drawing a rectangle with width: 4.0 and height: 6.0
    
    return 0;
}
```





```cpp
#include <iostream>
using namespace std;

class Vector {
public:
    // 默认构造函数
    Vector() : x(0), y(0) {}

    // 带参数的构造函数
    Vector(double x, double y) : x(x), y(y) {}

    // 重载加法运算符
    Vector operator+(const Vector& other) const {
        return Vector(x + other.x, y + other.y);
    }

    // 重载减法运算符
    Vector operator-(const Vector& other) const {
        return Vector(x - other.x, y - other.y);
    }

    // 重载乘法运算符
    Vector operator*(double scalar) const {
        return Vector(x * scalar, y * scalar);
    }

    // 重载插入运算符
    friend ostream& operator<<(ostream& os, const Vector& vec) {
        os << "Vector(" << vec.x << ", " << vec.y << ")";
        return os;
    }

    // 重载下标运算符
    double& operator[](int index) {
        if (index == 0) return x;
        if (index == 1) return y;
        throw out_of_range("Index out of range");
    }

    // 显示向量信息
    void display() const {
        cout << "Vector(" << x << ", " << y << ")" << endl;
    }

private:
    double x, y;
};

int main() {
    // 创建 Vector 对象
    Vector v1(3.0, 4.0);
    Vector v2(1.0, 2.0);

    // 显示向量信息
    cout << "v1: " << v1 << endl;
    cout << "v2: " << v2 << endl;

    // 向量加法
    Vector v3 = v1 + v2;
    cout << "v1 + v2: " << v3 << endl;

    // 向量减法
    Vector v4 = v1 - v2;
    cout << "v1 - v2: " << v4 << endl;

    // 向量与标量乘法
    Vector v5 = v1 * 2.0;
    cout << "v1 * 2.0: " << v5 << endl;

    // 使用下标运算符
    cout << "v1[0]: " << v1[0] << endl;
    cout << "v1[1]: " << v1[1] << endl;

    // 显示所有向量信息
    v1.display();
    v2.display();
    v3.display();
    v4.display();
    v5.display();

    return 0;
}
```

