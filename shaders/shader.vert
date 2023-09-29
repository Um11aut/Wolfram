#version 460
layout(location = 0) in vec3 vPos;
  
layout(std140, binding=0) uniform UniformData {
  mat4 model;
  mat4 view;
  mat4 projection;
};
  
void main(){
  gl_Position = projection * view * model * vec4(vPos,1);
}