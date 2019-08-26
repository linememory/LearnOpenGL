#version 330 core
layout (triangles) in;
layout (line_strip, max_vertices = 6) out;

in VS_OUT {
    vec3 normal;
} gs_in[];

float magnitude = 0.1;

void GenerateLine(int index){
    gl_Position = gl_in[index].gl_Position;
    EmitVertex();
    gl_Position = gl_in[index].gl_Position + vec4(gs_in[index].normal, 0.0) * magnitude;
    EmitVertex();
    EndPrimitive();
}

void GenerateNormalLine(){
    vec4 center = 1.0/3.0 * (gl_in[0].gl_Position + gl_in[1].gl_Position + gl_in[2].gl_Position);
    //center = gl_in[0].gl_Position;
    vec3 normal = normalize(gs_in[0].normal + gs_in[1].normal + gs_in[2].normal);
    //normal = gs_in[0].normal;
    gl_Position = center;
    EmitVertex();
    gl_Position = center + vec4(normal, 0.0) * magnitude;
    EmitVertex();
    EndPrimitive();
}

void main() {
    GenerateNormalLine();
    // GenerateLine(0);
    // GenerateLine(1);
    // GenerateLine(2);
}  