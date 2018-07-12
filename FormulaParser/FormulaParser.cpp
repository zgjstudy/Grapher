#include"FormulaParser.hpp"
#include<bits/stdc++.h>

Formula::Meta::Meta(std::string operation_,std::vector<Meta*> req_,bool isLeaf_ = false,double constant_value_ = 0)
{
	operation = operation_;
	req = req_;
	isLeaf = isLeaf_;
	constant_value = constant_value_;
}

Formula::Formula()
{
	//std::string raw;
	//std::cin >> raw;
	//initialSet(raw);
}

Formula::Formula(std::string raw)
{
	initialSet(raw);
}

Formula::~Formula()
{
	//foo
}

bool Formula::validate(std::string raw)
{
	//bracket check part
	int bracket_cnt=0;
	for(int i=0;i<raw.length();++i)
	{
		if(raw[i] =='(') ++ bracket_cnt;
		else if(raw[i] == ')') --bracket_cnt;
		if(bracket_cnt < 0) return false;
	}
	if(bracket_cnt)return false;


	return true;
}

bool Formula::is_function(std::string content,std::string &buffer)
{
	buffer.clear();
	for (int i = 0; i < content.length(); ++i)
	{
		if (content[i] >= 'a' && content[i] <= 'z') buffer += content[i];
		else break;
	}
	if (
		buffer == "sin"
		|| buffer == "cos"
		|| buffer == "tan"
		|| buffer == "arcsin"
		|| buffer == "arccos"
		|| buffer == "arctan"
		|| buffer == "ln"
		|| buffer == "lg"
		|| buffer == "power"
		)
		return true;
	return false;
}

int Formula::obtain_parameter_number(std::string function_name)
{
	if (
		function_name == ""
		|| function_name == "power"
		)
		return 1;
	else return 0;
}

void Formula::initialSet(std::string raw)
{
	if( !validate(raw))
	{
		throw (" expression illegal");
	}
	std::string null = "_NULL";
	/*root->operation =null;
	std::cout << "fine" << std::endl;
	root->req.push_back(transfer(raw));*/
	std::vector<Meta*> tmp;
	tmp.push_back(transfer(raw));
	root = new Meta(null, tmp);
}

Formula::Meta * Formula::transfer(std::string content)
{
	int bracket_cnt =0;
	/*for (int i = 0; i < content.length(); ++i)
	{
		if (content[i] == '(' && !i)
		{
			std::vector<Meta *> new_req;
			new_req.push_back(transfer(content.substr(1, content.length() - 2)));
			return(new Meta("bracket", new_req));
		}
	}*/

	//part of judge for barcket
	if (content[0] == '(' && content[content.length()-1] == ')')
	{
		std::vector<Meta *> new_req;
		new_req.push_back(transfer(content.substr(1, content.length() - 2)));
		return(new Meta("bracket", new_req));
	}
	//end barcket

	//part of judge for + and -
	for (int i = 0; i < content.length(); ++i)
	{
		if ((content[i] == '+' || content[i] == '-')
			&& bracket_cnt == 0)
		{
			std::vector<Meta*> new_req;
			new_req.push_back(transfer(content.substr(0, i)));
			new_req.push_back(transfer(content.substr(i + 1, content.length())));
			std::string new_operation;
			new_operation += content[i];
			return(new Meta(new_operation, new_req));
		}
		else
		{
			if (content[i] == '(') ++bracket_cnt;
			else if (content[i] == ')') --bracket_cnt;
		}
	}
	//end + and -

	//part of judge for * and /
	for (int i = 0; i < content.length(); ++i)
	{
		if ((content[i] == '*' || content[i] == '/')
			&& (bracket_cnt == 0))
		{
			std::vector<Meta*> new_req;
			new_req.push_back(transfer(content.substr(0, i)));
			new_req.push_back(transfer(content.substr(i + 1, content.length())));
			std::string new_operation;
			new_operation += content[i];
			return(new Meta(new_operation, new_req));
		}
		else
		{
			if (content[i] == '(') ++bracket_cnt;
			else if(content[i] == ')') --bracket_cnt;
		}
	}
	//end * and /

	//part of judge for function
	std::string function_name;
	if (is_function(content,function_name))
	{
		int begin_position = 0;
		std::vector<Meta*> new_req;
		//int num_parameter = obtain_parameter_number(function_name);
		
		{
			int begin_barcket = 0;
			int k = 0;
			for (begin_barcket = 0; begin_barcket < content.length(); ++begin_barcket)
				if (content[begin_barcket] == '(')break;
			for (int j = begin_barcket +1; j < content.length(); ++j)
			{
				for(k=j+1;k<content.length();++k)
				{
					if (content[k] == ')' || content[k] == ',')break;
				}
				/*if (content[j] == '(')
				{
					if (!begin_position) begin_position = j; break;
				}*/
				if (k < content.length())
				{
					new_req.push_back(transfer(content.substr(j, k-1)));
				}
				j = k;
			}
			//new_req.push_back(transfer(content.substr(begin_position, content.length() - 1)));
		}
		return(new Meta(function_name, new_req));
	}
	//end function

	//part of judge for variable
	for (int i = 0; i < content.length(); ++i)
	{
		if (content[i] == '\'')
		{
			std::string var;
			for (int j = i + 1; j < content.length(); ++j)
			{
				if (content[j] == '\'')
				{
					std::string tmp = "variable"; tmp += ' '; tmp += var;
					std::vector<Meta*> empty;
					return (new Meta(tmp, empty, true));
				}
				else var += content[j];
			}
		}
	}
	//end variable

	//part of judge for constant
	int dot_cnt = 1;
	std::string __tmp;
	bool is_constant=true;
	for (int i = 0; i < content.length(); ++i)
	{
		if (is_constant && (content[i] >= '0' && content[i] <= '9' || content[i] == '.' && dot_cnt))
		{
			if (content[i] == '.') --dot_cnt;
			__tmp += content[i];
			/*std::string cst;
			for (int j = i; j < content.length(); ++j)
			{
				if (content[j]<'0' || content[i] >'9')
				{
					std::string tmp = "constant";;
					std::vector<Meta*> empty;
					char *_tmp = new char[cst.length() + 1];
					for (int i = 0; i < cst.length(); ++i)
						_tmp[i] = cst[i];
					return (new Meta(tmp, empty, true, std::atof(_tmp)));
				}
				else cst += content[i];
			}
			char *_tmp = new char[cst.length() + 1];
			for (int i = 0; i < cst.length(); ++i)
				_tmp[i] = cst[i];
			std::string tmp = "constant";
			std::vector<Meta*> empty;
			//test
			std::cout << std::atof(_tmp) << std::endl;

			return (new Meta(tmp, empty, true, std::atof(_tmp)));*/
		}
		else is_constant = false;
	}
	if (__tmp.length())
	{
		std::string tmp = "constant";
		std::vector<Meta*> empty;
		char *_tmp = new char[content.length() + 1];
		for (int i = 0; i < content.length(); ++i)
			_tmp[i] = content[i];
		//test
		//std::cout << std::atof(_tmp) << std::endl;
		return (new Meta(tmp, empty, true, std::atof(_tmp)));
	}
	//end constant

	return nullptr;
}

Formula::Variable * Formula::get_var_by_name(std::string name)
{
	for(int i=0;i<var.size();++i)
	{
		if (var[i].name == name)return (&var[i]);
			return (nullptr);
	}
}

/*double Formula::get_value(std::vector<std::pair<std::string, double>> UpperBound, std::vector<std::pair<std::string, double>> LowerBound, double stride)
{

}*/

double Formula::get_value(const std::vector<std::pair<std::string, double>> & variable_value)
{
	/*
	input:
	a vector of each variable's value in form likes ( variable1 : value , variable2 : value ....)
	output:
	the calculate result of given certain variable value
	*/
	return root->calculate(variable_value);
}

double Formula::Meta::calculate(const std::vector<std::pair<std::string, double>> & variable_value)
{//holy s**t
	if (operation == "_NULL" || operation == "bracket")
	{
		return this->req[0]->calculate(variable_value);
	}
	else if (operation == "+")
	{
		return this->req[0]->calculate(variable_value) + this->req[1]->calculate(variable_value);
	}
	else if (operation == "-")
	{
		return this->req[0]->calculate(variable_value) - this->req[1]->calculate(variable_value);
	}
	else if (operation == "*")
	{
		return this->req[0]->calculate(variable_value) * this->req[1]->calculate(variable_value);
	}
	else if (operation == "/")
	{
		return this->req[0]->calculate(variable_value) / this->req[1]->calculate(variable_value);
	}
	else if (operation == "constant")
	{
		return this->constant_value;
	}
	else if (operation.length() > 8 && operation.substr(0,8) == "variable")
	{
		std::string variable_name = operation.substr(9, operation.length() - 1);
		auto it = variable_value.begin();
		for (; it != variable_value.end(); ++it)
		{
			if (it->first == variable_name)
			{
				return it->second;
			}
			//there will not have unexcepted case
		}
	}
	/*
	buffer == "sin"
		|| buffer == "cos"
		|| buffer == "tan"
		|| buffer == "arcsin"
		|| buffer == "arccos"
		|| buffer == "arctan"
		|| buffer == "ln"
		|| buffer == "log"
		|| buffer == "power"
	*/
	else//must be a funcion!
	{//instead this of enum must
		if (operation == "sin")
		{
			return sin(req[0]->calculate(variable_value));
		}
		else if (operation == "cos")
		{
			return cos(req[0]->calculate(variable_value));
		}
		else if (operation == "tan")
		{
			return tan(req[0]->calculate(variable_value));
		}
		else if (operation == "arcsin")
		{
			return asin(req[0]->calculate(variable_value));
		}
		else if (operation == "arccos")
		{
			return acos(req[0]->calculate(variable_value));
		}
		else if (operation == "arctan")
		{
			return atan(req[0]->calculate(variable_value));
		}
		else if (operation == "ln")
		{
			return log(req[0]->calculate(variable_value));
		}
		else if (operation == "lg")
		{
			return log10(req[0]->calculate(variable_value));
		}
		else if (operation == "power")
		{
			return pow(req[0]->calculate(variable_value),req[1]->calculate(variable_value));
		}
	}
}