#version 330

in vec2 fragLocal;
in vec4 fragColor;
flat in vec2 fragHalfSize;
flat in float fragRoundness;
flat in float fragBorderThickness;

out vec4 finalColor;

float sdRoundRect(vec2 p, vec2 b, float r) {
    vec2 q = abs(p) - b + vec2(r);
    return min(max(q.x, q.y), 0.0) + length(max(q, 0.0)) - r;
}

void main() {
    float radius = min(fragHalfSize.x, fragHalfSize.y) * clamp(fragRoundness, 0.0, 1.0);
    float d = sdRoundRect(fragLocal, fragHalfSize, radius);

    float alphaFill = 1.0 - smoothstep(-0.5, 0.5, d);
    float dOutline = abs(d + fragBorderThickness * 0.5) - fragBorderThickness * 0.5;
    float alphaBorder = 1.0 - smoothstep(-0.5, 0.5, dOutline);

    float alpha = mix(alphaFill, alphaBorder, step(0.5, fragBorderThickness));
    finalColor = vec4(fragColor.rgb, fragColor.a * alpha);
}