    class Program
    {
        static void Main(string[] args)
        {
            double real, image;
            bool ok = TryParse("2", out real, out image);
            Console.WriteLine($"{ok} - {real} : {image}");
            ok = TryParse("-2", out real, out image);
            Console.WriteLine($"{ok} - {real} : {image}");
            ok = TryParse("3i", out real, out image);
            Console.WriteLine($"{ok} - {real} : {image}");
            ok = TryParse("-3i", out real, out image);
            Console.WriteLine($"{ok} - {real} : {image}");
            ok = TryParse("2+3i", out real, out image);
            Console.WriteLine($"{ok} - {real} : {image}");
            ok = TryParse("2-3i", out real, out image);
            Console.WriteLine($"{ok} - {real} : {image}");
        }
        public static bool TryParse(string s, out double real, out double image)
        {
            real = 0;
            image = 0;
            if (s == null)
                return false;
            s.Trim();//把头尾可能的空格去掉

            //虚部是否为负
            bool negativeImage = false;
            s = s.ToUpper();
            int pos = s.IndexOf('+');//虚部的+/-符号的位置
            if (pos < 0)//如果没有正号
            {
                pos = s.IndexOf('-');
                if (pos >= 0)//如果有负号并且不是第一个
                    negativeImage = true;
            }

            //符号I的位置
            int iPos = s.IndexOf('I');
            if (iPos < 0)//如果没有I，说明仅有实部
            {
                if (pos > 0)//加号不是第一个，但又没有虚部，说明有错误
                    return false;
                else
                    return double.TryParse(s, out real);//解析出实部并返回
            }
            else//如果有I，说明有虚部，则分别解析两个部分
            {
                if (pos > 0)//如果有实部
                {
                    string s1 = s.Substring(0, pos);
                    if (!double.TryParse(s1, out real))//先解析出实部
                        return false;
                }

                string s2 = null;
                if (pos < 0)//虚部没有正负符号存在
                {
                    s2 = s.Substring(0, iPos - pos - 1);
                    return double.TryParse(s2, out image);
                }
                else
                {
                    s2 = s.Substring(pos+1, iPos - pos - 1);
                    if (!double.TryParse(s2, out image))//再解析出虚部
                        return false;

                    image = negativeImage ? -image : image;
                    return true;
                }
            }
        }
