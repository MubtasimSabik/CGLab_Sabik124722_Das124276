#version 150
<<<<<<< HEAD
// fragment shader

in  vec3 pass_Color;
out vec4 out_Color;

void main() {
    out_Color = vec4(pass_Color, 1.0);
=======
in vec3 pass_Color;
out vec4 out_Color;
void(){
out_Color = vec4(pass_Color, 1.0);
>>>>>>> fb969cbe34cc62bcbd66791595b0e3f6ca1101ae
}