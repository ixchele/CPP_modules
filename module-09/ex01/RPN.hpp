#pragma once

#include <stack>
#include <string>
class	RPN {
	public:
		typedef std::stack<std::string> Stack;
	private:
		std::string	_expr;

		int	_process(void);

	public:
		RPN(void);
		RPN(const std::string &expr);
		RPN(const RPN &other);
		~RPN(void);

		RPN	operator=(const RPN &other);

		void		setExpr(const std::string &expr);
		std::string	getExpr(void) const;

		int result(void);

		static int	evaluate(const std::string &expr);
};
