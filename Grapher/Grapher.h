#ifndef GRAPHER_H
#define GRAPHER_H

#include <glfw3.h>
#include <stdlib.h>
//#include <GL\glut.h>
#include<stdio.h>
#include <vector>
#include <math.h>
#include <iostream>
#include <algorithm>
#include "Equalation.hpp"


bool comp(const std::vector<double>  &a, const  std::vector<double>  &b);

class Grapher {
public:
	Grapher(std::string input,int dimension, double xLdomin,double xRdomin, double yLdomin, double yRdomin);
	//Shaper(std::vector<std::vector<double>>vdd);
	~Grapher();

private:
	void standardize(std::vector<std::vector<double>>&vdd);
	void drawAxis(double xLdomin, double xRdomin, double yLdomin, double yRdomin);
	void drawTri3D(double xLdomin, double xRdomin, double yLdomin, double yRdomin);
	void drawFunction(int dimension, double xLdomin, double xRdomin, double yLdomin, double yRdomin);
	void initScene(int w, int h);
	void  drawScene(GLFWwindow* window, int dimension, double xLdomin, double xRdomin, double yLdomin, double yRdomin);
	//void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	Equalation Add;

};

#endif // !GRAPHER_H
