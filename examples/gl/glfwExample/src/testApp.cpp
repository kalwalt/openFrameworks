#include "testApp.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/half_float.hpp>
#include <glm/gtc/type_precision.hpp>
#include <glm/gtc/type_ptr.hpp>


    GLuint VertexArrayName = 0;
	GLuint ProgramName = 0;
	GLuint BufferName = 0;
	GLint UniformMVP = 0;
	GLint UniformDiffuse = 0;

	GLsizei const VertexCount = 6;
	GLsizeiptr const PositionSize = VertexCount * sizeof(glm::vec2);

	glm::vec2 const PositionData[VertexCount] =
	{
		glm::vec2(-1.0f,-1.0f),
		glm::vec2( 1.0f,-1.0f),
		glm::vec2( 1.0f, 1.0f),
		glm::vec2( 1.0f, 1.0f),
		glm::vec2(-1.0f, 1.0f),
		glm::vec2(-1.0f,-1.0f)
	};

bool initArrayBuffer()
{
	glGenBuffers(1, &BufferName);
    glBindBuffer(GL_ARRAY_BUFFER, BufferName);
    glBufferData(GL_ARRAY_BUFFER, PositionSize, PositionData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
    ofLog(OF_LOG_NOTICE,"initArrayBuffer");
	return 1;  //glf::checkError("initArrayBuffer");
}

bool initVertexArray()
{
	glGenVertexArrays(1, &VertexArrayName);
    glBindVertexArray(VertexArrayName);
    glBindBuffer(GL_ARRAY_BUFFER, BufferName);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

    glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	return 1; //glf::checkError("initVertexArray");
}


//--------------------------------------------------------------
void testApp::setup(){

    shader.load("shaders/instanced");

    initArrayBuffer();
    initVertexArray();

   // glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
	//glm::mat4 ViewTranslate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -Window.TranlationCurrent.y));
	//glm::mat4 ViewRotateX = glm::rotate(ViewTranslate, Window.RotationCurrent.y + 45.0f, glm::vec3(1.f, 0.f, 0.f));
	//glm::mat4 View = glm::rotate(ViewRotateX, Window.RotationCurrent.x + 45.0f, glm::vec3(0.f, 1.f, 0.f));
	//glm::mat4 Model = glm::mat4(1.0f);
	//glm::mat4 MVP = Projection * View * Model;

    ofMatrix4x4 Projection;
    Projection.makePerspectiveMatrix(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);

    ofMatrix4x4 ViewTranslate;
    ViewTranslate.translate(0.0f,0.0f,-1.0f);

    ofMatrix4x4 ViewRotateX;
    ViewRotateX.rotate(45.0f,1.f, 0.f, 0.f);

    ofMatrix4x4 View;
    View.rotate(45.0f,1.f, 0.f, 0.f);

    ofMatrix4x4 Model;
    Model.set(1.0f,1.0f,1.0f,1.0f,1.0f,1.0f,1.0f,1.0f,1.0f,1.0f,1.0f,1.0f,1.0f,1.0f,1.0f,1.0f);

    MVP = Projection * View * Model;



    shader.begin();
    shader.setUniform4f("Diffuse",1.0f, 0.5f, 0.0f, 1.0f);
    shader.setUniformMatrix4f("MVP",  MVP);
    shader.end();
}

//--------------------------------------------------------------
void testApp::update(){
}

//--------------------------------------------------------------
void testApp::draw(){

    glEnable(GL_DEPTH_TEST);
    float Depth(1.0f);
    float zero[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glClearBufferfv(GL_DEPTH, 0, &Depth);
	glClearBufferfv(GL_COLOR, 0, zero);

    shader.begin();

    glBindVertexArray(VertexArrayName);
	glDrawArraysInstanced(GL_TRIANGLES, 0, VertexCount, 5);

    shader.end();


}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){

}
