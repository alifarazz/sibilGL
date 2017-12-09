#version 330 core

in vec3 Color;
in vec2 Texcoord;

out vec4 outColor;

uniform sampler2D texKitten;
uniform sampler2D texDog;
uniform float time;

void main()
{
  vec4 colKitten = texture(texKitten, Texcoord);
  vec4 colDog = texture(texDog, vec2(Texcoord.x, 1 - Texcoord.y));

  float period = 2.0;
  float intencity = 2.0 * abs((time / period) - floor(time / period + 0.5));

  // outColor =  mix(colDog, colKitten, intencity);
  outColor = colDog;
  // outColor = vec4(1 - Color.r, 1 - Color.g, 1 - Color.b , 1.0);
}
