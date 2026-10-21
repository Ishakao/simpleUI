#version 330
layout(location = 0) in vec2 corner;
layout(location = 6) in vec4 iPosSize;
layout(location = 7) in vec4 iOriginRotZ;
layout(location = 8) in vec4 iDest;
layout(location = 9) in vec4 iUV;
layout(location = 10) in vec4 iColor;
layout(location = 11) in vec4 iBorderColor;
layout(location = 12) in float iInset;

uniform mat4 mvp;

out vec2 fragLocal;
out vec2 fragUV;
out vec4 fragColor;
flat out vec4 fragBorderColor;
flat out float fragUseTex;
flat out vec2 fragSDBounds;
flat out float fragRadius;
flat out float fragBorderThickness;
flat out float fragInset;

void main() {
	vec2 halfSize = iPosSize.zw * 0.5;
	vec2 center = iPosSize.xy + halfSize;
	vec2 org = iPosSize.xy + iOriginRotZ.xy;
	float useTex = iDest.z > 0.0 ? 1.0 : 0.0;

	vec2 mn = useTex > 0.5 ? iDest.xy - center : -halfSize - 1.0;
	vec2 mx = useTex > 0.5 ? mn + iDest.zw : halfSize + 1.0;
	vec2 l = mix(mn, mx, corner);

	vec2 d = center + l - org;
	float s = sin(iOriginRotZ.z);
	float co = cos(iOriginRotZ.z);
	vec2 p = org + vec2(d.x * co - d.y * s, d.x * s + d.y * co);

	float z = iOriginRotZ.w;
	float b = floor(z);
	fragBorderThickness = b;
	float roundness = clamp((z - b) / 0.99, 0.0, 1.0);
	fragRadius = min(halfSize.x, halfSize.y) * roundness;
	fragSDBounds = halfSize - vec2(fragRadius);

	fragLocal = l;
	fragUV = mix(iUV.xy, iUV.zw, corner);
	fragUseTex = useTex;
	fragColor = iColor;
	fragBorderColor = iBorderColor;
	fragInset = iInset;

	gl_Position = mvp * vec4(p, 0.0, 1.0);
}