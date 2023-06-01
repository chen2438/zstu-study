    struct SomeVal { public int x; }
    class SomeRef { public int x; }
    class SomeRef2 { public SomeVal val; }
    struct SomeVal3 { public SomeRef rf; }
    class Program
    {
        public static void Main()
        {
            SomeVal v1; //有没有分配空间？分配在哪里（堆/栈）？有，在栈里       
            //Console.WriteLine(v1.x); //能运行吗? 不能，因为没有初始化      
            v1.x = 100; //能运行吗?为什么？能，因为已分配空间
            Console.WriteLine(v1.x); //能运行吗?为什么？能，因为字段已初始化
            v1 = new SomeVal();//有没有分配空间？分配在哪里（堆/栈）？ 同前      
            Console.WriteLine(v1.x); //输出: 0      
            v1.x = 5;
            Console.WriteLine(v1.x); //输出: 5      

            SomeRef r1;//有没有分配空间？分配在哪里（堆/栈）？ 没有      
            //Console.WriteLine(r1.x); //能运行吗? 不能，因为没有分配空间，也没有初始化
            //r1.x = 100;
            //Console.WriteLine(r1.x); //能运行吗? 不能，因为没有分配空间
            r1 = new SomeRef();//有没有分配空间？分配在哪里（堆/栈）？ 有，在堆里      
            Console.WriteLine(r1.x); // 输出: 0      
            r1.x = 5;
            Console.WriteLine(r1.x); // 输出: 5      

            SomeVal v2 = v1;
            SomeRef r2 = r1;
            v1.x = 9;
            r1.x = 8;
            Console.WriteLine(r1.x); // 输出: 8      
            Console.WriteLine(r2.x); // 输出: 8      
            Console.WriteLine(v1.x); // 输出: 9      
            Console.WriteLine(v2.x); // 输出: 5      

            SomeRef2 sf2_1 = new SomeRef2();//sf2_1空间分配在哪里（堆/栈）？堆       
            SomeVal sv2_1 = sf2_1.val;//sv2_1空间分配在哪里（堆/栈）？栈       
            SomeRef2 sf2_2 = new SomeRef2();
            SomeVal sv2_2 = sf2_2.val;
            Console.WriteLine($"两个类实例相等吗？{sf2_1.Equals(sf2_2)}");// 输出: False      
            Console.WriteLine($"两个结构实例相等吗？{sv2_1.Equals(sv2_2)}");// 输出: True      

            SomeVal3 sv3_1 = new SomeVal3();
            SomeVal3 sv3_2 = new SomeVal3();
            Console.WriteLine($"{sv3_1.rf == null} {sv3_2.rf == null}");// 输出: True True      
            Console.WriteLine($"两个结构实例相等吗？{sv3_1.Equals(sv3_2)}");// 输出: True      
            sv3_1.rf = new SomeRef();
            sv3_2.rf = new SomeRef();
            Console.WriteLine($"两个类实例相等吗？{sv3_1.rf.Equals(sv3_2.rf)}");// 输出: False      
        }
    }
