
attribute vec2 vert_position;

void main() {
	gl_Position = vec4(vert_position, 0.0, 1.0);
}