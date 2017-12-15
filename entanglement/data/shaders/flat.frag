
uniform float u_time;
uniform vec2 u_resolution;

bool circle(vec2 pos, vec2 origin, float radius)
{
	return length(pos - origin) < radius;
}

void main()
{
	vec2 texcoord = gl_FragCoord.xy / u_resolution;
	
	if (circle(texcoord + vec2(sin(u_time + texcoord.y * 10.0) * 0.2, 0.0), vec2(0.5), 0.2 + 0.2 * abs(sin(u_time * 0.1 + texcoord.x * 3.0))))
	{
		gl_FragColor = vec4(1.0, 1.0, 0.0, 1.0);
	}
	else
	{
		discard;
	}
	
}