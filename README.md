# CG_project3
# 着色器原理
本实验以上一个实验为基础，在第一个实验的基础上实现了着色器的渲染效果。
光照主要由三部分组成：环境光（ambient），漫反射（diffuse），镜面反射（specular）。首先设置全局的环境光变量，有 mat_ambient[]设置环境光，mat_diffuse[]设置漫反射光，mat_specular设置镜面光，position设置光源位置，设置光源的属性，然后设置身体不同部位的材质，
OPENGL有两种着色器，分别为顶点着色器和片元着色器，本实验中Blinn-Phone模型顶点着色器计算了每个顶点的属性如颜色，位置以及法线向量进行计算，类型都为varying，在片元着色器中，输入uniform类型的环境光、散射光和镜面光参数,首先通过观察点位置和光源位置的差计算光线方向并进行normalize操作：
        
        vec4 mypos = gl_ModelViewMatrix * myvertex;
        vec3 mypos_ = mypos.xyz / mypos.w;
        vec3 lightdir =lightposn[numused].xyz-mypos_;
        lightdir = normalize(lightdir);


下面计算漫反射光，反射光线的强度既依赖于材质，也依赖于光源相对表面的位置。一个物体的表面是粗糙的话，就会发生漫反射，理想的漫反射表面是如此粗糙，以至于各个方向的反射光强度都相等，称为lambert表面，首先需要将ModelViewMatrix求逆计算镜头的位置，然后求转置并与mynormal相乘求出入射点的法向量，然后计算L*cos(n,l)，L是入射光强和漫反射系数的乘积，l是光源入射的方向反向 

        vec3 mynormal_ = (gl_ModelViewMatrixInverseTranspose*vec4(mynormal,0.0)).xyz ;
        float ndot = dot(lightdir,mynormal_);//法向量和光线方向点积
        vec4 lightcolor_ = lightcolor[numused].xyzw;
        vec4 lambert = mat_diffuse * max(ndot,0);//漫反射光L*cos(n,l)

高光的颜色通常与环境光与满反射的颜色不同，就是光源的颜色，而且，所有得反射光线都在一个方向上，观察者看到的光线强度取决于理想反射器光线反射方向r和观察者方向v的夹角，反射光的计算公式为L*cos(r,l)^α，其中α为高光系数

        vec3 eye =vec3(0, 0, 5.0);
        vec3 halfv = lightdir + eye;
        halfv = normalize(halfv);//反射光和观察者的夹角
        float spec = dot(mynormal, halfv);
        vec4 specucolor = mat_specular
        *lightcolor_*pow(max(spec,0),high_shininess);//L*cos(r,l)^α
        finalcolor = mat_ambient + lambert + specucolor;//环境光 漫反射 镜面光
        gl_FragColor = finalcolor;

如果一个多边形上只有一种颜色，而且当前多边形面所使用的颜色是这个多边形的顶点中最后一个被渲染的顶点的颜色，而不是有这种插值方法得到的平滑效果，这个时候的渲染就叫做Flat Shading。在低版本的OPENGL中通过调用函数glShadeModel(GL_FLAT)实现。
