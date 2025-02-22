#include <iostream>
#include <memory>

// 定义接口 Component
class IScore {
public:
    virtual void Report() = 0;
    virtual ~IScore() = default;
};

// ConcreteComponent
class Score : public IScore {
private:
    int value;

public:
    Score(int value) : value(value) {}

    void Report() override {
        std::cout << "成绩是：" << value << "分" << std::endl;
    }
};

// 装饰器基类 Decorator
class ScoreDecorator : public IScore {
protected:
    std::shared_ptr<IScore> wrappedScore;

public:
    ScoreDecorator(std::shared_ptr<IScore> score) : wrappedScore(score) {}

    void Report() override {
        wrappedScore->Report();
    }
};

// ConcreteDecorator 前装饰器，比上次考试增加了分数
class ImprovedScoreDecorator : public ScoreDecorator {
private:
    int improvement;

public:
    ImprovedScoreDecorator(std::shared_ptr<IScore> score, int improvement)
        : ScoreDecorator(score), improvement(improvement) {}

    void Report() override {
        std::cout << "比上次考试增加了" << improvement << "分。" << std::endl;
        ScoreDecorator::Report();
    }
};

// ConcreteDecorator 前装饰器，最高分比自己的分数高一点点
class CloseToTopScoreDecorator : public ScoreDecorator {
public:
    CloseToTopScoreDecorator(std::shared_ptr<IScore> score)
        : ScoreDecorator(score) {}

    void Report() override {
        // 假设最高分是100分
        std::cout << "这次考试最高成绩比自己的成绩只高一点。" << std::endl;
        ScoreDecorator::Report();
    }
};

// ConcreteDecorator 后装饰器，班级排名前列
class HighRankScoreDecorator : public ScoreDecorator {
public:
    HighRankScoreDecorator(std::shared_ptr<IScore> score)
        : ScoreDecorator(score) {}

    void Report() override {
        ScoreDecorator::Report();
        std::cout << "这次考试班级排名前列。" << std::endl;
    }
};

int main() {
    std::shared_ptr<IScore> score = std::make_shared<Score>(65); // 原始成绩

    // 加装饰器
    score = std::make_shared<ImprovedScoreDecorator>(score, 5); // 增加了5分
    score = std::make_shared<CloseToTopScoreDecorator>(score);  // 最高分比自己的高一点点
    score = std::make_shared<HighRankScoreDecorator>(score);    // 班级排名前列

    score->Report(); // 输出装饰后的成绩报告

    return 0;
}
