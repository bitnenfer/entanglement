uniform vec2 uRes;
uniform float uTime;
uniform vec2 uMouse;

vec2 E = vec2(0,0.001);

float Smin(float a, float b, float k) {
    float res = exp(-k * a) + exp(-k * b);
    return -log(res) / k;
}

vec2 vMin(vec2 a, vec2 b)
{
	float v = Smin(a.x,b.x,24.0);
	return a.x < b.x ? vec2(v,a.y) : vec2(v,b.y);
}

float sdSphere(vec3 p, float r)
{
	return length(p) - r;
}

float sdTorus( vec3 p, vec2 t )
{
  vec2 q = vec2(length(p.xy)-t.x,p.z);
  return length(q)-t.y;
}


vec2 map(vec3 p)
{
	float time = uTime * 10.0;
	float sn = sin(time);
	float cn = cos(time);

	p = vec3(vec4(p, 1.0) * mat4(
		sn, cn, 0.0, 0.0,
		cn, -sn, 0.0, 0.0,
		0.0, 0.0, 1.0, 0.0,
		0.0, 0.0, 0.0, 1.0
	));

	sn = sin(time * 2.0);
	cn = cos(time * 2.0);

	p = vec3(vec4(p, 1.0) * mat4(
		1.0, 0.0, 0.0, 0.0,
		0.0, sn, cn, 0.0,
		0.0, cn, -sn, 0.0,
		0.0, 0.0, 0.0, 1.0
	));

	vec2 s0 = vec2(sdSphere(p + vec3(-0.25, -0.1, 0), 0.4), 0.0);
	vec2 s1 = vec2(sdSphere(p + vec3(+0.25, -0.1, 0), 0.4), 1.0);
	vec2 s2 = vec2(sdTorus(p + vec3(0.0, 0.2, -0.2), vec2(0.3, 0.1)), 2.0);

	return vMin(vMin(s0, s1),s2);
}

vec3 normal(vec3 p)
{
	return normalize(vec3(
		map(p + E.yxx).x - map(p - E.yxx).x,
		map(p + E.xyx).x - map(p - E.xyx).x,
		map(p + E.xxy).x - map(p - E.xxy).x
	));
}

vec3 raymarch(vec3 ro, vec3 rd)
{
	float total = 0.0;
	vec2 mouse = (uMouse / uRes) * 2.0 - 1.0;
	mouse.x = mouse.x * (uRes.x / uRes.y);
	mouse.y = mouse.y * -1.0;
	vec3 ld = normalize(vec3(mouse, 0.3));

	for (int i = 0; i < 128; ++i)
	{
		vec3 p = ro + rd * total;
		vec2 sd = map(p);
		float dist = sd.x;
		if (dist < 0.001)
		{
			vec3 n = normal(p);
			float ln = max(dot(n, ld),0.0);
			float s = pow(ln, 256.0);

			if (sd.y == 0.0)
			{
				return vec3(0.5, 0.6, 0.8) * vec3(pow(total, 8.0) * 2.0) + (vec3(ln) * vec3(1.0,0.4,0.4) + vec3(s) * vec3(0.3) + vec3(0.05));
			}
			else if (sd.y == 1.0)
			{
				return vec3(0.5, 0.6, 0.8) * vec3(pow(total, 8.0) * 2.0) + (vec3(ln) * vec3(0.4,1.0,0.4) + vec3(s * s *s) * vec3(0.3) + vec3(0.05));
			}
			else if (sd.y == 2.0)
			{
				return vec3(ln) * vec3(0.4,0.4,1.0) + vec3(0.01, 0.04, 0.0);
			}
		}
		total += dist;
	}
	
	return vec3(0.0);
}

void main()
{
	vec2 pos = (gl_FragCoord.xy / uRes) * 2.0 - 1.0;
	pos.x = pos.x * (uRes.x / uRes.y);

	vec3 ro = normalize(vec3(pos, 1.0));
	vec3 rd = normalize(cross(vec3(0,1,0), vec3(1,0,0)));
	vec3 color = raymarch(ro, rd);

	gl_FragColor = vec4(color, 1);
}
