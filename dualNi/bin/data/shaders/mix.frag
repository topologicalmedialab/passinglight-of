#version 330

precision mediump float;

uniform sampler2DRect tex0; // cmap
uniform sampler2DRect depth1;
uniform sampler2DRect depth2;

in vec2 vTexcoord;
in vec4 vColor;
out vec4 fragColor;

vec3 hsv2rgb(vec3 c)
{
    vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
    vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
    return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
}

void main() {
  vec2 fragCoord = vTexcoord;
  fragCoord = fragCoord * vec2(320.0, 240.0*2);

  vec4 col1 = texture(depth1, fragCoord);
  vec4 col2 = texture(depth2, fragCoord);

  float depth = max(col1.r, col2.r) * 10;
  vec3 col = vec3(depth);
  //col = hsv2rgb(vec3(fract(depth * 10), 1, 1));
  fragColor = vec4(col, 1.0);
}
