// Apex Legends Mobile packed normals, binorm sign and tangents unpacking
// File: Unreal/UnrealMesh/UnMeshTypes.h
// https://github.com/floxay/UEViewer/commit/8f5418b6df4e4db10f123c2a4860e07c3050c08b
// and
// https://github.com/floxay/UEViewer/commit/38177801bfae02d1a40f283d4e001c975516c8c7
FPackedNormal &operator=(const uint16 &InData)
{
	auto x = (byte)(InData & 0xFF);
	auto y = (byte)((InData >> 8) & 0xFF);
	//ugly af, copied the vertex shader glsl code
	FVector2D v27; // = v30;
	float f29;
	v27.X = x;
	v27.Y = y;
	if (((int)(v27.X + 0.5)) > 127 && ((int)(v27.Y + 0.5)) > 127)
	{
		f29 = -1.f;
		v27.X = (v27.X + -128.0f) / 127.0f;
		v27.Y = (v27.Y + -128.0f) / 127.0f;
	}
	else
	{
		f29 = 1.f;
		v27.X /= 127.0f;
		v27.Y /= 127.0f;
	}
	FVector2D v31;
	v31.X = (v27.X * 2) + -1.0f;
	v31.Y = (v27.Y * 2) + -1.0f;
	FVector v32;
	v32.Set(v31.X, v31.Y, 1 + -(1 * fabs(v31.X) + 1 * fabs(v31.Y)));
	FVector v28 = v32;
	if (v32.Z < 0.0f)
	{
		FVector2D v33;
		v33.X = fabs(v32.Y);
		v33.Y = fabs(v32.X);
		FVector2D v34;
		v34.X = v32.X > 0.0f ? 1.0f : -1.0f;
		v34.Y = v32.Y > 0.0f ? 1.0f : -1.0f;
		v28.X = (1.0f + -v33.X) * v34.X;
		v28.Y = (1.0f + -v33.Y) * v34.Y;
	}
	CVec3 temp = (CVec3&)v28;
	temp.Normalize();
	v28 = (FVector&)temp;
	FVector4 v35;
	v35.X = v28.X;
	v35.Y = v28.Y;
	v35.Z = v28.Z;
	v35.W = f29;
	return *this = v35;
}
