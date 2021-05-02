#pragma once
namespace RBT
{
	struct Color
	{
		float R;
		float G;
		float B;
		Color()
		{
			R = 0.0f;
			G = 0.0f;
			B = 0.0f;
		}
		Color(float R, float G, float B)
		{
			this->R = R;
			this->G = G;
			this->B = B;
		}
		static Color fromRGB(int R, int G, int B)
		{
			return Color
			(
				R / 255.0F,
				G / 255.0F,
				B / 255.0F
			);
		}
	};
}