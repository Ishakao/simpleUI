#version 330
in vec2 fragLocal;
in vec2 fragUV;
in vec4 fragColor;
flat in float fragUseTex;
flat in vec2 fragSDBounds;
flat in float fragRadius;
flat in float fragBorderThickness;
uniform sampler2D texture0;
out vec4 finalColor;
void main() {
    float alpha = 1.0;
    if (fragUseTex < 0.5 || fragRadius > 0.0) {
        vec2 q = abs(fragLocal) - fragSDBounds;
        float d = min(max(q.x, q.y), 0.0) + length(max(q, 0.0)) - fragRadius;
        if (fragBorderThickness > 0.5) {
            float halfBorder = fragBorderThickness * 0.5;
            float dOutline = abs(d + halfBorder) - halfBorder;
            alpha = 1.0 - smoothstep(-0.5, 0.5, dOutline);
        } else {
            alpha = 1.0 - smoothstep(-0.5, 0.5, d);
        }
    }
    vec4 c = fragColor;
    if (fragUseTex > 0.5) c *= texture(texture0, fragUV);
    finalColor = vec4(c.rgb, c.a * alpha);
}