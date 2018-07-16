#include<bits/stdc++.h>
#include"Equalation.hpp"
#include "Grapher.h"

using namespace std;

int main()
{
  	string input = "'z'='x'*'x'+'y'*'y'";
	//string input = "'y'=sin('x')";


	Grapher A(input,3,-1.0,1.0,-1.0,1.0);
	//Grapher A(input,2,-10.0,10.0,-1.0,1.0);

	system("pause");
	return 0;
}

