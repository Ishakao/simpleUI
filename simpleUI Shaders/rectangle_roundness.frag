#version 330
in vec2 fragLocal;
in vec2 fragUV;
in vec4 fragColor;
flat in vec4 fragBorderColor;
flat in float fragUseTex;
flat in vec2 fragSDBounds;
flat in float fragRadius;
flat in float fragBorderThickness;
flat in float fragInset;
uniform sampler2D texture0;
out vec4 finalColor;

float sdRoundBox(vec2 p, vec2 hb, float r) {
	vec2 q = abs(p) - hb;
	return min(max(q.x, q.y), 0.0) + length(max(q, 0.0)) - r;
}

void main() {
	vec2 outerHalf = fragSDBounds + vec2(fragRadius);
	float outerMin = min(outerHalf.x, outerHalf.y);
	float roundness = outerMin > 0.0 ? fragRadius / outerMin : 0.0;

	vec2 innerHalf = max(outerHalf - vec2(fragInset), vec2(0.0));
	float innerR = min(innerHalf.x, innerHalf.y) * roundness;
	float dIn = sdRoundBox(fragLocal, innerHalf - vec2(innerR), innerR);
	float fillCov = 1.0 - smoothstep(-0.5, 0.5, dIn);

	float ringCov = 0.0;
	if (fragBorderThickness > 0.5) {
		float dOut = sdRoundBox(fragLocal, fragSDBounds, fragRadius);
		float halfBorder = fragBorderThickness * 0.5;
		float dOutline = abs(dOut + halfBorder) - halfBorder;
		ringCov = 1.0 - smoothstep(-0.5, 0.5, dOutline);
	}

	vec4 fc = fragColor;
	if (fragUseTex > 0.5) fc *= texture(texture0, fragUV);

	float fa = fc.a * fillCov;
	float ba = fragBorderColor.a * ringCov;
	float oa = ba + fa * (1.0 - ba);
	if (oa <= 0.0) discard;
	vec3 rgb = (fragBorderColor.rgb * ba + fc.rgb * fa * (1.0 - ba)) / oa;
	finalColor = vec4(rgb, oa);
}