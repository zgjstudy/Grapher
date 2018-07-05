#ifndef FORMULAPARSER_H
#define FORMULAPARSER_H

#include<bits/stdc++.h>
class Formula
{
public:
	Formular();
	Formula(std::string raw)
	~Formular();


private:
	class Meta
	{
	public:
		double LDomain, RDomain;
		double LRange, RRange;
		std::string operation;
		std::vector<Meta*> req;
		bool isLeaf

		Meta(std::string operation,vector<Meta*> req,bool isLeaf = false);
		~Meta();
	};
	class Variable
	{
	public:
		std::string name;
		double value;
	};
	Meta * root;
	std::vector<Varoable> var;

	void initialSet(std::string raw);
	bool validate(std::string raw);
	Meta * transfer(std::string content);
	Variable * get_var_by_name(std::string name);
	bool is_function(std::string buffer);

};


#endif //FORMULAPARSER_H