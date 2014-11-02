#version 120
#extension GL_EXT_geometry_shader4 : enable

void main(void) {
    int i, layer;
    for (layer = 0; layer < 6; layer++) {
        gl_Layer = layer;
        for (i = 0; i < 3; i++) {
            gl_Position = gl_PositionIn[i];
            EmitVertex();
        }
        EndPrimitive();
    }
}
