#type vertex
#version 330 core

layout(location = 0) in vec3 i_Position;
layout(location = 1) in vec2 i_TexCoord;

out vec2 v_TexCoord;

uniform mat4 u_ViewProjection;
uniform mat4 u_Model;

void main() {
    v_TexCoord = i_TexCoord;
    gl_Position = u_ViewProjection * u_Model * vec4(i_Position, 1.0);
}

#type fragment
#version 330 core

in vec2 v_TexCoord;

layout(location = 0) out vec4 o_Color;

uniform sampler2D u_Texture;

void main() {
    o_Color = texture(u_Texture, v_TexCoord);
}