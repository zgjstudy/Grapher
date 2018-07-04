#ifndef FORMULAPARSER_H
#define FORMULAPARSER_H

#include<bits/stdc++.h>
class Formula
{
public:
	Formular();
	~Formular();


private:
	class Meta
	{
	public:
		double LDomain, RDomain;
		double LRange, RRange;
		Meta * NextStep;
		std::string operation;
	};
	class Variable
	{
	public:
		std::string name;
		std::vector<Meta> relation;
	};
	std::vector<Meta> meta;
	std::vector<Varoable> var;


};


#endif //FORMULAPARSER_H