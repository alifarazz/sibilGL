#version 330 core

in vec3 Color;
in vec2 Texcoord;

out vec4 outColor;

uniform sampler2D tex;

void main()
{
  outColor = texture(tex, Texcoord) * vec4(Color, 1.0);
  // outColor = vec4(1 - Color.r, 1 - Color.g, 1 - Color.b , 1.0);
}
