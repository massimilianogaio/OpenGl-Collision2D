#version 330 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec2 offset;
layout(location = 2) in vec2 size;

uniform mat4 m_projection;
uniform mat4 m_mvp;

void main() {
	gl_Position = m_mvp * m_projection * vec4(pos.x, pos.y, pos.z, 1.0);
}