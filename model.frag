#version 330 core
out vec4 FragColor;
//in vec2 TexCord;
uniform sampler2D texture0;
uniform sampler2D texture1;
void main(){
//    FragColor=mix(texture(texture0,TexCord),texture(texture1,TexCord),0.5);
//    FragColor=texture(texture0,TexCord*vec2(1.0f,1.0f));
    FragColor=vec4(0.5f,0.0f,0.0f,0.0f);
}
