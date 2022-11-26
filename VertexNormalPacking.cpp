// Packs given normalized 3D vector into a uint32 by dropping one component.
// 2 bits signifying dropped component, 1 bit for sign, 2x9 bits for other 2 components.
// TODO: Packing tangent (to 10 bits) and setting binorm sign bit.
inline uint32_t pack(float *vector)
{
	uint8_t largestIdx = 0;
	for (uint8_t i = 1; i < 3; i++)
	{
		if (std::abs(vector[i]) >= std::abs(vector[largestIdx]))
		{
			largestIdx = i;
		}
	}

	bool bNegative = vector[largestIdx] < 0.f;
	uint32_t r = (largestIdx << 1) + bNegative;

	// what on earth is going on
	if (largestIdx == 1)
	{
		const float temp = vector[0];
		vector[0] = vector[2];
		vector[2] = temp;
	}

	for (uint8_t i = 0; i < 3; i++)
	{
		if (i != largestIdx)
		{
			uint16_t packedComponent = std::roundf((vector[i] / (vector[largestIdx] / (bNegative ? -255 : 255))) + 256);
			r = ((r << 9) | packedComponent);
		}
	}

	return (r << 10);
}
