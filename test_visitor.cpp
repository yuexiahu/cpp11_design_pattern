#include "Visitor.hpp"
#include <string>
#include <iostream>
#include <vector>

//将数据结构和数据操作分离
//需要实现二次动态分派

//问题:
//如果老师教学反馈得分大于等于85分、学生成绩大于等于90分，则可以入选"成绩优秀奖"
//如果老师论文数目大于8、学生论文数目大于2，则可以入选"科研优秀奖"

class Teacher;
class Student;

// 元素的访问者基类
using ElementVisitor = Visitor<Teacher, Student>;

// 元素基类
class Element
{
public:
    virtual void accept(ElementVisitor& v) = 0;
};

// 具体元素: 数据结构
class Teacher : public Element
{
public:
    Teacher(std::string name, int score, int paper_count)
        : m_name(std::move(name))
        , m_score(score)
        , m_paper_count(paper_count)
    {
    }

    // 二次动态分派
    void accept(ElementVisitor& v) override
    {
        v.Visit(*this);
    };

    const std::string& name() const
    {
        return m_name;
    }

    int score() const
    {
        return m_score;
    }

    int paper_count() const
    {
        return m_paper_count;
    }

private:
    std::string m_name;
    int m_score;
    int m_paper_count;
};

class Student : public Element
{
public:
    Student(std::string name, int grade, int paper_count)
        : m_name(std::move(name))
        , m_grade(grade)
        , m_paper_count(paper_count)
    {
    }

    // 二次动态分派
    void accept(ElementVisitor& v) override
    {
        v.Visit(*this);
    };

    const std::string& name() const
    {
        return m_name;
    }

    int grade() const
    {
        return m_grade;
    }

    int paper_count() const
    {
        return m_paper_count;
    }

private:
    std::string m_name;
    int m_grade;
    int m_paper_count;
};

// 具体访问者: 对数据的操作
class GradeSelection : public ElementVisitor
{
public:
    void Visit(const Teacher& teacher) override
    {
        if (teacher.score() >= 85)
        {
            std::cout << "恭喜 " << teacher.name() << " 老师，教学反馈得分为 " << teacher.score() << ", 获得 成绩优秀奖"
                      << std::endl;
        }
    }

    void Visit(const Student& student) override
    {
        if (student.grade() >= 90)
        {
            std::cout << "恭喜 " << student.name() << " 学生，成绩为 " << student.grade() << ", 获得 成绩优秀奖"
                      << std::endl;
        }
    }
};

class ResearchSelection : public ElementVisitor
{
public:
    void Visit(const Teacher& teacher) override
    {
        if (teacher.paper_count() >= 8)
        {
            std::cout << "恭喜 " << teacher.name() << " 老师，论文数量为 " << teacher.paper_count()
                      << ", 获得 科研优秀奖" << std::endl;
        }
    }

    void Visit(const Student& student) override
    {
        if (student.paper_count() >= 2)
        {
            std::cout << "恭喜 " << student.name() << " 学生，论文数量为 " << student.paper_count()
                      << ", 获得 科研优秀奖" << std::endl;
        }
    }
};

void test_visitor()
{
    std::vector<Teacher> teachers = {
        {"张三丰", 85, 20},
        {"张无忌", 70, 10},
        {"周芷若", 90, 2},
        {"谢逊", 50, 2},
    };

    std::vector<Student> students = {
        {"郭靖", 95, 0},
        {"黄蓉", 70, 1},
        {"欧阳锋", 90, 2},
        {"老顽童", 100, 2},
    };

    GradeSelection gradeSelection;
    ResearchSelection researchSelection;

    std::cout << "老师获奖：\n";
    for (auto&& teacher : teachers)
    {
        teacher.accept(gradeSelection);
        teacher.accept(researchSelection);
    }
    std::cout << "\n";

    std::cout << "学生获奖：\n";
    for (auto&& student : students)
    {
        student.accept(gradeSelection);
        student.accept(researchSelection);
    }
}

int main()
{
    test_visitor();
}
