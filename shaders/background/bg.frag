// some magic cargo cult function
float rand(in vec2 co)
{
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

void main()
{
    vec2 coord = gl_TexCoord[0].xy;
    float brightness = 0.002;

    float finalBWColor = clamp(brightness / rand(coord), 0., 1.);

    gl_FragColor = vec4(
        finalBWColor,
        finalBWColor,
        finalBWColor,
        1.0
    );
}
