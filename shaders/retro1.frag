
uniform sampler2D texture;
//uniform float time;
uniform vec2 textureSize;
//uniform vec2 movement = vec2(100.,100.);

void main()
{
    vec2 offset = -1.0*vec2(1.,1.);//+movement/100.;
    vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);
    vec4 pixel2 = texture2D(texture, gl_TexCoord[0].xy+offset/textureSize);

    // multiply it by the color
    vec4 color = gl_Color;

    gl_FragColor.gb = color.gb * pixel.a * pixel.gb;
    gl_FragColor.r = color.r * pixel2.a * pixel2.r;
    gl_FragColor.a = color.a * (pixel.a+pixel2.a)/1.;
}
