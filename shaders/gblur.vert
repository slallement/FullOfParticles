#version 120
// ?
varying vec2 vTexCoord;

void main()
{
    // transform the vertex position
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
	//vTexCoord = gl_Position*0.5+0.5;

    // transform the texture coordinates
    gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;
	//vTexCoord =gl_TexCoord[0].xy;

    // forward the vertex color
    gl_FrontColor = gl_Color;
}
