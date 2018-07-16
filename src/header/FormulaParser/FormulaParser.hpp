#ifndef FORMULAPARSER_H
#define FORMULAPARSER_H

#include<bits/stdc++.h>
class Formula
{
public:
	Formula();
	Formula(std::string raw);
	~Formula();
	//double get_value(const std::vector<std::pair<std::string,double>> UpperBound, std::vector<std::pair<std::string,double>> LowerBound,double stride);
	void set_variables(std::vector < std::pair < std::string, double>> value);
	void increase_certain_variables(std::string variable_name, double stride);
	double get_value(const std::vector<std::pair<std::string, double>>& variable_value);
	

private:
	class Meta
	{
	public:
		double LDomain, RDomain;
		double LRange, RRange;
		double constant_value;
		std::string operation;
		std::vector<Meta*> req;
		bool isLeaf;

		Meta(std::string operation_,std::vector<Meta*> req_,bool isLeaf_,double constant_value_);
		~Meta();
		double calculate(const std::vector<std::pair<std::string, double>> & variable_value);
	};
	class Variable
	{
	public:
		std::string name;
		double value;
	};
	Meta * root;
	std::vector<Variable> var;

	void initialSet(std::string raw);
	bool validate(std::string raw);
	Meta * transfer(std::string content);
	Variable * get_var_by_name(std::string name);
	bool is_function(std::string buffer,std::string &function_name);
	int obtain_parameter_number(std::string function_name);
	bool reach_bound_limitation(std::vector<std::pair<std::string, double>> &UpperBound) const;
};


#endif //FORMULAPARSER_H

/*
log:
need to add a preprocess to delete the surplus space

passed:
+ -
* /
variable 
	'x'
constant
	2
barckets
	('x'+2)
	('x'+'x')*2
functions
	power('x',2)
	sin(ln('x'))
*/