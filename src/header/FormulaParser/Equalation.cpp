#include"Equalation.hpp"
#include<bits/stdc++.h>
#include<thread>

Equalation::Equalation()
{
	//foo
}

Equalation::Equalation(std::string equ)
{
	int i = 0;
	while (equ[i] != '=')++i;
	left = Formula(equ.substr(0, i));
	right = Formula(equ.substr(i+1, equ.length()));
}

Equalation::~Equalation()
{
	//foo
}

void Equalation::SetupSequence(std::vector<std::pair<std::string, int>> variable_seq)
{
	sort(variable_seq.begin(), variable_seq.end(),
		[](const std::pair<std::string, int> & a, const std::pair<std::string, int> &b)->bool
		{return a.second < b.second; });
	for (auto it = variable_seq.begin(); it != variable_seq.end(); ++it)
	{
		variables.push_back(it->first);
	}
}

void Equalation::SetupBound(const std::vector<std::pair<double, double>> & bound_)
{
	for (auto it = bound_.begin(); it != bound_.end(); ++it)
	{
		bound.push_back( std::pair<double,double>(it->first,it->second) );
	}
}

std::vector<std::vector<double>> Equalation::GetPoints(double stride)
{

	std::vector<std::thread> th;
	std::vector<std::pair<double, double>> bound_temp = bound;
	double bound_stride = (bound[0].second - bound[0].first) / thread_number;
	bound_temp[0].second = bound_temp[0].first;
	bound_temp[0].first -= bound_stride;
	for (int i = 0; i<thread_number; ++i)
	{
		bound_temp[0].first += bound_stride;
		bound_temp[0].second += bound_stride;
		th.push_back(std::thread(&Equalation::scatter,this,bound_temp, stride));
	}

	for (auto it = th.begin(); it != th.end(); ++it)
	{
		it->join();
	}

	//add mult-thread after finishing test
	//scatter(stride);
	
	//std::thread scatter1(scatter,std::ref(stride));
	//scatter1.join();
	
	//std::thread thread1(thread_test,this);
	//thread1.join();
	return solution;
}

void Equalation::scatter(const std::vector<std::pair<double, double>> &bound,double stride)
{
	int variables_number = variables.size();
	std::vector< std::pair<std::string, double>> instantaneous;
	std::vector<double> equaled;
	for (int i = 0; i < variables_number; ++i)
	{
		instantaneous.push_back(std::pair<std::string, double>(variables[i], bound[i].first));
	}
	while (!should_exit(bound,instantaneous))
	{
		increase_variables(instantaneous,stride,bound);
		if (abs(left.get_value(instantaneous) - right.get_value(instantaneous)) <= stride)
		{
			equaled.clear();
			for (auto it = instantaneous.begin(); it != instantaneous.end(); ++it)
			{
				equaled.push_back(it->second);
			}

			std::lock_guard<std::mutex> guard(vector_locker);
			solution.push_back(equaled);
		}
	}
}

bool Equalation::should_exit(const std::vector<std::pair<double, double>> &bound,const std::vector<std::pair<std::string, double>>& instantaneous)
{
	return instantaneous[instantaneous.size() - 1].second > bound[bound.size() - 1].second;
}

void Equalation::increase_variables(std::vector<std::pair<std::string, double>>& instantaneous, const double stride, const std::vector<std::pair<double, double>> & bound)
{
	int size = instantaneous.size();
	for (int i = 0; i < size; ++i)
	{
		if (instantaneous[i].second + stride <= bound[i].second)
		{
			instantaneous[i].second += stride;
			return;
		}
		else
		{
			instantaneous[i].second = bound[i].first;
		}
	}
	instantaneous[instantaneous.size()-1].second = bound[bound.size()-1].second + 2 * stride;
	return;
}

double Equalation::get_single_point(std::vector<std::pair<std::string, double>> var)
{
	return right.get_value(var);
}