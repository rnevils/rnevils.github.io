#version 330 core
out vec4 color;
in vec3 vertex_normal;
in vec3 vertex_pos;
in vec2 vertex_tex;
uniform vec3 campos;

uniform int soln;

uniform sampler2D tex;
uniform sampler2D tex2;
uniform sampler2D tex3;
uniform sampler2D tex4;
uniform sampler2D tex5;
uniform sampler2D tex6;

void main()
{
    vec3 n = normalize(vertex_normal);
    vec3 lp=vec3(10,-20,-100);
    vec3 ld = normalize(vertex_pos - lp);
    float diffuse = dot(n,ld);
    
    
    vec4 tcol = vec4(1,1,1,1);

    
    if (soln == 0)
    {
        tcol = texture(tex, vertex_tex);
    }
    else if (soln == 1)
    {
        tcol = texture(tex2, vertex_tex);
    }
    else if (soln == 2)
    {
        tcol = texture(tex5, vertex_tex);
    }
    else if (soln == 3)
    {
        tcol = texture(tex3, vertex_tex);
    }
    else if (soln == 4)
    {
        tcol = texture(tex3, vertex_tex);
    }
    else if (soln == 5)
    {
        tcol = texture(tex6, vertex_tex);
    }
    else if (soln == 6)
    {
        tcol = texture(tex4, vertex_tex);
    }
    else if (soln == 7)
    {
        tcol = texture(tex4, vertex_tex);
    }
    else if (soln == 8)
    {
        tcol = texture(tex3, vertex_tex);
    }
    else if (soln == 9)
    {
        tcol = texture(tex4, vertex_tex);
    }
    else
    {
        tcol = texture(tex4, vertex_tex);
    }
    
    color = tcol;
    //color.a = 0.1;
    
    vec3 cd = normalize(vertex_pos - campos);



}
