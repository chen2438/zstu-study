#include <iostream>
#include <memory>

// ����ӿ� Component
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
        std::cout << "�ɼ��ǣ�" << value << "��" << std::endl;
    }
};

// װ�������� Decorator
class ScoreDecorator : public IScore {
protected:
    std::shared_ptr<IScore> wrappedScore;

public:
    ScoreDecorator(std::shared_ptr<IScore> score) : wrappedScore(score) {}

    void Report() override {
        wrappedScore->Report();
    }
};

// ConcreteDecorator ǰװ���������ϴο��������˷���
class ImprovedScoreDecorator : public ScoreDecorator {
private:
    int improvement;

public:
    ImprovedScoreDecorator(std::shared_ptr<IScore> score, int improvement)
        : ScoreDecorator(score), improvement(improvement) {}

    void Report() override {
        std::cout << "���ϴο���������" << improvement << "�֡�" << std::endl;
        ScoreDecorator::Report();
    }
};

// ConcreteDecorator ǰװ��������߷ֱ��Լ��ķ�����һ���
class CloseToTopScoreDecorator : public ScoreDecorator {
public:
    CloseToTopScoreDecorator(std::shared_ptr<IScore> score)
        : ScoreDecorator(score) {}

    void Report() override {
        // ������߷���100��
        std::cout << "��ο�����߳ɼ����Լ��ĳɼ�ֻ��һ�㡣" << std::endl;
        ScoreDecorator::Report();
    }
};

// ConcreteDecorator ��װ�������༶����ǰ��
class HighRankScoreDecorator : public ScoreDecorator {
public:
    HighRankScoreDecorator(std::shared_ptr<IScore> score)
        : ScoreDecorator(score) {}

    void Report() override {
        ScoreDecorator::Report();
        std::cout << "��ο��԰༶����ǰ�С�" << std::endl;
    }
};

int main() {
    std::shared_ptr<IScore> score = std::make_shared<Score>(65); // ԭʼ�ɼ�

    // ��װ����
    score = std::make_shared<ImprovedScoreDecorator>(score, 5); // ������5��
    score = std::make_shared<CloseToTopScoreDecorator>(score);  // ��߷ֱ��Լ��ĸ�һ���
    score = std::make_shared<HighRankScoreDecorator>(score);    // �༶����ǰ��

    score->Report(); // ���װ�κ�ĳɼ�����

    return 0;
}
