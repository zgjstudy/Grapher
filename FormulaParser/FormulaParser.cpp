#include"FormulaParser.hpp"
#include<bits/stdc++.h>

Meta::Meta(std::string operation_,std::vector<Meta*> req_,bool isLeaf_ = false)
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
		thraw (" expression illegal")
	}

	root->operation = "null"
	root->req.push_back(transfer(raw));
}

Formula::Meta * Formula::transfer(std::string content)
{
	int bracket_cnt =0;
	std::string buffer;
	for(int i=0;i<content.length();++i)
	{
		if(content[i] == '(' && !i)
		{
			std::vector<Meta *> new_rqe;
			new_req.push_back(transfer(1,content.length()-2));
			return(new Meta("bracket"),new_req);
		}
		else if((content[i] == '+' || content[i] == '-') 
			&&bracket_cnt == 0)
		{
			std::vector<Meta*> new_req;
			new_req.push_back(transfer(content.substr(0,i-1)));
			new_req.push_back(transfer(content.substr(i+1,content.length())));
			std::string new_operation;
			new_operation +=content[i];
			return(new Meta(new_operation,new_req))
		}
		else if(content[i] == '*' || content[i] == '/') 
			&&bracket_cnt == 0)
		{
			std::vector<Meta*> new_req;
			new_req.push_back(transfer(content.substr(0,i-1)));
			new_req.push_back(transfer(content.substr(i+1,content.length())));
			std::string new_operation;
			new_operation +=content[i];
			return(new Meta(new_operation,new_req))
		}
		else if(is_function(buffer))
		{
			int begin_position=0;
			for(int j=0;j<content.length();++j)
			{
				if(content == '(')
				{
					if(!begin_position) begin_position = j;break;
				}
			}
			std::vector<Meta*> new_req;
			new_req.push_back(content.substr(begin_position,content.length()-1));
			return(new Meta(buffer,new_req));
		}
		else if(content[i] == '\'')
		{
			std::string var;
			for(int j=i+1;j<content.length();++j)
			{
				if(content[j]=='\'')
				{
					return (new Meta("variable"+" "+var,nullptr,true);)
				}
				else var+=content[i];
			}
		}
		else if(content[i] >= '0' && content[i] <= '9')
		{
			std::string cst;
			for(int j=i+1;j<content.length();++j)
			{
				if(content[j]<'0' || content[i] >'9')
				{
					return (new Meta("constant"+" "+cst,nullptr,true);)
				}
				else cst+=content[i];
			}
		}
		else
		{
			if(content[i] == '(') ++ bracket_cnt;
			else if(content[i] == ')') -- bracket_cnt;
			else buffer += content[i];
		}
	}
	return nullptr;
}

Formula::Variable * get_var_by_name(std::string name)
{
	for(int i=0;i<var.length();++i)
	{
		if(var[i].name == name)return (&var[i])
		return nullptr
	}
}