import java.util.List;
import java.util.concurrent.ThreadLocalRandom;

class Producer implements Runnable {
    private static final ThreadLocalRandom RANDOM = ThreadLocalRandom.current();
    private static final int TIMES = 3;
    private final List<Integer> list;
    private final int MAX_SIZE;

    Producer(List<Integer> list, int size) {
        this.list = list;
        this.MAX_SIZE = size;
    }

    @Override
    public void run() {
        for (int i = 0; i < TIMES; i++) {
            synchronized (list) {
                while (list.size() == this.MAX_SIZE) {
                    try {
                        System.out.println("生产者：" + Thread.currentThread().getName() + "\t仓库已达最大容量，进入阻塞状态");
                        list.wait();
                        System.out.println("生产者：" + Thread.currentThread().getName() + "\t被唤醒，退出阻塞状态");
                    } catch (Exception e) {
                        e.printStackTrace();
                    }
                }
                int number = RANDOM.nextInt(8000);
                System.out.println("生产者：" + Thread.currentThread().getName() + "\t生产的产品编号为：R" + number);
                list.add(number);
                Controller.showList(list);
                list.notifyAll();
                try {
                    Thread.sleep(500);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        }
        System.out.println("生产者：" + Thread.currentThread().getName() + "\t停止生产，进程结束！");
    }
}