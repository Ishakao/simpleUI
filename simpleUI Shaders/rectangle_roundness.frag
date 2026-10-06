#version 330
in vec2 fragLocal;
in vec4 fragColor;
flat in vec2 fragSDBounds;
flat in float fragRadius;
flat in float fragBorderThickness;
out vec4 finalColor;
void main() {
    vec2 q = abs(fragLocal) - fragSDBounds;
    float d = min(max(q.x, q.y), 0.0) + length(max(q, 0.0)) - fragRadius;
    float alpha;
    if (fragBorderThickness > 0.5) {
        float halfBorder = fragBorderThickness * 0.5;
        float dOutline = abs(d + halfBorder) - halfBorder;
        alpha = 1.0 - smoothstep(-0.5, 0.5, dOutline);
    } else {
        alpha = 1.0 - smoothstep(-0.5, 0.5, d);
    }
    finalColor = vec4(fragColor.rgb, fragColor.a * alpha);
}