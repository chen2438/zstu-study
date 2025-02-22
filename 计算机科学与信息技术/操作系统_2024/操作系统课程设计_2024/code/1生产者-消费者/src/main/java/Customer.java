import java.util.List;

class Customer implements Runnable {
    private static final int TIMES = 3;
    private final List<Integer> list;

    Customer(List<Integer> list) {
        this.list = list;
    }

    @Override
    public void run() {
        for (int i = 0; i < TIMES; i++) {
            synchronized (list) {
                while (list.isEmpty()) {
                    try {
                        System.out.println("消费者：" + Thread.currentThread().getName() + "\t仓库已空，进入阻塞状态");
                        list.wait();
                        System.out.println("消费者：" + Thread.currentThread().getName() + "\t被唤醒，退出阻塞状态");
                    } catch (Exception e) {
                        e.printStackTrace();
                    }
                }
                Integer removed = list.remove(0);
                System.out.println("消费者：" + Thread.currentThread().getName() + "\t购买的商品编号为：R" + removed);
                Controller.showList(list);
                list.notifyAll();
                try {
                    Thread.sleep(500);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        }
        System.out.println("消费者：" + Thread.currentThread().getName() + "\t消费结束，进程结束！");
    }
}
