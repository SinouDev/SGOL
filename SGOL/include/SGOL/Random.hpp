#pragma once

#include "Math.hpp"

#include <cstdlib>

namespace SGOL {

	class Random
	{
	public:

		static __SGOL_INLINE void __SGOL_FASTCALL Init()
		{

		}

		static __SGOL_INLINE double __SGOL_FASTCALL RandomDouble()
		{
			// Returns a random real in [0,1).
			return rand() / (RAND_MAX + 1.0f);
		}

		static __SGOL_INLINE double __SGOL_FASTCALL RandomDouble(double min, double max)
		{
			// Returns a random real in [min,max).
			return min + (max - min) * RandomDouble();
		}

		static __SGOL_INLINE int32_t __SGOL_FASTCALL RandomInt()
		{
			return static_cast<int32_t>(RandomDouble());
		}

		static __SGOL_INLINE int32_t __SGOL_FASTCALL RandomInt(int32_t min, int32_t max)
		{
			return static_cast<int32_t>(RandomDouble(min, max));
		}

		static __SGOL_INLINE float __SGOL_FASTCALL RandomFloat()
		{
			return static_cast<float>(RandomDouble());
		}

		static __SGOL_INLINE float __SGOL_FASTCALL RandomFloat(float min, float max)
		{
			return static_cast<float>(RandomDouble(min, max));
		}

		template<typename T>
		static __SGOL_INLINE T __SGOL_FASTCALL GetRandom()
		{
			return static_cast<T>(RandomDouble());
		}

		template<typename T>
		static __SGOL_INLINE T __SGOL_FASTCALL GetRandom(T min, T max)
		{
			return static_cast<T>(RandomDouble(min, max));
		}

		static __SGOL_INLINE SGOL::Math::Vec3 __SGOL_FASTCALL RandomVec3()
		{
			return { RandomDouble(), RandomDouble(), RandomDouble() };
		}

		static __SGOL_INLINE SGOL::Math::Vec3 __SGOL_FASTCALL RandomVec3(double min, double max)
		{
			return { RandomDouble(min, max), RandomDouble(min,  max), RandomDouble(min, max) };
		}

		static __SGOL_INLINE SGOL::Math::Vec3 __SGOL_FASTCALL RandomInUnitSphere()
		{
			//return Random::RandomVec3(-1.0, 1.0);
			while (true)
			{
				SGOL::Math::Vec3 p = Random::RandomVec3(-1.0, 1.0);
				if (SGOL::Math::Dot(p, p) >= 1.0f)
					continue;
				return p;
			}
		}

		static __SGOL_INLINE SGOL::Math::Vec3 __SGOL_FASTCALL RandomInUnitDisk()
		{
			//return Random::RandomVec3(-1.0, 1.0);
			while (true)
			{
				SGOL::Math::Vec3 p = SGOL::Math::Vec3(Random::RandomDouble(-1.0, 1.0), Random::RandomDouble(-1.0, 1.0), 0.0);
				if (SGOL::Math::Dot(p, p) >= 1.0f)
					continue;
				return p;
			}
		}

		static __SGOL_INLINE SGOL::Math::Vec3 __SGOL_FASTCALL RandomUnitVector()
		{
			SGOL::Math::Vec3 tmp = RandomInUnitSphere();
			return tmp / SGOL::Math::Q_Length(tmp);
		}

		static __SGOL_INLINE SGOL::Math::Vec3 __SGOL_FASTCALL RandomInHemisphere(SGOL::Math::Vec3& normal)
		{
			SGOL::Math::Vec3 in_unit_sphere = RandomInUnitSphere();
			if (SGOL::Math::Dot(in_unit_sphere, normal) > 0.0f)
			{
				return in_unit_sphere;
			}
			else
			{
				return -in_unit_sphere;
			}
		}
	};
}