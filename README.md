# CG_project3
# 原理
本实验以上一个实验为基础，在第一个实验的基础上实现了着色器的渲染效果。
光照主要由三部分组成：环境光（ambient），漫反射（diffuse），镜面反射（specular）。首先设置全局的环境光变量，有 mat_ambient[]设置环境光，mat_diffuse[]设置漫反射光，mat_specular设置镜面光，position设置光源位置，设置光源的属性，然后设置身体不同部位的材质，
OPENGL有两种着色器，分别为顶点着色器和片元着色器，本实验中phong shading模型顶点着色器计算了每个顶点的属性如颜色，位置以及法线向量进行计算，类型都为varying，在片元着色器中，输入uniform类型的环境光、散射光和镜面光参数,首先通过观察点位置和光源位置的差计算光线方向并进行normalize操作： 
        vec4 mypos = gl_ModelViewMatrix * myvertex;
        vec3 mypos_ = mypos.xyz / mypos.w;
        vec3 lightdir =lightposn[numused].xyz-mypos_;
        lightdir = normalize(lightdir);

下面计算漫反射光，反射光线的强度既依赖于材质，也依赖于光源相对表面的位置。一个物体的表面是粗糙的话，就会发生漫反射，理想的漫反射表面是如此粗糙，以至于各个方向的反射光强度都相等，称为lambert表面，计算公式为L*cos(n,l)，L是入射光强和漫反射系数的乘积，l是光源入射的方向反向 
n是p点得法线方向 
vec3 mynormal_ = (gl_ModelViewMatrixInverseTranspose*vec4(mynormal,0.0)).xyz ;
        float ndot = dot(lightdir,mynormal_);//法向量和光线方向点积

        vec4 lightcolor_ = lightcolor[numused].xyzw;
        vec4 lambert = mat_diffuse * max(ndot,0);//漫反射光L*cos(n,l)

现在将对图元中的每个片断进行处理，因此需要插值的结果。
vec3 mynormal_ = (gl_ModelViewMatrixInverseTranspose*vec4(mynormal,0.0)).xyz ;
        float ndot = dot(lightdir,mynormal_);//法向量和光线方向点积

        vec4 lightcolor_ = lightcolor[numused].xyzw;
        vec4 lambert = mat_diffuse * max(ndot,0);//漫反射光L*cos(n,l)

        vec3 eye =vec3(0, 0, 5.0);
        vec3 halfv = lightdir + eye;
        halfv = normalize(halfv);//反射光和观察者的夹角
        float spec = dot(mynormal, halfv);
        vec4 specucolor = mat_specular
        *lightcolor_*pow(max(spec,0),high_shininess);//L*cos(r,l)^α
        finalcolor = mat_ambient + lambert + specucolor;//环境光 漫反射 镜面光
        gl_FragColor = finalcolor;
