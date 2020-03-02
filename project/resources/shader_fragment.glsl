#version 330 core
out vec4 color;
in vec3 vertex_normal;
in vec3 vertex_pos;
in vec2 vertex_tex;
uniform vec3 campos;

uniform sampler2D tex;
uniform sampler2D tex2;
uniform sampler2D tex3;


void main()
{
    //diffuse lighting
    vec3 n = normalize(vertex_normal);
    vec3 lp=vec3(0,100,10);
    vec3 ld = normalize(lp - vertex_pos);
    float diffuse = dot(n,ld);
    
    //color = texture(tex, vertex_tex) + texture(tex2, vertex_tex);
    color = vec4(1,0,0,1);

    color *= diffuse*.7;
    vec3 cd = normalize(vertex_pos - campos);
    //vec3 h = normalize(cd+ld);
    //float spec = dot(n,h);
    //spec = clamp(spec,0,1);
    //spec = pow(spec,20);
    //color += texture(tex3, vertex_tex)*spec*.8;
    //color.a = 0.5;
    
    
    // making it trasparent - from snowman
    //vec3 normal = normalize(fragNor);
    //vec3 fragNornormalized = -1*normalize(vertex_normal);
    //vec3 normalcampos = normalize(campos);
    
    //color.a = 1 - clamp(dot(normalcampos, fragNornormalized) , 0, 1);



}
