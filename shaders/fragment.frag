#version 150 core

in vec3 Color;

out vec4 outColor;

void main()
{
  outColor = vec4(1 - Color, 1.0);
  // outColor = vec4(1 - Color.r, 1 - Color.g, 1 - Color.b , 1.0);
}
