#version 330 core
layout(location = 0) in vec3 vertPos;
layout(location = 1) in vec3 vertNor;
layout(location = 2) in vec2 vertTex;

uniform mat4 P;
uniform mat4 V;
uniform mat4 M;
uniform float t;
uniform int soln;
uniform int spd;

out vec3 vertex_pos;
out vec2 vertex_tex;
out vec3 vertex_normal;




void main()
{
    vertex_normal = vec4(M * vec4(vertNor,0.0)).xyz;
    // don't create these every time?
    float k1 = 1;
    float k2 = 1;
    float w = 1;
    float x = vertPos.x;
    float z = vertPos.z;
    float y = 0;
    
    
    
    
    vec3 posnorm = normalize(vertPos);
    
    
    float r = pow(pow(vertPos.x, 2) + pow(vertPos.z, 2), 0.5);
    float r1 = pow(pow(vertPos.x - 4, 2) + pow(vertPos.z, 2), 0.5);
    float r2 = pow(pow(vertPos.x + 4, 2) + pow(vertPos.z, 2), 0.5);
    float r3 = pow(pow(vertPos.x - 6, 2) + pow(vertPos.z - 2, 2), 0.5);
    
    float r11 = pow(pow(vertPos.x+8, 2) + pow(vertPos.z, 2), 0.5);
    float r12 = pow(pow(vertPos.x+8, 2) + pow(vertPos.z - 4, 2), 0.5);
    float r13 = pow(pow(vertPos.x+8, 2) + pow(vertPos.z - 8, 2), 0.5);
    float r14 = pow(pow(vertPos.x+8, 2) + pow(vertPos.z + 4, 2), 0.5);
    float r15 = pow(pow(vertPos.x+8, 2) + pow(vertPos.z + 8, 2), 0.5);
    
    
    // flat plane
    if (soln == 0)
    {
        y = 0*t;
    }
    
    //Waves
    //float
    
    if (soln == 1)
    {
        //y = cos(0.1*pow(x,2) + 0.1*pow(z,2.3) - t); //cool ripples but they decay?
        y = cos(r - t) + spd; //cool ripples but they decay?
    }
    
    if (soln == 2)
    {
        y = cos(0.1*pow(x,2) + 0.1*pow(z,2) - t); //cool ripples but they decay?
    }
    if (soln == 3)
    {
        y = exp(-1.0* pow(r - t, 2)); // bounce and extending outwared
        
    }
    if (soln == 4)
    {   
        y = exp(-1.0* pow(r - t, 2)) + exp(-1.0* pow(r2 - t, 2))  + exp(-1.0* pow(r3 - t, 6)); // bounce and extending superposition
    }
    if (soln == 5)
    {
        y = exp(-1.0* pow(x - t, 2)) + 2*exp(-1.0* pow(x - 9 + t, 3)); // single plane wave
    }
    if (soln == 6)
    {
        y = cos(x  + z - t) + sin(x - z - t);; //plane wave
    }
    if (soln == 7)
    {
        y = cos(x + z - t); //plane wave
    }
    if (soln == 8)
    {
        y = exp(-1.0* pow(r11 - t, 1.4)) + exp(-1.0* pow(r12 - t, 1.4)) + exp(-1.0* pow(r13 - t, 1.4)) + exp(-1.0* pow(r14 - t, 1.4)) + exp(-1.0* pow(r15 - t, 1.4));
    }
    if (soln == 9)
    {
        y = cos(r11 - t) + cos(r12 - t) + cos(r13 - t) + cos(r14 - t) + cos(r15 - t); //plane wave
    }

    
    vec4 tpos =  M * vec4(vertPos, 1.0);

    tpos.y += y;
    vertex_pos = tpos.xyz;
    
    gl_Position = P * V * tpos;
    vertex_tex = vertTex;
}
