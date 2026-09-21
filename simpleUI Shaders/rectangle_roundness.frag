#version 330

in vec2 fragTexCoord;
out vec4 finalColor;

uniform vec2 rectSize;
uniform float roundness;
uniform vec4 color;

float sdRoundRect(vec2 p, vec2 b, float r) {
    vec2 q = abs(p) - b + vec2(r);
    return min(max(q.x, q.y), 0.0) + length(max(q, 0.0)) - r;
}

void main() {
    vec2 halfSize = rectSize / 2.0;
    float radius = min(halfSize.x, halfSize.y) * clamp(roundness, 0.0, 1.0);
    vec2 p = (fragTexCoord - 0.5) * rectSize;
    float d = sdRoundRect(p, halfSize, radius);
    float alpha = 1.0 - smoothstep(-1.0, 0.0, d);
    finalColor = vec4(color.rgb, color.a * alpha);
}