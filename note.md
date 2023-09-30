<파이프라인>

application : 정점의 위치, 색깔을 입력 <- 우리가 opengl의 함수을 호출해서 할 것
<br/>
<br/>
--------------- 여기 아래서부터는 GPU가 다 알아서 해줌!!
<br/>
<br/>
geometry : 삼각형이 화면에 어느 위치에 있는지
resterization : 삼각형을 픽셀 단위로 변경
pixel : 픽셀 단위의 처리, 픽셀 색상의 결정

- 쉐이더 : 각 파이프라인 단계마다 GPU상에서 실행되는 작은 프로그램
- GLSL(GL Shading Language) : 옛날에는 옵션같은 존재였는데, Opengl3.3부터는 필수가 됨

---
<OPENGL Shader>
- OpenGL은 그림을 그려내기 위해 2개의 쉐이더가 반드시 필요!!
    - vertex shader
    - fragment shader

shader 코드는 opengl 코드 안에서 빌드되고 로딩됨.

shared ptr : 해당 주소값을 소유하고 있는 애들이 전부 사라질 때까지 포인터를 가지고 있다가, 해당 카운트가 모두 사라지게 되면, 그제서야 포인터를 해제한다. 이렇게 숫자를 세는 것을 reference counting 이라고 함!! (카운트가 0이 되는 순간, 아무도 해당 포인터를 사용하고 있지 않은 순간에 할당 해제!)

유니크 포인터를 쉐어드 포인터로 어떻게 만들까?
그냥 넣어주면 됨!

SharedPtr shader = Shader::CreateFromFile();

---
vertex buffer object(VBO) = 정점 데이터를 담아놓은 메모리 버퍼
정점에 대한 다양한 데이터를 GPU가 접근 가능한 메모리에 저장해둔다.
하나의 정점에 여러개의 데이터가 있을 수 있음!

---
<context.cpp>
```c++ // [2] VBO binding :: 버텍스 버퍼 생성(generate)
glGenBuffers(1, &m_vertexBuffer);
// Bind array_buffer <- vertex buffer
glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
// 실제로 데이터를 복사하는 과정 : (버텍스 버퍼, 크기 지정, vertices(pointer), 용도) 를 넣어줌.
glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 12, vertices, GL_STATIC_DRAW);


=>  m_vertexBuffer = Buffer::CreateWithData(GL_ARRAY_BUFFER, GL_STATIC_DRAW, vertices, sizeof(float) * 12);

// [3] Vertex attribute setting
glGenBuffers(1, &m_indexBuffer);
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * 6, indices, GL_STATIC_DRAW);

=> m_indexBuffer = Buffer::CreateWithData(GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW, indices, sizeof(float) * 6);

```
로 대체될 수 있다!