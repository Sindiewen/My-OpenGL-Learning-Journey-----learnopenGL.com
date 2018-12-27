#shader vertex
#version 330 core

layout (location = 0) in vec3 aPos; // The position variable has attribute position 0
layout (location = 1) in vec3 aColor; // the color variable has attribute posiiton 1

out vec3 outColor; // output a color to the fragment shader

void main()
{
    gl_position = vec4(apos, 1.0);
    ourColor = aColor // set ourColor to the input color we got from the vertex data
}

#shader fragment
#version 330 core
out vec4 FragColor;
in vec3 ourColor;

void main()
{
    FragColor = vec4(ourColor, 1.0);
}