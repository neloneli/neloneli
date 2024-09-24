#pragma once

#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<unordered_map>
#include<random>
#include<sstream>
#include<stack>


#ifndef ARITH_H
#define ARITH_H
enum ope
{
	ADD,
	SUB,
	MUL,
	DIV
};


class Fraction //分数管理类
{
private:
	int numerator; // 分子
	int denominator; // 分母
	int gcd(int a, int b);// 计算最大公约数，用于约分
	void reduce();// 约分分数
public:
	std::string get_str_fra();//得到分数的字符串形式
	float get_frac()const;//得到分数的浮点数形式
	Fraction(int n = 0, int d = 1);//通过传入分子和分母构造Fraction
	Fraction(std::string& s);//通过传入string字符串生成分数
	Fraction operator+(const Fraction& other) const;//分数加法
	Fraction operator-(const Fraction& other) const;//分数减法
	Fraction operator*(const Fraction& other) const;//分数乘法
	Fraction operator/(const Fraction& other) const;//分数除法

	bool operator>(const Fraction& other) const;//重载大于比较
	bool operator<(const Fraction& other) const;//重载小于比较
	bool operator!=(const Fraction& other) const;//重载不等比较
	bool operator==(const Fraction& other) const;//重载等于比较
	friend std::ostream& operator<<(std::ostream& os, const Fraction& f);//重载分数的流提取运算符
	friend std::istream& operator>>(std::istream& is, Fraction& f);//重载分数的流插入运算符

};

class Question //管理一个计算题的类
{
public:
	int range;//数值的范围
	int num;//计算数字的个数（两个或三个）
	bool par_flag;//有无括号
	int par_pos;//括号的位置
	std::vector<Fraction> data;//存储每个数据
	std::vector<int> oper;//存储运算符
	std::vector<int> step;//存储运算步骤，用于查重
	Fraction result;//存储结果以Fraction类形式
	std::vector<std::string> que;//存储题目，以string字符串数组的方式
	std::string res;//存储结果，以string的形式
public:
	friend std::ostream& operator<<(std::ostream& os, const Question& q);//重载流插入运算符，实现向文件中打印题目
	Question(int _range, int _num);//以数据范围和个数生成一个题目
	Question(std::vector<std::string>& vs);//从文件中读到的一个题目拆分成的字符串数组构建一个题目
	void get_DataOper(std::vector<std::string>& vs);//第二种构造下用于得到数据和运算符
	int get_oper(std::string& v);//用于将运算符转化为数字记录
	void get_str();//根据题目生成字符串数组que
	bool operator==(const Question& other) const;//重载“==”符号用于比较两个题目是否重复
	void ran_oper();//生成随机运算符，用于第一种构造
	void ran_data();//生成随机数据，用于第二种构造
	int GetPri(int ope);//得到运算符的优先级
	void get_result();//得到本题结果
	void calculate();//生成运算先后步骤，被get_result()调用
	Fraction _calculate(Fraction& tmp1, Fraction& tmp2, int st);//计算两个分数的运算结果，被calculate调用
};

class MyHash {
public:float operator()(const Fraction& res) const;//哈希函数，用于题目查重
};

class Generator//计算题生成器
{
private:
	int number;//题目数量
	int range;//题目数据的范围
	std::vector<Question> questions;//存档所有题目
	std::unordered_multimap<Fraction, Question, MyHash> record;//记录已生成题目，用于查重
	std::string qFile;//目标题目写入/读取文件
	std::string aFile;//目标答案写入/读取文件
public:
	Generator(int _num, int _range, const char* _qfile = "Exercises.txt", const char* _afile = "Answers.txt");//构造函数用于生成题目
	Generator(const char* _qfile, const char* _afile, const char* _rfile = "Grade.txt");//构造函数二用于检查错误题目数量
	~Generator();//析构函数
	void Create();//创建题目
	bool judge(Question& q);//判断题目是否已有重复
	void Write();//写入目标文件
	void Accuracy(const char* rfile);//处理文件读取的内容生成题目计算结果，调用_accuracy()得到精确度
	void _accuracy(std::vector<Question>& que, std::vector<Fraction>& ans, const char* rfile);//计算得到精确度
};

# endif //ARITH_H