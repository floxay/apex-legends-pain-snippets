struct RMdlPackedVertexTBN
{
	uint32_t _Value;

	// uint32_t _Value = 0b11011111111111111111110000110010;
	//                     ^
	//        binorm sign==|^^
	//                      ||^
	//norm dropped component|||^^^^^^^^^
	//             norm sign==|  norm1  ^^^^^^^^^
	//                                    norm2  ^^^^^^^^^^
	//                                           packedTangent

	Math::Vector3 UnpackNormal()
	{
		... // see code in LegionPlus repo; ./Legion/rmdlstructs.h/RMdlPackedVertexNormal/Unpack()
	}

	// unpack packed tangent from 10 bits + normalized normal vector
	Math::Vector3 UnpackTangent(Math::Vector3 Normal)
	{
		float r2y = 1 + Normal.Z;
		r2y = 1.f / r2y;
		float r2z = -r2y * Normal.X;
		float r2w = Normal.Y * Normal.Y;
		float r3x = r2z * Normal.Y;
		float r4x = -r2y * r2w + 1;
		float r4y = -Normal.X;
		float r4z = -Normal.Y;
		float r3z = r2z * Normal.X + 1;
		float r3y;
		float r3w = r4y;
		if (Normal.Z < -0.999899983)
		{
			r2y = 0;
			r2z = -1;
			r2w = 0;
		}
		else
		{
			r2y = r3z;
			r2z = r3x;
			r2w = r3w;
		}
		float r4w = r3x;
		if (Normal.Z < -0.999899983)
		{
			r3x = -1;
			r3y = 0;
			r3z = 0;
		}
		else
		{
			r3x = r4w;
			r3y = r4x;
			r3z = r4z;
		}

		float x = (_Value & 1023) * 0.00614192151;
		float r2x = sin(x);
		r4x = cos(x);
		r3x *= r2x;
		r3y *= r2x;
		r3z *= r2x;
		r2x = r2y * r4x + r3x;
		r2y = r2z * r4x + r3y;
		r2z = r2w * r4x + r3z;

		// normalizing
		float r1w = r2x * r2x + r2y * r2y + r2z * r2z;
		r1w = 1.f / sqrt(r1w);
		r2x *= r1w;
		r2y *= r1w;
		r2z *= r1w;

		return Math::Vector3(r2x, r2y, r2z);
	}

	int8_t GetBitangentSign()
	{
		return _Value >> 31 ? -1 : 1;
	}
};
