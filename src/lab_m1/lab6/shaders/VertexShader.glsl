#version 330

// Input
// TODO(student): Get vertex attributes from each location
layout(location = 0) in vec3 position;
layout(location = 3) in vec3 normal;
layout(location = 2) in vec2 texCoord;
layout(location = 1) in vec3 color;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform float Time;

// Output
// TODO(student): Output values to fragment shader
out vec3 frag_pos;
out vec3 frag_normal;
out vec2 frag_uv;
out vec3 frag_color;

void main()
{
    // TODO(student): Send output to fragment shader
    frag_pos = position;
    frag_normal = normal;
    frag_uv = texCoord;
    frag_color = Time*color;
    // TODO(student): Compute gl_Position
    vec3 position2 = position + vec3(cos(Time), sin(Time), 0);
    gl_Position = Projection * View * Model * vec4(position2, 1.0);

}
