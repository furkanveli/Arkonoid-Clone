#version 330 core
in vec2 TexCoordinates;
out vec4 FragColor;

uniform sampler2D image;
uniform vec3 quadColor;

void main()
{    
    FragColor = vec4(quadColor, 1.0) * texture(image, TexCoordinates);
}  