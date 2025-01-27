﻿#version 330 core

layout(location = 0) in vec3 aVertexPosition;
layout(location = 1) in vec3 aVertexNormal;
layout(location = 2) in vec2 aVertexTexcoords;

void main() {
    vec4 vertexPosition = vec4(aVertexPosition, 1);
    gl_Position = vertexPosition;
}