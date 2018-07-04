#include"FormulaParser.hpp"
#include<bits/stdc++.h>

Formula::Formula()
{
	std::string row;
	std::cin >> row;
	initialSet(row);
}

Formula::Formula(std::string row)
{
	initialSet(row);
}

Formula::~Formula()
{
	//foo
}

Formula::initialSet(std::string row)
{

}