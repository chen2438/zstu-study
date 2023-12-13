// 定义接口 Component
public interface IScore
{
    void Report();
}

// ConcreteComponent
public class Score : IScore
{
    private int value;

    public Score(int value)
    {
        this.value = value;
    }

    public void Report()
    {
        Console.WriteLine($"成绩是：{value}分");
    }
}

// 装饰器基类 Decorator
public abstract class ScoreDecorator : IScore
{
    protected IScore wrappedScore;

    public ScoreDecorator(IScore score)
    {
        wrappedScore = score;
    }

    public virtual void Report()
    {
        wrappedScore.Report();
    }
}

// ConcreteDecorator 前装饰器，比上次考试增加了分数
public class ImprovedScoreDecorator : ScoreDecorator
{
    private int improvement;

    public ImprovedScoreDecorator(IScore score, int improvement) : base(score)
    {
        this.improvement = improvement;
    }

    public override void Report()
    {
        Console.WriteLine($"比上次考试增加了{improvement}分。");
        base.Report();
    }
}

// ConcreteDecorator 前装饰器，最高分比自己的分数高一点点
public class CloseToTopScoreDecorator : ScoreDecorator
{
    public CloseToTopScoreDecorator(IScore score) : base(score)
    {
    }

    public override void Report()
    {
        // 假设最高分是100分
        Console.WriteLine($"这次考试最高成绩比自己的成绩只高一点。");
        base.Report();
    }
}

// ConcreteDecorator 后装饰器，班级排名前列
public class HighRankScoreDecorator : ScoreDecorator
{
    public HighRankScoreDecorator(IScore score) : base(score)
    {
    }

    public override void Report()
    {
        base.Report();
        Console.WriteLine("这次考试班级排名前列。");
    }
}

// 客户端代码
class Program
{
    static void Main(string[] args)
    {
        IScore score = new Score(65); // 原始成绩
        
        // 加装饰器
        score = new ImprovedScoreDecorator(score, 5); // 增加了5分
        score = new CloseToTopScoreDecorator(score);  // 最高分比自己的高一点点
        score = new HighRankScoreDecorator(score);    // 班级排名前列

        score.Report(); // 输出装饰后的成绩报告
    }
}
