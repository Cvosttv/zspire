#version 330 core                                  
                             
in vec2 uvs;                                                                
out vec4 FragColor;                                                        
uniform sampler2D font_sampler; 
uniform vec3 textColor;                                         
void main()                                                                  
{                                                                          
    vec4 color = texture(font_sampler, uvs);                                                                         
    FragColor = color * vec4(textColor, 1.0);                           
}
