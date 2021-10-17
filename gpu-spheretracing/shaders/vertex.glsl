#version 330 core
in int gl_VertexID;
out vec2 texcoord;
smooth out vec3 view_ray;
const vec2 data[4] = vec2[]
(
  vec2(-1.0,  1.0),
  vec2(-1.0, -1.0),
  vec2( 1.0,  1.0),
  vec2( 1.0, -1.0)
);
uniform mat4 invViewProj;
void main()
{
	gl_Position = vec4( data[ gl_VertexID ], 0.0, 1.0);
	texcoord = (data[ gl_VertexID ].xy+ 1.0f) * 0.5f;
	view_ray = (invViewProj * vec4( data[ gl_VertexID ], 1.0, 1.0)).xyz;
}