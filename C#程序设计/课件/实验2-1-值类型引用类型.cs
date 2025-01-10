    struct SomeVal { public int x; }
    class SomeRef { public int x; }
    class SomeRef2 { public SomeVal val; }
    struct SomeVal3 { public SomeRef rf; }
    class Program
    {
        public static void Main()
        {
            SomeVal v1; //��û�з���ռ䣿�����������/ջ�����У���ջ��       
            //Console.WriteLine(v1.x); //��������? ���ܣ���Ϊû�г�ʼ��      
            v1.x = 100; //��������?Ϊʲô���ܣ���Ϊ�ѷ���ռ�
            Console.WriteLine(v1.x); //��������?Ϊʲô���ܣ���Ϊ�ֶ��ѳ�ʼ��
            v1 = new SomeVal();//��û�з���ռ䣿�����������/ջ���� ͬǰ      
            Console.WriteLine(v1.x); //���: 0      
            v1.x = 5;
            Console.WriteLine(v1.x); //���: 5      

            SomeRef r1;//��û�з���ռ䣿�����������/ջ���� û��      
            //Console.WriteLine(r1.x); //��������? ���ܣ���Ϊû�з���ռ䣬Ҳû�г�ʼ��
            //r1.x = 100;
            //Console.WriteLine(r1.x); //��������? ���ܣ���Ϊû�з���ռ�
            r1 = new SomeRef();//��û�з���ռ䣿�����������/ջ���� �У��ڶ���      
            Console.WriteLine(r1.x); // ���: 0      
            r1.x = 5;
            Console.WriteLine(r1.x); // ���: 5      

            SomeVal v2 = v1;
            SomeRef r2 = r1;
            v1.x = 9;
            r1.x = 8;
            Console.WriteLine(r1.x); // ���: 8      
            Console.WriteLine(r2.x); // ���: 8      
            Console.WriteLine(v1.x); // ���: 9      
            Console.WriteLine(v2.x); // ���: 5      

            SomeRef2 sf2_1 = new SomeRef2();//sf2_1�ռ�����������/ջ������       
            SomeVal sv2_1 = sf2_1.val;//sv2_1�ռ�����������/ջ����ջ       
            SomeRef2 sf2_2 = new SomeRef2();
            SomeVal sv2_2 = sf2_2.val;
            Console.WriteLine($"������ʵ�������{sf2_1.Equals(sf2_2)}");// ���: False      
            Console.WriteLine($"�����ṹʵ�������{sv2_1.Equals(sv2_2)}");// ���: True      

            SomeVal3 sv3_1 = new SomeVal3();
            SomeVal3 sv3_2 = new SomeVal3();
            Console.WriteLine($"{sv3_1.rf == null} {sv3_2.rf == null}");// ���: True True      
            Console.WriteLine($"�����ṹʵ�������{sv3_1.Equals(sv3_2)}");// ���: True      
            sv3_1.rf = new SomeRef();
            sv3_2.rf = new SomeRef();
            Console.WriteLine($"������ʵ�������{sv3_1.rf.Equals(sv3_2.rf)}");// ���: False      
        }
    }
