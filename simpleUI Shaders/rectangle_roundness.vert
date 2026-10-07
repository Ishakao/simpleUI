#version 330
in vec3 vertexPosition;
in vec4 vertexTexCoord;
in vec3 vertexTexCoord2;
in vec4 vertexColor;
uniform mat4 mvp;
out vec2 fragLocal;
out vec2 fragUV;
out vec4 fragColor;
flat out float fragUseTex;
flat out vec2 fragSDBounds;
flat out float fragRadius;
flat out float fragBorderThickness;
void main() {
    fragLocal = vertexTexCoord.xy;
    fragUV = vertexTexCoord2.xy;
    fragUseTex = vertexTexCoord2.z;
    fragColor = vertexColor;
    vec2 halfSize = vertexTexCoord.zw;
    float b = floor(vertexPosition.z);
    fragBorderThickness = b;
    float roundness = clamp((vertexPosition.z - b) / 0.99, 0.0, 1.0);
    fragRadius = min(halfSize.x, halfSize.y) * roundness;
    fragSDBounds = halfSize - vec2(fragRadius);
    gl_Position = mvp * vec4(vertexPosition.xy, 0.0, 1.0);
}