uniform int frame;
uniform sampler2D unProcessed;

float rand(vec3 co)
{
    return fract(sin(dot(co.xyz, vec3(12.9898,78.233,0.03))) * 43758.5453);
}

void main()
{
    vec2 coord = gl_TexCoord[0].xy;
    float deviation = rand(vec3(coord, frame));
    deviation /= 1.;
    deviation += 0.5;

    gl_FragColor = texture2D(unProcessed, coord) * deviation;
}
