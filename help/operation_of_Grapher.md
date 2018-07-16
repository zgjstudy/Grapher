# Grapher #

- 构造函数原型：
    - Grapher(std::string input,int dimension, double xLdomin,double xRdomin, double yLdomin, double yRdomin);
    - input:函数表达式
    - dimension:维度，只能是2或者3
    - xLdomin：x定义域最小值
    - xRdomin：x定义域最大值
    - yLdomin：y定义域最小值
    - yRdomin：y定义域最大值
- 缩放：
    - O键缩小
    - P键放大
- 旋转：
    - 方向键UP&DOWN绕x轴旋转
    - 方向键LEFT&RIGHT绕y轴旋转
    - SPACE键开启观察模式 函数模型将自动旋转
- 退出：
    - ESC结束窗口