
#include "Grapher.h"
#include <algorithm>
#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 600
const GLfloat PI = 3.1415f;
float  xrot = 0.0f, yrot = 0.0f, zrot = 0.0f;
void drawExample();
bool flag = true;
bool roIt = false;


void  key_callback(GLFWwindow * window, int key, int scancode, int action, int mods)
{
	
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
			glfwSetWindowShouldClose(window, GL_TRUE);
		if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
				yrot -= 10.0f;
		/*if (key == GLFW_KEY_LEFT && action == GLFW_RELEASE)
			yRot = 0.0f;*/
		if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
			yrot +=10.0f;
		if (key == GLFW_KEY_UP && action == GLFW_PRESS)
			xrot +=10.0f;
		if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
			xrot -= 10.0f;
	/*	if (key == GLFW_KEY_DOWN && action == GLFW_RELEASE)
			xRot = 0.0f;*/
		if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
			roIt = true;


	/*if (xRot < 0) xRot = 355.0f;
	if (xRot > 360.0f) xRot = 0.0f;

	if (yRot < 0) yRot = 355.0f;
	if (yRot > 360.0f) yRot = 0.0f;*/
}


bool comp(const std::vector<double>  &a, const  std::vector<double>  &b)
{
	return a[0] < b[0];
}




Grapher::Grapher(std::vector<std::vector<double>>vdd,std::string input) {

	/*先对数据进行标准化*/
	standardize(vdd);
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
		//glClear(GL_COLOR_BUFFER_BIT);

		
		drawScene(window, vdd);

		/* 轮询事件 */
		glfwPollEvents();
	}

	glfwTerminate();

}

Grapher::~Grapher() {
//to be finished
}

void Grapher::standardize(std::vector<std::vector<double>>&vdd) {
	sort(vdd.begin(), vdd.end(), comp);
	
	
	double max = -99999;

	/*for (int i = 0; i < vdd.size(); i++) {
		std::cout << vdd[i][0] << std::endl;
	}
    */
	for (int i = 0; i < vdd.size();i++) {
		if (max < vdd[i][0]) max = vdd[i][0];
	}

	for (int i = 0; i < vdd.size(); i++) {
		vdd[i][0]/=max;
	}
	/*for (int i = 0; i < vdd.size(); i++) {
		std::cout<<vdd[i][0]<< " " << vdd[i][1]<< " " << vdd[i][2]<<std::endl;
	}*/
	max = -9999;
	for (int i = 0; i < vdd.size(); i++) {
		if (max < vdd[i][1]) max = vdd[i][1];
	}
	for (int i = 0; i < vdd.size(); i++) {
		vdd[i][1] /=max;
	}




}

void Grapher::drawAxis() {

	glLineWidth(1.0f);//设置线段宽度
	glBegin(GL_LINES);

	glColor3f(1.0, 0.0, 0.0);
	glVertex2f(-1.0, -0.0); //x - red
	glVertex2f(1.0, 0.0);

	glColor3f(0.0, 1.0, 0.0);
	glVertex2f(0.0, -1.0); //y - green
	glVertex2f(0.0, 1.0);

	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0.0, 0.0, -1.0); //z - blue
	glVertex3f(0.0, 0.0, 1.0);

	glEnd();



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

}

void Grapher::drawTri3D(std::vector<std::vector<double>> vdd) {

	/*分割*/
	
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glBegin(GL_TRIANGLE_STRIP);
	GLfloat color1= 0.0;
	GLfloat color2 = 0.0;


	
	for (float i = -1.0f; i<1.0f; i += 0.1f)
		for (float j = -1.0f; j <1.1f; j += 0.1f) {

			glColor3f(0.0f, color1, color2);

			std::vector<std::pair<std::string, double>> A;
			std::pair < std::string, double >B = {"x", i};
			A.push_back(B);
			std::pair < std::string, double >C = { "y", j };
			A.push_back(C);
			double z = Add.get_single_point(A);
			glVertex3f(i, j, z);
			
			if(flag)std::cout << i << " " << j << " " << z << std::endl;
			
			A.clear();
			B = { "x", i+0.1f };
			A.push_back(B);
			C = { "y", j };
			A.push_back(C);
			z = Add.get_single_point(A);
			glVertex3f(i+0.1f , j, z);

			color1 += 0.05;
			color2	+=0.01;
		}

	flag = false;
	
	
	glEnd();
	glPopMatrix();
}

inline void Grapher::drawFunction(std::vector<std::vector<double>> vdd) {



	//定点坐标范围
	if (vdd[0].size() == 2) {
	
		glLineWidth(5.0f);//设置线段宽度
		for (int i = 0; i < vdd.size() - 1; i++) {
			/*划线*/

			glBegin(GL_LINES);
			glColor3f(1.0, 1.0, 1.0);

			glVertex2f(vdd[i][0], vdd[i][1]);
			glVertex2f(vdd[i + 1][0], vdd[i + 1][1]);
			glEnd();
		}
	}
	else if (vdd[0].size() == 3) {

		/*此处绘制三角剖分*/
		drawTri3D(vdd);

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
inline void Grapher::drawScene(GLFWwindow * window, std::vector<std::vector<double>> vdd) {

	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();                                   // Reset The View 

	glClearColor(0.0, 0.0, 0.0, 0.0);					// Reset Color
	glClear(GL_COLOR_BUFFER_BIT);

	glRotatef(xrot, 1.0f, 0.0f, 0.0f);
	glRotatef(yrot, 0.0f, 1.0f, 0.0f);
	glRotatef(zrot, 0.0f, 0.0f, 1.0f);

	/*
	进行渲染
	*/
	
	drawAxis();
	glPushMatrix();
	drawFunction(vdd);
	//drawExample();

	

	/*
	旋转
	*/
	if (roIt) {
		xrot += 1.0f;
		yrot += 1.0f;
	}

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


