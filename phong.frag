varying vec4 color;
varying vec3 mynormal; 
varying vec4 myvertex; 

const int numLights = 1; 
uniform bool enablelighting; // are we lighting at all (global).
uniform vec4 lightposn[numLights]; // positions of lights 
uniform vec4 lightcolor[numLights]; // colors of lights
uniform int numused;               // number of lights used

uniform vec4 ambient; 
uniform vec4 diffuse; 
uniform vec4 specular; 
uniform vec4 emission; 
uniform float shininess; 

void main()
{
        vec4 finalcolor;     
        vec4 mypos = gl_ModelViewMatrix * myvertex;
        vec3 mypos_ = mypos.xyz / mypos.w;
        vec3 lightdir =lightposn[numused].xyz-mypos_;

        lightdir = normalize(lightdir);
        vec3 mynormal_ = (gl_ModelViewMatrixInverseTranspose*vec4(mynormal,0.0)).xyz ;
        float ndot = dot(lightdir,mynormal_);

        vec4 lightcolor_ = lightcolor[numused].xyzw;
        vec4 lambert = diffuse * max(ndot,0);

        vec3 eye =vec3(0, 0, 5.0);
        vec3 halfv = lightdir + eye;
        halfv = normalize(halfv);
        float spec = dot(mynormal, halfv);
        vec4 specucolor = specular
        *lightcolor_*pow(max(spec,0),shininess);
        finalcolor = ambient + lambert + specucolor;
        gl_FragColor = finalcolor;

}