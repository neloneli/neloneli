#include"arith.h"




// 计算最大公约数，用于约分
int Fraction::gcd(int a, int b) {
	return b == 0 ? a : gcd(b, a % b);
}

// 约分分数
void Fraction::reduce() {
	int divisor = gcd(numerator, denominator);
	numerator /= divisor;
	denominator /= divisor;
	// 确保分母总是正数
	if (denominator < 0) {
		numerator = -numerator;
		denominator = -denominator;
	}
}

std::string Fraction::get_str_fra()
{
	std::string fra;
	if (numerator > denominator)
	{
		fra += std::to_string(numerator / denominator);
		fra.push_back('\'');
	}
	if (numerator % denominator == 0)
	{
		if (numerator == denominator)
		{
			return std::string("1");
		}
		fra.erase(fra.size() - 1);
		return fra;
	}
	fra += std::to_string(numerator % denominator);
	fra.push_back('/');
	fra += std::to_string(denominator);
	return fra;
}

float Fraction::get_frac()const
{
	return (float)numerator / (float)denominator;
}

// 构造函数
Fraction::Fraction(int n , int d ) : numerator(n), denominator(d) {
	if (d == 0) {
		throw std::invalid_argument("Denominator cannot be zero.");
	}
	reduce();
}
Fraction::Fraction(std::string& s) : numerator(0), denominator(1)
{
	int inte = 0;
	size_t pos1 = s.find('\'');
	size_t pos2 = s.find('/');

	if (pos1 == std::string::npos && pos2 == std::string::npos)
	{
		std::string integer = s.substr(0);
		inte = std::stoi(integer);
		numerator += inte * denominator;
	}
	else if (pos2 != std::string::npos)
	{
		int begin = 0;
		int len = 0;
		if (pos1 != std::string::npos)
		{
			begin = pos1 + 1;
			len = pos2 - pos1;
			std::string integer = s.substr(0, pos1);
			inte = std::stoi(integer);
		}
		else
		{
			len = pos2;
		}
		std::string integer = s.substr(begin, len);
		numerator = std::stoi(integer);

		integer = s.substr(pos2 + 1);
		denominator = std::stoi(integer);
		
		numerator += inte * denominator;
	}

	
}

// 重载加法运算符
Fraction Fraction::operator+(const Fraction& other) const {
	if (numerator == 0)
	{
		return other;
	}
	if (other.numerator == 0)
	{
		return *this;
	}
	return Fraction(numerator * other.denominator + other.numerator * denominator,
		denominator * other.denominator);
}

// 重载减法运算符
Fraction Fraction::operator-(const Fraction& other) const {
	return Fraction(numerator * other.denominator - other.numerator * denominator,
		denominator * other.denominator);
}

// 重载乘法运算符
Fraction Fraction::operator*(const Fraction& other) const {
	if (numerator == 0 || other.numerator == 0)
	{
		return Fraction(0);
	}

	return Fraction(numerator * other.numerator, denominator * other.denominator);
}

// 重载除法运算符
Fraction Fraction::operator/(const Fraction& other) const {
	return Fraction(numerator * other.denominator, denominator * other.numerator);
}

//比较两个分数大小
bool Fraction::operator>(const Fraction& other) const {
	return numerator * other.denominator > denominator * other.numerator;
}

//比较两个分数大小
bool Fraction::operator<(const Fraction& other) const {
	return !(*this > other);
}

//判断相等
bool Fraction::operator==(const Fraction& other) const {
	if (numerator == 0 && other.numerator == 0)
		return true;
	else
	{
		return (numerator == other.numerator) && (denominator == other.denominator);
	}
}
bool Fraction::operator!=(const Fraction& other) const {
	return !(*this == other);
}

// 输出流运算符重载
std::ostream& operator<<(std::ostream& os, const Fraction& f) {
	os << f.numerator << "/" << f.denominator;
	return os;
}

// 输入流运算符重载
std::istream& operator>>(std::istream& is, Fraction& f) {
	is >> f.numerator >> f.denominator;
	f.reduce();
	return is;
}





std::ostream& operator<<(std::ostream& os, const Question& q) {
	for (auto it : q.que)
	{
		os << it << " ";
	}
	return os;
}

Question::Question(int _range, int _num)
	:range(_range), num(_num), par_flag(false)
{
	ran_data();//生成数字
	ran_oper();//生成运算符
	get_result();//得到结果
	get_str();//生成字符串
}
Question::Question(std::vector<std::string>& vs)
{
	if (vs.size() == 5)
	{
		num = 2;
		Fraction d1(vs[1]);
		Fraction d2(vs[3]);
		data.push_back(d1);
		data.push_back(d2);
		oper.push_back(get_oper(vs[2]));
	}
	else
	{
		num = 3;
		get_DataOper(vs);
	}

	get_result();//得到结果
	get_str();//生成字符串

}


void Question::get_DataOper(std::vector<std::string>& vs)
{
	int dp1, dp2, dp3, oper1, oper2;

	if (vs[1] == "(")
	{
		par_flag = true;
		par_pos = 0;
	}
	else if (vs[3] == "(")
	{
		par_flag = true;
		par_pos = 1;
	}
	else
	{
		par_flag = false;
		par_pos = 2;
	}

	if (par_pos == 0)
	{
		dp1 = 2;
		dp2 = 4;
		dp3 = 7;
		oper1 = 3;
		oper2 = 6;
	}
	else if (par_pos == 1)
	{
		dp1 = 1;
		dp2 = 4;
		dp3 = 6;
		oper1 = 2;
		oper2 = 5;
	}
	else{
		dp1 = 1;
		dp2 = 3;
		dp3 = 5;
		oper1 = 2;
		oper2 = 4;
	}

	data.push_back(Fraction(vs[dp1]));
	data.push_back(Fraction(vs[dp2]));
	data.push_back(Fraction(vs[dp3]));
	oper.push_back(get_oper(vs[oper1]));
	oper.push_back(get_oper(vs[oper2]));
}
int Question::get_oper(std::string& v)
{
	if (v == "+")
		return 0;
	if (v == "-")
		return 1;
	if (v == "×")
		return 2;
	if (v == "÷")
		return 3;
}
void Question::get_str()
{
	if (result == Fraction(0))
	{
		res = std::string("0");
	}
	else
		res = result.get_str_fra();

	for (auto e : data)
	{
		if (e == Fraction(0))
			que.push_back(std::string("0"));
		else
			que.push_back(e.get_str_fra());
	}
	auto pos = que.begin() + 1;
	for (auto it : oper)
	{
		switch (it)
		{
		case ADD:que.insert(pos, std::string("+")); break;
		case SUB:que.insert(pos, std::string("-")); break;
		case MUL:que.insert(pos, std::string("×")); break;
		case DIV:que.insert(pos, std::string("÷")); break;
		default:
			break;
		}
		pos = que.begin() + 3;
	}
	if (par_flag)
	{
		int left_par, right_par;
		if (par_pos == 0)
		{
			left_par = 0;
			right_par = 4;
		}
		else
		{
			left_par = 2;
			right_par = 6;
		}
		que.insert(left_par + que.begin(), std::string("("));
		que.insert(right_par + que.begin(), std::string(")"));

	}
	que.emplace(que.end(), std::string("="));
}

//判断相等
bool Question::operator==(const Question& other) const {
	std::string q1, q2;
	for (int i = 1; i < que.size()-1; ++i)
	{
		q1 += que[i];
	};
	for (int i = 1; i < other.que.size() - 1; ++i)
	{
		q2 += other.que[i];
	}
	return areEquivalent(q1, q2);
	
}


std::vector<std::string> Question::infixToPostfix(const std::string& infix) const{
	std::stack<char> operators;
	std::vector<std::string> postfix;
	for (char ch : infix) {
		if (isdigit(ch)) {
			std::string num(1, ch);
			postfix.insert(postfix.end(), num);
		}
		else if (ch == '(') {
			operators.push(ch);
		}
		else if (ch == ')') {
			while (!operators.empty() && operators.top() != '(') {
				postfix.push_back(std::string(1, operators.top()));
				operators.pop();
			}
			operators.pop(); // Remove '(' from the stack
		}
		else {
			while (!operators.empty() && precedence(operators.top()) >= precedence(ch)) {
				postfix.push_back(std::string(1, operators.top()));
				operators.pop();
			}
			operators.push(ch);
		}
	}
	while (!operators.empty()) {
		postfix.push_back(std::string(1, operators.top()));
		operators.pop();
	}
	return postfix;
}

// 比较两个表达式是否等价
bool Question::areEquivalent(const std::string& expr1, const std::string& expr2) const{
	auto postfix1 = infixToPostfix(expr1);
	auto postfix2 = infixToPostfix(expr2);
	return postfix1 == postfix2;
}

// 定义运算符的优先级
int Question::precedence(char op) const{
	if (op == '+' || op == '-') return 1;
	if (op == '*' || op == '/') return 2;
	return 0;
}

void Question::ran_oper()
{
	std::mt19937 rng(std::random_device{}());
	std::uniform_int_distribution<int> dist(0, range);

	if (num == 3 && dist(rng) % 2 == 0)
	{
		par_flag = true;
		par_pos = dist(rng) % 2;
	}
	int _num = num;
	while (--_num != 0)
	{
		int choice = dist(rng) % 4;
		oper.push_back(choice);
	}
}

void Question::ran_data()
{
	std::mt19937 rng(std::random_device{}());
	std::uniform_int_distribution<int> dist(0, range);
	std::uniform_int_distribution<int> dist1(1, range);

	int _num = num;
	while (_num-- != 0)//随机出数字
	{

		int numerator = dist(rng);
		int denominator = dist1(rng);
		Fraction f(numerator, denominator);
		data.push_back(f);

	}
}

int Question::GetPri(int ope)
{
	if (ope == ADD || ope == SUB)
		return 1;
	else
		return 2;
}

void Question::get_result()
{
	if (num == 2)
	{
		step.push_back(0);
	}
	else
	{
		int prev_step, next_step;

		if (par_flag)
		{
			prev_step = par_pos;
		}
		else
		{
			if (GetPri(oper[0]) < GetPri(oper[1]))
			{
				prev_step = 1;
			}
			else
			{
				prev_step = 0;
			}
		}
		next_step = (prev_step + 1) % 2;
		step.push_back(prev_step);
		step.push_back(next_step);
	}
	calculate();
}

void Question::calculate()
{
	if (num == 2)
	{
		result = _calculate(data[0], data[1], 0);
	}
	else if (num == 3) {
		std::stack<Fraction> inter;
		int i = 0;
		inter.push(data[i++]);
		inter.push(data[i++]);

		if (step[0] == 1)
		{
			inter.push(data[i++]);
		}
		Fraction tmp2 = inter.top();
		inter.pop();
		Fraction tmp1 = inter.top();
		inter.pop();
		tmp1 = _calculate(tmp1, tmp2, 0);
		inter.push(tmp1);
		if (i < num)
		{
			inter.push(data[i++]);
		}

		tmp2 = inter.top();
		inter.pop();
		tmp1 = inter.top();
		inter.pop();
		result = _calculate(tmp1, tmp2, 1);
	}

}
Fraction Question::_calculate(Fraction& tmp1, Fraction& tmp2, int st)
{
	if (oper[step[st]] == SUB)
	{
		if (tmp2 > tmp1)
		{
			oper[step[st]] = ADD;
		}
	}
	if (oper[step[st]] == DIV)
	{
		if (tmp2 == Fraction(0))
		{
			oper[step[st]] = MUL;
		}
	}
	switch (oper[step[st]])
	{
	case ADD:return tmp1 + tmp2;
	case SUB:return tmp1 - tmp2;
	case MUL:return tmp1 * tmp2;
	case DIV:return tmp1 / tmp2;
	default:
		break;
	}
}
Fraction Question::get_fra_res()
{
	return result;
}
std::string Question::get_str_res()
{
	return res;
}


float MyHash::operator()(const Fraction& res) const {
float result = res.get_frac();
return result;
}



Generator::Generator(int _num, int _range, const char* _qfile, const char* _afile)
	:number(_num), range(_range), qFile(_qfile), aFile(_afile)
{
	Create();
}
Generator::Generator(const char* _qfile, const char* _afile, const char* _rfile)
	:qFile(_qfile), aFile(_afile)
{
	Accuracy(_rfile);
}
Generator::~Generator()
{}


//生成题目和答案
void Generator::Create()
{
	int num = number;
	while (num-- != 0)
	{
		std::mt19937 rng(std::random_device{}());
		std::uniform_int_distribution<int> dist(2, 3);
		int count = dist(rng);
		Question q(range, count);
		if (judge(q))
		{
			num++;
			continue;
		}
		else
		{
			questions.push_back(q);
			record.insert({ q.get_fra_res(), q});
		}
	}
	Write();
}

//判断有无相同的题目
bool Generator::judge(Question& q)
{
	if (record.count(q.get_fra_res()) != 0)
	{
		auto range = record.equal_range(q.get_fra_res());
		for (auto it = range.first; it != range.second; it++)
		{
			if (it->second == q)
			{
				return true;
			}
		}
	}

	return false;

}

//将题目和答案写入文件
void Generator::Write()
{
	std::ofstream QueFile;
	QueFile.open(qFile);
	for (int i = 0; i < questions.size(); i++)
	{
		QueFile << std::to_string(i + 1) << ".   " << questions[i] << std::endl;

	}
	std::ofstream AnsFile;
	AnsFile.open(aFile);
	for (int i = 0; i < questions.size(); i++)
	{
		AnsFile << std::to_string(i + 1) << ".   " << questions[i].get_str_res() << std::endl;
	}
}
//根据题目和答案判断正确率
void Generator::Accuracy(const char* rfile)
{

	std::ifstream QueFile(qFile);
	std::ifstream ResFile(aFile);
	std::string line;
	std::vector<Fraction> answers;
	while (getline(QueFile, line))
	{
		std::istringstream iss(line);
		std::vector<std::string> words;
		std::string word;
		while (iss >> word)
		{
			words.push_back(word);
		}
		Question q(words);
		questions.push_back(q);
	}
	while (getline(ResFile, line))
	{
		std::istringstream iss(line);
		std::vector<std::string>words;
		std::string word;
		while (iss >> word)
		{
			words.push_back(word);
		}
		Fraction ans(words[1]);
		answers.push_back(ans);
	}
	return _accuracy(questions, answers, rfile);

}
void Generator::_accuracy(std::vector<Question>& que, std::vector<Fraction>& ans,const char* rfile)
{
	int right = 0;
	int wrong = 0;
	std::string rs("(");
	std::string ws("(");
	for (int i = 0; i < que.size(); i++)
	{
		std::stringstream ss;
		if (que[i].get_fra_res() != ans[i])
		{
			wrong++;
			ss << i + 1;
			ws += ss.str();
			ws += ",";
		}
		else
		{
			right++;
			ss << i + 1;
			rs += ss.str();
			rs += ",";
		}
	}
	if (ws.size() != 1)
		ws.erase(ws.end() - 1);
	if (rs.size() != 1)
		rs.erase(rs.end() - 1);
	ws.append(")");
	rs.append(")");
	std::ofstream OutFile;
	OutFile.open(rfile);
	OutFile << "Correct:" << right << " " << rs << std::endl;
	OutFile << " wrong :" << wrong << " " << ws << std::endl;

};
