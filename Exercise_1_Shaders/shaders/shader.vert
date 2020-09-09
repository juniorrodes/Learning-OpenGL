#shader vertex
#version 330 core
layout (location = 0) in vec3 Position;

void main(){
    gl_Position = vec4(Position.x, -Position.y, Position.y, 1.0);
}
#shader fragment
#version 330 core

out vec4 FragColor;

uniform vec4 u_Color;

void main(){
    //FragColor = u_Color;
    FragColor = vec4(1.0, 0.6, 0.3, 1.0);
}
