    class MeanTool
    {
        public static double Mean(double a, double b, double c)
        {
            return (a + b + c) / 3;
        }
        public static void Mean(double a, double b, double c,
            ref double max, ref double min, ref double average)
        {
            max = min = a;
            max = (max > b) ? max : b;
            min = (min < b) ? min : b;
            max = (max > c) ? max : c;
            min = (min < c) ? min : c;
            average = (a + b + c) / 3;
        }
        public static void Mean2(double a, double b, double c,
            out double max, out double min, out double average)
        {
            max = min = a;
            max = (max > b) ? max : b;
            min = (min < b) ? min : b;
            max = (max > c) ? max : c;
            min = (min < c) ? min : c;
            average = (a + b + c) / 3;
        }
        public static (double, double, double) Mean(params double[] numbers)
        {
            double max = 0;
            double min = 0;
            double average = 0;
            if (numbers.Length == 0)
                return (0, 0, 0);

            max = numbers[0];
            min = numbers[0];
            double sum = numbers[0];
            for (int i = 1; i < numbers.Length; i++)
            {
                if (numbers[i] > max)
                    max = numbers[i];
                if (numbers[i] < min)
                    min = numbers[i];
                sum += numbers[i];
            }
            average = sum / numbers.Length;
            return (max, min, average);
        }
    }
    class Ex3
    {
        public static void Main()
        {
            double max = 2, min = 3, average = 4;
            Console.WriteLine($"函数1：(2, 3, 4) -> {MeanTool.Mean(max, min, average)}");

            Console.Write("函数2：");
            MeanTool.Mean(2, 3, 4, ref max, ref min, ref average);
            Console.WriteLine($"(2, 3, 4) -> ({max}, {min}, {average})");

            Console.Write("函数3：");
            MeanTool.Mean2(12, 3, 9, out max, out min, out average);
            Console.WriteLine($"(12, 3, 9) -> ({max}, {min}, {average})");

            Console.Write("函数4：");
            (max, min, average) = MeanTool.Mean(2, 3, 4, 5, 6);
            Console.WriteLine($"(2, 3, 4, 5, 6) -> ({max}, {min}, {average})");
        }
    }
