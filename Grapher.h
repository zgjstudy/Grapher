#ifndef GRAPHER_H
#define GRAPHER_H

#include <glfw3.h>
#include <stdlib.h>
#include <GL\glut.h>
#include<stdio.h>
#include <vector>
#include <math.h>
#include <iostream>
#include <algorithm>

bool comp(const std::vector<double>  &a, const  std::vector<double>  &b);

class Grapher {
public:
	Grapher(std::vector<std::vector<double>>vdd);
	//Shaper(std::vector<std::vector<double>>vdd);
	~Grapher();

private:
	void standardize(std::vector<std::vector<double>>&vdd);
	void drawAxis();
	void drawTri3D(std::vector<std::vector<double>>vdd);
	void drawFunction(std::vector<std::vector<double>>vdd);
	void initScene(int w, int h);
	void  drawScene(GLFWwindow* window, std::vector<std::vector<double>>vdd);
	//void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);


};

#endif // !GRAPHER_H
