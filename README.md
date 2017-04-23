# CG_project3
# 原理
本实验以上一个实验为基础，在第一个实验的基础上实现了着色器的渲染效果。
光照主要由三部分组成：环境光（ambient），漫反射（diffuse），镜面反射（specular）。首先设置全局的环境光变量，有 mat_ambient[]设置环境光，mat_diffuse[]设置漫反射光，mat_specular设置镜面光，position设置光源位置
OPENGL有两种着色器，分别为顶点着色器和片元着色器，利用uniform参数从应用程序中向shader里传递当前模型视图矩阵和模型视图投影，
