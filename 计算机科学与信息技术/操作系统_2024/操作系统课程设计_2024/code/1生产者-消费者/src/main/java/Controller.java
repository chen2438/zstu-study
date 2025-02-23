import java.util.List;

public class Controller {
    public static void showList(List<Integer> list) {
        System.out.println("=============== 缓冲区情况 =============");
        for (int i = 0; i < list.size(); i++) {
            System.out.println("当前指针位置：" + i + " -------- " + "对应商品编号：R" + list.get(i));
        }
        System.out.println("======================================\n");
    }
}