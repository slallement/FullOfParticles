#version 120
uniform sampler2D texture; // the texture with the scene you want to blur
uniform vec2 texture_size; // the texture with the scene you want to blur
varying vec2 vTexCoord;
uniform float horizontal;

 
void main(void)
{
	vec4 sum = vec4(0.0);
	if(horizontal>=1.){
		float blurSize = 1./texture_size.x;
		sum += texture2D(texture, vec2(vTexCoord.x - 4.0*blurSize, vTexCoord.y)) * 0.05;
		sum += texture2D(texture, vec2(vTexCoord.x - 3.0*blurSize, vTexCoord.y)) * 0.09;
		sum += texture2D(texture, vec2(vTexCoord.x - 2.0*blurSize, vTexCoord.y)) * 0.12;
		sum += texture2D(texture, vec2(vTexCoord.x - blurSize, vTexCoord.y)) * 0.15;
		sum += texture2D(texture, vec2(vTexCoord.x, vTexCoord.y)) * 0.162;
		sum += texture2D(texture, vec2(vTexCoord.x + blurSize, vTexCoord.y)) * 0.15;
		sum += texture2D(texture, vec2(vTexCoord.x + 2.0*blurSize, vTexCoord.y)) * 0.12;
		sum += texture2D(texture, vec2(vTexCoord.x + 3.0*blurSize, vTexCoord.y)) * 0.09;
		sum += texture2D(texture, vec2(vTexCoord.x + 4.0*blurSize, vTexCoord.y)) * 0.05;
	}else{
		float blurSize = 1./texture_size.y;
		sum += texture2D(texture, vec2(vTexCoord.x, vTexCoord.y - 4.0*blurSize)) * 0.05;
		sum += texture2D(texture, vec2(vTexCoord.x, vTexCoord.y - 3.0*blurSize)) * 0.09;
		sum += texture2D(texture, vec2(vTexCoord.x, vTexCoord.y - 2.0*blurSize)) * 0.12;
		sum += texture2D(texture, vec2(vTexCoord.x, vTexCoord.y - blurSize)) * 0.15;
		sum += texture2D(texture, vec2(vTexCoord.x, vTexCoord.y)) * 0.16;
		sum += texture2D(texture, vec2(vTexCoord.x, vTexCoord.y + blurSize)) * 0.15;
		sum += texture2D(texture, vec2(vTexCoord.x, vTexCoord.y + 2.0*blurSize)) * 0.12;
		sum += texture2D(texture, vec2(vTexCoord.x, vTexCoord.y + 3.0*blurSize)) * 0.09;
		sum += texture2D(texture, vec2(vTexCoord.x, vTexCoord.y + 4.0*blurSize)) * 0.05;
		
	}
 
   gl_FragColor = gl_Color *  sum;
}