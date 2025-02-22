import java.util.LinkedList;
import java.util.List;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        System.out.println("=========================");
        Scanner scanner = new Scanner(System.in);
        System.out.print("请输入生产者数量（>=2）：");
        int producerNum = scanner.nextInt();
        System.out.print("请输入消费者数量（>=2）：");
        int customerNum = scanner.nextInt();
        System.out.print("请输入缓存区大小：");
        int capacity = scanner.nextInt();
        System.out.println("=========================");
        List<Integer> list = new LinkedList<>();

        for (int i = 0; i < producerNum; i++) {
            Thread producerThread = new Thread(new Producer(list, capacity));
            producerThread.start();
        }

        for (int i = 0; i < customerNum; i++) {
            Thread customerThread = new Thread(new Customer(list));
            customerThread.start();
        }
    }
}