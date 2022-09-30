// Packs given normalized 3D vector into a uint32 by dropping one component.
// 2 bits signifying dropped component, 1 bit for sign, 2x9 bits for other 2 components.
// TODO: Packing tangent (to 10 bits) and setting binorm sign bit.
uint32_t pack(float v1, float v2, float v3)
{
	int16_t v90, v91;
	uint8_t sign = 0, droppedComponent = 0;
	float s;

	float f1 = std::abs(v1);
	float f2 = std::abs(v2);
	float f3 = std::abs(v3);

	if (f1 >= f2 && f1 >= f3)
		droppedComponent = 0;
	else if (f2 >= f1 && f2 >= f3)
		droppedComponent = 1;
	else
		droppedComponent = 2;

	switch (droppedComponent)
	{
	case 0:
		sign = v1 < 0 ? 1 : 0;
		s = v1 / (sign ? -255 : 255);
		v91 = (int16_t)std::roundf((v2 / s) + 256);
		v90 = (int16_t)std::roundf((v3 / s) + 256);
		break;
	case 1:
		sign = v2 < 0 ? 1 : 0;
		s = v2 / (sign ? -255 : 255);
		v90 = (int16_t)std::roundf((v1 / s) + 256);
		v91 = (int16_t)std::roundf((v3 / s) + 256);
		break;
	case 2:
		sign = v3 < 0 ? 1 : 0;
		s = v3 / (sign ? -255 : 255);
		v91 = (int16_t)std::roundf((v1 / s) + 256);
		v90 = (int16_t)std::roundf((v2 / s) + 256);
		break;
	default:
		break;
	}

	return (droppedComponent << 29) + (sign << 28) + (v91 << 19) + (v90 << (19 - 9));
}
