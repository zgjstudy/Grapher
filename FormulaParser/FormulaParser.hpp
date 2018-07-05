#ifndef FORMULAPARSER_H
#define FORMULAPARSER_H

#include<bits/stdc++.h>
class Formula
{
public:
	Formula();
	Formula(std::string raw);
	~Formula();


private:
	class Meta
	{
	public:
		double LDomain, RDomain;
		double LRange, RRange;
		std::string operation;
		std::vector<Meta*> req;
		bool isLeaf;

		Meta(std::string operation_,std::vector<Meta*> req_,bool isLeaf_);
		~Meta();
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
	bool is_function(std::string buffer);

};


#endif //FORMULAPARSER_H

/*
log:
need to add a preprocess to delete the surplus space
'+' and variable and constant passed
*/