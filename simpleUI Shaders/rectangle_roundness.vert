#version 330
in vec3 vertexPosition;
in vec2 vertexTexCoord;
in vec4 vertexColor;
uniform mat4 mvp;
out vec2 fragLocal;
out vec4 fragColor;
flat out vec2 fragSDBounds;
flat out float fragRadius;
flat out float fragBorderThickness;
void main() {
    fragLocal = vertexTexCoord;
    fragColor = vertexColor;
    vec2 halfSize = abs(vertexTexCoord) - vec2(1.0);
    float b = floor(vertexPosition.z);
    fragBorderThickness = b;
    float roundness = clamp((vertexPosition.z - b) / 0.99, 0.0, 1.0);
    fragRadius = min(halfSize.x, halfSize.y) * roundness;
    fragSDBounds = halfSize - vec2(fragRadius);
    gl_Position = mvp * vec4(vertexPosition.xy, 0.0, 1.0);
}