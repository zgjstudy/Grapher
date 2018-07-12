#ifndef EQUALATION_H
#define EQUALATION_H

#include<bits/stdc++.h>
#include"FormulaParser.hpp"

class Equalation
{
public:
	Equalation();
	Equalation(std::string);
	~Equalation();
	void SetupSequence(std::vector<std::pair<std::string, int>> variable_seq);
	void SetupBound(const std::vector<std::pair<double, double>> & bound);
	std::vector < std::vector<double> > GetPoints(double stride);
private:
	std::vector<std::pair<double, double>> bound;
	Formula left, right;
	std::vector<std::string> variables;
	void scatter(const std::vector<std::pair<double, double>> & bound,double stride);
	bool should_exit(const std::vector<std::pair<double, double>> & bound, const std::vector< std::pair<std::string, double>> &instantaneous);
	void increase_variables(std::vector< std::pair<std::string, double>> &instantaneous, const double stride, const std::vector<std::pair<double, double>> & bound);
	std::vector < std::vector<double> > solution;
};

#endif //EQUALATION_H