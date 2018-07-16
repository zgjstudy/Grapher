//version 1.1
#include "Grapher.h"
#include <algorithm>
#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 600
const GLfloat PI = 3.1415f;
float  xrot = 0.0f, yrot = 0.0f, zrot = 0.0f;
void drawExample();
bool flag = true;
bool roIt = false;
GLfloat scal = 1.0;


void  key_callback(GLFWwindow * window, int key, int scancode, int action, int mods)
{
	  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
			glfwSetWindowShouldClose(window, GL_TRUE);
		if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
				yrot -= 10.0f;
		if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
			yrot +=10.0f;
		if (key == GLFW_KEY_UP && action == GLFW_PRESS)
			xrot -=10.0f;
		if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
			xrot += 10.0f;
		if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
			roIt = true;
		if (key == GLFW_KEY_P && action == GLFW_PRESS)
			scal += 0.1f;
		if (key == GLFW_KEY_O && action == GLFW_PRESS)
			scal -= 0.1f;

}



bool comp(const std::vector<double>  &a, const  std::vector<double>  &b)
{
	return a[0] < b[0];
}

void Grapher::standardize(std::vector<std::vector<double>>&vdd) {

	sort(vdd.begin(), vdd.end(), comp);


	double max = -99999;

	//for (int i = 0; i < vdd.size(); i++) {
	//std::cout << vdd[i][0] << " "<<vdd[i][i]<<std::endl;
	//}
	
	for (int i = 0; i < vdd.size(); i++) {
		if (max < vdd[i][0]) max = vdd[i][0];
	}

	for (int i = 0; i < vdd.size(); i++) {
		vdd[i][0] /= max;
	}
	/*for (int i = 0; i < vdd.size(); i++) {
	std::cout<<vdd[i][0]<< " " << vdd[i][1]<< " " << vdd[i][2]<<std::endl;
	}*/
	max = -9999;
	for (int i = 0; i < vdd.size(); i++) {
		if (max < vdd[i][1]) max = vdd[i][1];
	}
	for (int i = 0; i < vdd.size(); i++) {
		vdd[i][1] /= max;
	}

}




Grapher::Grapher(std::string input, int dimension, double xLdomin, double xRdomin, double yLdomin, double yRdomin) {

	
	Add=Equalation(input);

	GLFWwindow* window;
	/* 初始化glfw库 */
	if (!glfwInit()) {
		exit(EXIT_FAILURE);
	}



	/* 创建一个窗口和它的OpenGL上下文 */
	window = glfwCreateWindow(800, 800, "Grapher", NULL, NULL);
	//初始化OpenGL窗口
	initScene(WINDOW_WIDTH, WINDOW_HEIGHT);

	if (!window)
	{
		/* 没有创建会返回NULL */
		glfwTerminate();
		abort();
	}

	/* 设置当前的窗口上下文 */
	glfwMakeContextCurrent(window);


	/*设置回调函数*/
	glfwSetKeyCallback(window, key_callback);

	/* 循环，直到用户关闭窗口 */
	while (!glfwWindowShouldClose(window))
	{
		
		
		/* 在这里做渲染 */
		drawScene(window,  dimension,  xLdomin,  xRdomin,  yLdomin, yRdomin);
		
	

		/* 轮询事件 */
		glfwPollEvents();
	}

	glfwTerminate();

}

Grapher::~Grapher() {
//to be finished
}

//
//void Grapher::standardize(std::vector<std::vector<double>>&vdd) {
//	sort(vdd.begin(), vdd.end(), comp);
//	
//	
//	double max = -99999;
//
//	/*for (int i = 0; i < vdd.size(); i++) {
//		std::cout << vdd[i][0] << std::endl;
//	}
//    */
//	for (int i = 0; i < vdd.size();i++) {
//		if (max < vdd[i][0]) max = vdd[i][0];
//	}
//
//	for (int i = 0; i < vdd.size(); i++) {
//		vdd[i][0]/=max;
//	}
//	/*for (int i = 0; i < vdd.size(); i++) {
//		std::cout<<vdd[i][0]<< " " << vdd[i][1]<< " " << vdd[i][2]<<std::endl;
//	}*/
//	max = -9999;
//	for (int i = 0; i < vdd.size(); i++) {
//		if (max < vdd[i][1]) max = vdd[i][1];
//	}
//	for (int i = 0; i < vdd.size(); i++) {
//		vdd[i][1] /=max;
//	}
//
//}

void Grapher::drawAxis(double xLdomin, double xRdomin, double yLdomin, double yRdomin) {




	GLfloat x, y, angle;

	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 1.05f);
	for (angle = 0.0f; angle < (2.0f * PI); angle += (PI / 8.0f))
	{
		x = 0.01f * sin(angle);
		y = 0.01f * cos(angle);
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(x, y, 1.0f);
	}
	glEnd();
	glPopMatrix();


	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 1.05f, 0.0f);
	for (angle = 0.0f; angle < (2.0f * PI); angle += (PI / 8.0f))
	{
		x = 0.01f * sin(angle);
		y = 0.01f * cos(angle);
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(x, 1.0, y);
	}
	glEnd();
	glPopMatrix();

	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(1.05f, 0.0f, 0.0f);
	for (angle = 0.0f; angle < (2.0f * PI); angle += (PI / 8.0f))
	{
		x = 0.01f * sin(angle);
		y = 0.01f * cos(angle);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(1.0, x, y);
	}
	glEnd();
	glPopMatrix();

	glLineWidth(1.0f);//设置线段宽度
	glBegin(GL_LINES);

	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(xLdomin, 0.0,0.0); //x - red
	glVertex3f(xRdomin, 0.0,0.0);

	if (yLdomin == 0 && yRdomin == 0) {
		glColor3f(0.0, 1.0, 0.0);
		glVertex3f(0.0, -1.0, 0.0); //y - green
		glVertex3f(0.0, 1.0, 0.0);

	}
	else {
		glColor3f(0.0, 1.0, 0.0);
		glVertex3f(0.0, yLdomin, 0.0); //y - green
		glVertex3f(0.0, yRdomin, 0.0);

	}

	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0.0, 0.0, -1.0); //z - blue
	glVertex3f(0.0, 0.0, 1.0);

	glEnd();
	glPopMatrix();

}

void Grapher::drawTri3D(double xLdomin, double xRdomin, double yLdomin, double yRdomin) {

	/*分割*/
	
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	
	GLfloat color1= 0.6;
	GLfloat color2 = 0.6;


	bool mode = 1;
	for (float i = xLdomin; i<xRdomin; i += 0.1f)
	{
		glBegin(GL_TRIANGLE_STRIP);
	
		for (float j = yLdomin; j < yRdomin; j += 0.1f) {
			
			glColor3f(0.0f, color1, color2);

			std::vector<std::pair<std::string, double>> A;
			std::pair < std::string, double >B = {"x", i};
			A.push_back(B);
			std::pair < std::string, double >C = { "y", j };
			A.push_back(C);
			double z = Add.get_single_point(A);
			glVertex3f(i, j, z);
			
	  //	 if(flag)std::cout << i << " " << j << " " << z << std::endl;
			
			A.clear();
			B = { "x", i+0.1f };
			A.push_back(B);
			C = { "y", j };
			A.push_back(C);
			z = Add.get_single_point(A);
			glVertex3f(i+0.1f , j, z);

			
			if (mode) {
				color1 += 0.1f;
				color2 += 0.1f;
				if (color1 > 1.0f)mode = 0;
			}
			else {
				color1 -= 0.1f;
				color2 -= 0.1f;
				if (color1 <0.6)mode = 1;
			}
		}
		glEnd();
	}

	flag = false;
	
	
	
	glPopMatrix();
}

inline void Grapher::drawFunction(int dimension, double xLdomin, double xRdomin, double yLdomin, double yRdomin) {



	//定点坐标范围
	if (dimension == 2) {

		glLineWidth(5.0f);//设置线段宽度
		for (float i = xLdomin; i < xRdomin; i+=0.01f) {
			/*划线*/

			std::vector<std::pair<std::string, double>> A;
			std::pair < std::string, double >B = { "x", i };
			A.push_back(B);
			double y1 = Add.get_single_point(A);

			A.clear();
			B = { "x",i + 0.01f };
			A.push_back(B);
			double y2 = Add.get_single_point(A);

			glBegin(GL_LINES);
			glColor3f(1.0, 1.0, 1.0);

			glVertex2f(i, y1);
			glVertex2f(i+0.01f, y2);
			glEnd();
		}

	}
	else if (dimension == 3) {

		/*此处绘制3D三角剖分*/
		drawTri3D(xLdomin,xRdomin,yLdomin,yRdomin);

	}
	else {
		throw ("wrong data!");
	}
}

void Grapher::initScene(int w, int h)
{
	// 启用阴影平滑
	glShadeModel(GL_SMOOTH);
	// 黑色背景
	glClearColor(0.0, 0.0, 0.0, 0.0);
	// 设置深度缓存
	glClearDepth(1.0);
	// 启用深度测试
	glEnable(GL_DEPTH_TEST);
	// 所作深度测试的类型
	glDepthFunc(GL_LEQUAL);
	// 告诉系统对透视进行修正
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}


//这里进行所有的绘图工作
//需要补充旋转、放缩等callback操作
inline void Grapher::drawScene(GLFWwindow* window, int dimension, double xLdomin, double xRdomin, double yLdomin, double yRdomin) {

	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();                                   // Reset The View 

	glClearColor(0.0, 0.0, 0.0, 0.0);					// Reset Color
	glClear(GL_COLOR_BUFFER_BIT);


	
	

	/*
	进行渲染
	*/
	
	drawAxis(xLdomin, xRdomin, yLdomin, yRdomin);

	/*旋转操作*/
	glRotatef(xrot, 1.0f, 0.0f, 0.0f);
	glRotatef(yrot, 0.0f, 1.0f, 0.0f);
	glRotatef(zrot, 0.0f, 0.0f, 1.0f);
	/*放缩操作*/
	glScalef(scal, scal, scal);


	drawFunction(dimension, xLdomin, xRdomin, yLdomin, yRdomin);
	/*放缩操作*/
	glScalef(scal, scal, scal);
	scal = 1.0f;

	/*旋转操作*/
	glRotatef(xrot, 1.0f, 0.0f, 0.0f);
	glRotatef(yrot, 0.0f, 1.0f, 0.0f);
	glRotatef(zrot, 0.0f, 0.0f, 1.0f);
	xrot = 0.0f;
	yrot = 0.0f;

	glPushMatrix();
	
	//drawExample();

	

	/*
	旋转参数
	*/
	if (roIt) {
		xrot += 1.0f;
		yrot += 1.0f;
	}

	/*
	放缩参数
	*/
	//scal += 0.1f;


	// 交换缓冲区 
	glfwSwapBuffers(window);
}

void drawExample() {

	GLfloat x, y, angle;
	glClear(GL_COLOR_BUFFER_BIT);

	glPushMatrix();
	glRotatef(xrot, 1.0f, 0.0f, 0.0f);
	glRotatef(yrot, 0.0f, 1.0f, 0.0f);

	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0.0f, 0.0f, 75.0f);

	int ipvot = 0;
	for (angle = 0.0f; angle < (2.0f * PI); angle += (PI / 8.0f))
	{
		x = 0.50f * sin(angle);
		y = 0.50f * cos(angle);

		if (ipvot % 2 == 0) glColor3f(0.0f, 1.0f, 0.0f);
		else glColor3f(1.0f, 0.0f, 0.0f);

		ipvot++;

		glVertex3f(x, y, 0.0f);

	}
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0.0f, 0.0f, 0.0f);

	for (angle = 0; angle < (2.0f * PI); angle += (PI / 8.0f))
	{
		x = 0.50f * sin(angle);
		y = 0.50f * cos(angle);

		if (ipvot % 2 == 0) glColor3f(0.0f, 1.0f, 0.0f);
		else glColor3f(1.0f, 0.0f, 0.0f);

		ipvot++;

		glVertex3f(x, y, 0.0f);
	}

	glEnd();
}


