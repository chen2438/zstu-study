    class Ex4
    {
        static void Main(string[] args)
        {
            Write("请输入矩阵行数：");
            int row = int.Parse(ReadLine());
            Write("请输入矩阵列数：");
            int col = int.Parse(ReadLine());
            double[,] arr1 = new double[row, col];
            double[,] arr2 = new double[row, col];
            Random rd = new Random();
            for (int i = 0; i < row; i++)
            {
                for (int j = 0; j < col; j++)
                {
                    arr1[i, j] = rd.Next(10);
                    arr2[i, j] = rd.Next(10);
                }
            }

            Console.WriteLine("矩阵加法:");
            double[,] result = AddMatrix(arr1, arr2);
            for (int i = 0; i < result.GetLength(0); i++)
            {
                for (int j = 0; j < result.GetLength(1); j++)
                {
                    Console.Write($"{arr1[i, j],4}");
                }
                Console.Write("|\t");
                for (int j = 0; j < result.GetLength(1); j++)
                {
                    Console.Write($"{arr2[i, j],4}");
                }
                Console.Write("|" + "\t");
                for (int j = 0; j < result.GetLength(1); j++)
                {
                    Console.Write($"{result[i, j],4}");
                }
                Console.WriteLine();
            }
        }
        public static double[,] AddMatrix(double[,] a, double[,] b)
        {
            if (a.GetLength(0) != b.GetLength(0)
                || a.GetLength(1) != b.GetLength(1))
                return null;

            int n = a.GetLength(0);
            int m = a.GetLength(1);
            double[,] result = new double[n, m];
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < m; j++)
                {
                    result[i, j] = a[i, j] + b[i, j];
                }
            }
            return result;
        }
