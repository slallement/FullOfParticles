#version 120
uniform sampler2D texture;
uniform float time;

void main()
{
    vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);
    float value = (pixel.r+pixel.g+pixel.b)/3.;
    if(time > 4.){
        value = 0.;
        pixel = vec4(0.,0.,0.,1.);
    }else if(time > 1.){
        value *= (1.-time/4.);
        pixel = vec4(value,value,value,1.);
    }else{
        value *= (1.-time/4.);
        float t1 = time/1.;
        float t2 = 1.-time/1.;
        pixel = (vec4(value,value,value,1.)*t1+pixel*t2);
    }

    gl_FragColor = gl_Color*pixel;
}
