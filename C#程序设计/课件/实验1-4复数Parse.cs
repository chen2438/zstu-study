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
            s.Trim();//��ͷβ���ܵĿո�ȥ��

            //�鲿�Ƿ�Ϊ��
            bool negativeImage = false;
            s = s.ToUpper();
            int pos = s.IndexOf('+');//�鲿��+/-���ŵ�λ��
            if (pos < 0)//���û������
            {
                pos = s.IndexOf('-');
                if (pos >= 0)//����и��Ų��Ҳ��ǵ�һ��
                    negativeImage = true;
            }

            //����I��λ��
            int iPos = s.IndexOf('I');
            if (iPos < 0)//���û��I��˵������ʵ��
            {
                if (pos > 0)//�ӺŲ��ǵ�һ��������û���鲿��˵���д���
                    return false;
                else
                    return double.TryParse(s, out real);//������ʵ��������
            }
            else//�����I��˵�����鲿����ֱ������������
            {
                if (pos > 0)//�����ʵ��
                {
                    string s1 = s.Substring(0, pos);
                    if (!double.TryParse(s1, out real))//�Ƚ�����ʵ��
                        return false;
                }

                string s2 = null;
                if (pos < 0)//�鲿û���������Ŵ���
                {
                    s2 = s.Substring(0, iPos - pos - 1);
                    return double.TryParse(s2, out image);
                }
                else
                {
                    s2 = s.Substring(pos+1, iPos - pos - 1);
                    if (!double.TryParse(s2, out image))//�ٽ������鲿
                        return false;

                    image = negativeImage ? -image : image;
                    return true;
                }
            }
        }
