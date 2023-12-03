#version 330 core

// in vec4 vertexColor; // vs로부터 입력된 변수
uniform vec4 color;
out vec4 fragColor; // 최종 출력 색상

void main() {
  fragColor = color;
}