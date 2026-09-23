#version 330

in vec3 vertexPosition;
in vec2 vertexTexCoord;
in vec4 vertexColor;

uniform mat4 mvp;

out vec2 fragLocal;
out vec4 fragColor;
flat out vec2 fragHalfSize;
flat out float fragRoundness;
flat out float fragBorderThickness;

void main() {
    fragLocal = vertexTexCoord;
    fragColor = vertexColor;
    fragHalfSize = abs(vertexTexCoord) - vec2(1.0);
    float b = floor(vertexPosition.z);
    fragBorderThickness = b;
    fragRoundness = (vertexPosition.z - b) / 0.99;
    gl_Position = mvp * vec4(vertexPosition.xy, 0.0, 1.0);
}