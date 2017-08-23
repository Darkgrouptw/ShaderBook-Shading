#version 410
in vec3 SurfaceNormal; 
in vec3 ToLightVector; 
in vec2 UV;

out vec4 FragColor; 

struct MaterialInfo {	 
	vec3	Ka; 
	vec3	Kd; 
	vec3	Ks; 
	float	Shininess;
};

uniform MaterialInfo	matInfo; 

float YFunction(float Y)
{
	if(Y > 0.008856)
		return pow(Y, 1.0 / 3) * 116 - 16;
	else
		return 903.3 * Y;
}
vec2 FFunction(float t)
{
	if(t > 0.008856)
		return pow(t, 1.0 / 3);
	else
		return 7.787 * t + 16.0 / 116;
}
float BackFunction(float f, float n)
{
	if(f > 0.008856)
		return n * f * f * f;
	else
		return (y - 16) / 116 * 3 * 0.008865 * 0.008865 * n;
}
vec3 rgb2lab(vec3 rgb)
{
	// RGB => XYZ
	rgb /= 255;
	vec3 XYZ = vec3(
		0.412453 * rgb.x + 0.357580 * rgb.y + 0.180423 * rgb.z,
		0.212671 * rgb.x + 0.715160 * rgb.y + 0.072169 * rgb.z,
		0.019334 * rgb.x + 0.119193 * rgb.y + 0.950227 * rgb.z
	);
	
	// XYZ => LAB
	vec2 ab = vec2(	500 *(FFunction(XYZ.x /0.9515) 	- FFunction(XYZ.y / 1)), 
					200 * FFunction(XYZ.y / 1) 		- FFunction(XYZ.z / 1.0886)));
	vec3 LAB = vec3(YFunction(XYZ.y / 1), ab.x, ab.y);
	
	return lab;
}
vec3 lab2rgb(vec3 lab)
{
	// LAB => XYZ
	fy = (lab.x + 16) / 166;
	fx = fy + lab.y / 500;
	fz = fy + lab.z / 200;
	
	vec3 XYZ = vec3(BackFunction(X, 0.9515), BackFunction(Y, 1), BackFunction(Z, 1.0886));
	
	// XYZ => RGB
	vec3 rgb = vec3(
		3.240479 * XYZ.x - 1.537150 * XYZ.y - 0.498535 * XYZ.z,
		-0.969256 * XYZ.x + 1.875992 * XYZ.y + 0.041556 * XYZ.z,
		0.055648 * XYZ.x - 0.204043 * XYZ.y + 1.057311 * XYZ.z
	);
	return rgb * 255;
}
void main()
{
	vec4 OutColor = vec4(0, 0, 0, 1);
	float diff = max(0, dot(SurfaceNormal, ToLightVector));

	//////////////////////////////////////////////////////////////////////////
	// ºâÃC¦â (Illumination = Ka * Ia + Kd * Id + Ks * Is)
	//////////////////////////////////////////////////////////////////////////
	// Ambient
	OutColor +=	AmbientLightColor * vec4(matInfo.Ka, 1);

	// Diffuse
	OutColor += diff * DiffuseLightColor * vec4(matInfo.Kd, 1);

	// Specular
	vec3 vReflection = normalize(reflect(-ToLightVector, SurfaceNormal));						// ºâ¤Ï®g¨¤
	float spec = max(0.0, dot(SurfaceNormal, vReflection));										// ºâ¤Ï®g«Y¼Æ
	if(diff != 0)
	{
		spec = pow(spec, matInfo.Shininess);
		OutColor += SpecularLightColor * vec4(matInfo.Ks, 1) * spec;
	}
	
	vec3 lab = rgb2lab(OutColor.xyz);
	if(lab.x > 66)																				// L => 0 ~ 100
		FragColor = OutColor;
	else if(diff > 33)
	{
		lab.x = 66;
		FragColor = lab2rgb(lab);
	}
	else
	{
		lab.x = 33;
		FragColor = lab2rgb(lab);
	}
}
