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


class Fraction //����������
{
private:
	int numerator; // ����
	int denominator; // ��ĸ
	int gcd(int a, int b);// �������Լ��������Լ��
	void reduce();// Լ�ַ���
public:
	std::string get_str_fra();//�õ��������ַ�����ʽ
	float get_frac()const;//�õ������ĸ�������ʽ
	Fraction(int n = 0, int d = 1);//ͨ��������Ӻͷ�ĸ����Fraction
	Fraction(std::string& s);//ͨ������string�ַ������ɷ���
	Fraction operator+(const Fraction& other) const;//�����ӷ�
	Fraction operator-(const Fraction& other) const;//��������
	Fraction operator*(const Fraction& other) const;//�����˷�
	Fraction operator/(const Fraction& other) const;//��������

	bool operator>(const Fraction& other) const;//���ش��ڱȽ�
	bool operator<(const Fraction& other) const;//����С�ڱȽ�
	bool operator!=(const Fraction& other) const;//���ز��ȱȽ�
	bool operator==(const Fraction& other) const;//���ص��ڱȽ�
	friend std::ostream& operator<<(std::ostream& os, const Fraction& f);//���ط���������ȡ�����
	friend std::istream& operator>>(std::istream& is, Fraction& f);//���ط����������������

};

class Question //����һ�����������
{
public:
	int range;//��ֵ�ķ�Χ
	int num;//�������ֵĸ�����������������
	bool par_flag;//��������
	int par_pos;//���ŵ�λ��
	std::vector<Fraction> data;//�洢ÿ������
	std::vector<int> oper;//�洢�����
	std::vector<int> step;//�洢���㲽�裬���ڲ���
	Fraction result;//�洢�����Fraction����ʽ
	std::vector<std::string> que;//�洢��Ŀ����string�ַ�������ķ�ʽ
	std::string res;//�洢�������string����ʽ
public:
	friend std::ostream& operator<<(std::ostream& os, const Question& q);//�����������������ʵ�����ļ��д�ӡ��Ŀ
	Question(int _range, int _num);//�����ݷ�Χ�͸�������һ����Ŀ
	Question(std::vector<std::string>& vs);//���ļ��ж�����һ����Ŀ��ֳɵ��ַ������鹹��һ����Ŀ
	void get_DataOper(std::vector<std::string>& vs);//�ڶ��ֹ��������ڵõ����ݺ������
	int get_oper(std::string& v);//���ڽ������ת��Ϊ���ּ�¼
	void get_str();//������Ŀ�����ַ�������que
	bool operator==(const Question& other) const;//���ء�==���������ڱȽ�������Ŀ�Ƿ��ظ�
	void ran_oper();//�����������������ڵ�һ�ֹ���
	void ran_data();//����������ݣ����ڵڶ��ֹ���
	int GetPri(int ope);//�õ�����������ȼ�
	void get_result();//�õ�������
	void calculate();//���������Ⱥ��裬��get_result()����
	Fraction _calculate(Fraction& tmp1, Fraction& tmp2, int st);//������������������������calculate����
};

class MyHash {
public:float operator()(const Fraction& res) const;//��ϣ������������Ŀ����
};

class Generator//������������
{
private:
	int number;//��Ŀ����
	int range;//��Ŀ���ݵķ�Χ
	std::vector<Question> questions;//�浵������Ŀ
	std::unordered_multimap<Fraction, Question, MyHash> record;//��¼��������Ŀ�����ڲ���
	std::string qFile;//Ŀ����Ŀд��/��ȡ�ļ�
	std::string aFile;//Ŀ���д��/��ȡ�ļ�
public:
	Generator(int _num, int _range, const char* _qfile = "Exercises.txt", const char* _afile = "Answers.txt");//���캯������������Ŀ
	Generator(const char* _qfile, const char* _afile, const char* _rfile = "Grade.txt");//���캯�������ڼ�������Ŀ����
	~Generator();//��������
	void Create();//������Ŀ
	bool judge(Question& q);//�ж���Ŀ�Ƿ������ظ�
	void Write();//д��Ŀ���ļ�
	void Accuracy(const char* rfile);//�����ļ���ȡ������������Ŀ������������_accuracy()�õ���ȷ��
	void _accuracy(std::vector<Question>& que, std::vector<Fraction>& ans, const char* rfile);//����õ���ȷ��
};

# endif //ARITH_H