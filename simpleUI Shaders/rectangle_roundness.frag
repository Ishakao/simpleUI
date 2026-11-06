#version 330
in vec2 fragLocal;
in vec2 fragUV;
in vec4 fragColor;
in vec2 fragWorld;
flat in vec4 fragBorderColor;
flat in float fragUseTex;
flat in vec2 fragSDBounds;
flat in float fragRadius;
flat in float fragBorderThickness;
flat in float fragInset;
flat in float fragClip;
flat in float fragShape; // your background shape. base shape: 0
uniform sampler2D texture0;
uniform vec4 clips[256];
out vec4 finalColor;

float sdRoundBox(vec2 p, vec2 hb, float r) {
	vec2 q = abs(p) - hb;
	return min(max(q.x, q.y), 0.0) + length(max(q, 0.0)) - r;
}

float clipSDF(vec2 p, vec4 a, vec4 b) {
	vec2 q = p - a.xy;
	q = vec2(b.x * q.x + b.y * q.y, -b.y * q.x + b.x * q.y);
	vec2 d = abs(q) - a.zw + b.z;
	return length(max(d, 0.0)) + min(max(d.x, d.y), 0.0) - b.z;
}

float clipCoverage(vec2 p, float idxf) {
	if (idxf < 0.0) return 1.0;
	int idx = int(idxf + 0.5);
	float d = -1e9;
	for (int i = 0; i < 8 && idx >= 0; i++) {
		vec4 a = clips[idx * 2];
		vec4 b = clips[idx * 2 + 1];
		d = max(d, clipSDF(p, a, b));
		idx = int(b.w);
	}
	return clamp(0.5 - d, 0.0, 1.0);
}

void main() {
	int shape = int(fragShape + 0.5);

	if (shape == 0) {
		vec2 outerHalf = fragSDBounds + vec2(fragRadius);
		float outerMin = min(outerHalf.x, outerHalf.y);
		float roundness = outerMin > 0.0 ? fragRadius / outerMin : 0.0;

		bool hasB = fragBorderThickness > 0.5;
		float dOut = sdRoundBox(fragLocal, fragSDBounds, fragRadius);

		vec2 innerHalf = max(outerHalf - vec2(fragInset), vec2(0.0));
		float innerR = min(innerHalf.x, innerHalf.y) * roundness;
		float dIn = sdRoundBox(fragLocal, innerHalf - vec2(innerR), innerR);
		float fillCov = 1.0 - smoothstep(-0.5, 0.5, dIn - (hasB ? 1.0 : 0.0));

		float ringCov = 0.0;
		float outerCov = 1.0;
		if (hasB) {
			ringCov = smoothstep(-0.5, 0.5, dOut + fragBorderThickness);
			outerCov = 1.0 - smoothstep(-0.5, 0.5, dOut);
		}

		vec4 fc = fragColor;
		if (fragUseTex > 0.5) fc *= texture(texture0, fragUV);

		float fa = fc.a * fillCov;
		float ba = fragBorderColor.a * ringCov;
		float oa = ba + fa * (1.0 - ba);
		if (oa <= 0.0) discard;
		vec3 rgb = (fragBorderColor.rgb * ba + fc.rgb * fa * (1.0 - ba)) / oa;
		oa *= outerCov;
		oa *= clipCoverage(fragWorld, fragClip);
		if (oa <= 0.0) discard;
		finalColor = vec4(rgb, oa);
	} // here you can create your "shape" branch
}