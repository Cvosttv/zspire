#version 460 core

layout (location = 0) in vec3 Position;                                    
layout (location = 1) in vec2 vertexUV;                                     
out vec2 uvs;                           


uniform float step;
uniform float offset_y;

uniform int res_x;
uniform int res_y;

uniform float posT_x;
uniform float posT_y;


uniform float scale;

void main()                                                                  
{             

    float pos_x = (posT_x * 2 - 1) / res_x + (Position.x / res_x * 2 - 1) + (step * 2 - 1) / res_x;    
    float pos_y = (posT_y * 2 ) / res_y + (Position.y / res_y * 2 - 1) ;

    gl_Position = vec4(pos_x, pos_y, 1, 1.0);              
    uvs = vertexUV;                                                          
}
