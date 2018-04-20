uniform vec2 uRes;

void main()
{
	vec2 pos = gl_FragCoord.xy/uRes;
	pos = pos * 2.0 - 1.0;
	pos.x *= uRes.x/uRes.y;
	
	if (length(pos) <  0.5)
	{
		gl_FragColor = vec4(pos,0,1);
	}
	else
	{
		discard;
	}
}
