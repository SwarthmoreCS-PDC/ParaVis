#version 410

uniform sampler2D Tex0;

in vec4 color;
in vec2 texCoord;

out vec3 fragColor;

void main() {
  fragColor = texture(Tex0, texCoord).rgb;
  // fragColor.a = 1;
  // fragColor = vec4(texCoord.x,texCoord.y,0,1.);
  // fragColor = color.rgb;
}
