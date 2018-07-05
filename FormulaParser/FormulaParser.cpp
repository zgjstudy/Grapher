#include"FormulaParser.hpp"
#include<bits/stdc++.h>

Formula::Meta::Meta(std::string operation_,std::vector<Meta*> req_,bool isLeaf_ = false)
{
	operation = operation_;
	req = req_;
	isLeaf = isLeaf_;
}

Formula::Formula()
{
	std::string raw;
	std::cin >> raw;
	initialSet(raw);
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

bool Formula::is_function(std::string buffer)
{
	if(
	   buffer == "sin"
	|| buffer == "cos"
	|| buffer == "sec"
	)
		return true;
	return false;
}

void Formula::initialSet(std::string raw)
{
	if( !validate(raw))
	{
		throw (" expression illegal");
	}
	std::string null = "null";
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
	std::string buffer;
	for (int i = 0; i < content.length(); ++i)
	{
		if (content[i] == '(' && !i)
		{
			std::vector<Meta *> new_req;
			new_req.push_back(transfer(content.substr(1, content.length() - 2)));
			return(new Meta("bracket", new_req));
		}
	}
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
			else buffer += content[i];
		}
	}
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
			else if (content[i] == ')') --bracket_cnt;
			else buffer += content[i];
		}
	}
	for (int i = 0; i < content.length(); ++i)
	{
		if (is_function(buffer))
		{
			int begin_position = 0;
			for (int j = 0; j < content.length(); ++j)
			{
				if (content[j] == '(')
				{
					if (!begin_position) begin_position = j; break;
				}
			}
			std::vector<Meta*> new_req;
			new_req.push_back(transfer(content.substr(begin_position, content.length() - 1)));
			return(new Meta(buffer, new_req));
		}
		else
		{
			if (content[i] == '(') ++bracket_cnt;
			else if (content[i] == ')') --bracket_cnt;
			else buffer += content[i];
		}
	}
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
	for (int i = 0; i < content.length(); ++i)
	{
		if (content[i] >= '0' && content[i] <= '9')
		{
			std::string cst;
			for (int j = i; j < content.length(); ++j)
			{
				if (content[j]<'0' || content[i] >'9')
				{
					std::string tmp = "constant"; tmp += ' '; tmp += cst;
					std::vector<Meta*> empty;
					return (new Meta(tmp, empty, true));
				}
				else cst += content[i];
			}
			std::string tmp = "constant"; tmp += ' '; tmp += cst;
			std::vector<Meta*> empty;
			return (new Meta(tmp, empty, true));
		}
	}
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