#include <RPN.hpp>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <sstream>
#include <stdexcept>
#include <string>

RPN::RPN(void) : _expr("0") {
	//pass
}

RPN::RPN(const std::string &expr) {
	setExpr(expr);
}

RPN::RPN(const RPN &other) {
	*this = other; 
}

RPN::~RPN(void) {
	//pass
}

RPN	RPN::operator=(const RPN &other) {
	if (this == &other)
		return *this;
	setExpr(other.getExpr());
	return *this;
}

void	RPN::setExpr(const std::string &expr) {
	_expr = expr;
}

std::string	RPN::getExpr(void) const {
	return _expr;
}

static void	validOperator(const std::string &op) {
	std::string validOperators("+-*/");
	if (op.size() != 1 || validOperators.find(op) == std::string::npos)
		throw std::runtime_error("Error");
}

static int	doOperation(int a, int b, const std::string &op) {
	switch (op[0]) {
		case '+': return a + b;
		case '-': return a - b;
		case '*': return a * b;
		case '/': if (b == 0) throw std::runtime_error("Error"); return a / b;
	}
	return 0;
}

int RPN::_process(void)
{
    std::stringstream ss(_expr);
    std::string token;
    std::stack<int> st;

    while (ss >> token) {
        if (token.size() == 1 && std::isdigit(token[0]))
            st.push(std::atoi(token.c_str()));
        else {
            validOperator(token);

            if (st.size() < 2)
                throw std::runtime_error("Error");

            int b = st.top();
			st.pop();

            int a = st.top();
			st.pop();

            st.push(doOperation(a, b, token));
        }
    }

    if (st.size() != 1)
        throw std::runtime_error("Error");

    return st.top();
}

int	RPN::result(void) {
	return _process();
}
