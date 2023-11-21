#pragma once

namespace nsKaEngine {

	/// <summary>
	/// 二次元ベクトルクラス。
	/// </summary>
	class Vector2
	{
	public:
		static const Vector2 Zero;
		static const Vector2 One;
		static const Vector2 DEFAULT_PIVOT;

	public:
		/// <summary>
		/// コンストラクタ。
		/// </summary>
		explicit Vector2()
		{
			x = 0.0f;
			y = 0.0f;
		}
		Vector2(const float x, const float y)
		{
			this->x = x;
			this->y = y;
		}

		/// <summary>
		/// デストラクタ。
		/// </summary>
		~Vector2() {}

		/// <summary>
		/// 代入演算子。
		/// </summary>
		/// <param name="v"></param>
		/// <returns></returns>
		Vector2& operator=(const Vector2& v)
		{
			vec = v.vec;
			return *this;
		}

		union {
			glm::vec2 vec;
			struct { float x, y; };
			float v[2];
		};
	};


	/// <summary>
	/// 三次元ベクトルクラス。
	/// </summary>
	class Vector3
	{
	public:
		static const Vector3 Zero;
		static const Vector3 One;
		static const Vector3 Up;
		static const Vector3 Forward;
		static const Vector3 Backward;

	public:
		/// <summary>
		/// コンストラクタ。
		/// </summary>	
		explicit Vector3()
		{
			x = 0.0f;
			y = 0.0f;
			z = 0.0f;
		}
		Vector3(const float x, const float y, const float z)
		{
			this->x = x;
			this->y = y;
			this->z = z;
		}

		/// <summary>
		/// デストラクタ。
		/// </summary>
		~Vector3() {}

		union {
			glm::vec3 vec;
			struct { float x, y, z; };
			float v[3];
		};

	public:
		/// <summary>
		/// ベクトル同士の加算。
		/// </summary>
		/// <param name="v"></param>
		void Add(const Vector3& v)
		{
			vec.x += v.x;
			vec.y += v.y;
			vec.z += v.z;
		}

		/// <summary>
		/// ベクトル同士の減算。
		/// </summary>
		/// <param name="v"></param>
		void Subtract(const Vector3& v)
		{
			vec.x -= v.x;
			vec.y -= v.y;
			vec.z -= v.z;
		}

		/// <summary>
		/// ベクトルをスカラーで拡大。
		/// </summary>
		/// <param name="s"></param>
		void Scale(const float s)
		{
			vec.x *= s;
			vec.y *= s;
			vec.z *= s;
		}

		/// <summary>
		/// ベクトルをスカラーで除算。
		/// </summary>
		/// <param name="s"></param>
		void Div(const float s)
		{
			float scale = 1.0f / s;
			Scale(scale);
		}

		/// <summary>
		/// 正規化をする。
		/// </summary>
		void Normalize()
		{
			vec = glm::normalize(vec);
		}

		/// <summary>
		/// 内積を計算。
		/// </summary>
		/// <param name="v"></param>
		/// <returns></returns>
		const float Dot(const Vector3& v) const
		{
			return glm::dot(vec, v.vec);
		}

		/// <summary>
		/// 外積を計算。
		/// </summary>
		/// <param name="v"></param>
		void Cross(const Vector3& v)
		{
			vec = glm::cross(vec, v.vec);
		}

		/// <summary>
		/// 外積を計算。
		/// </summary>
		/// <param name="v0"></param>
		/// <param name="v1"></param>
		void Cross(const Vector3& v0, const Vector3& v1)
		{
			vec = glm::cross(v0.vec, v1.vec);
		}

		/// <summary>
		/// ベクトルの長さを取得。
		/// </summary>
		/// <returns></returns>
		const float Length() const
		{
			return glm::length(vec);
		}

		/// <summary>
		/// ベクトルの長さの2乗を取得。
		/// </summary>
		/// <returns></returns>
		const float LengthSq() const
		{
			return glm::length2(vec);
		}

		/// <summary>
		/// 代入演算子。
		/// </summary>
		/// <param name="v"></param>
		/// <returns></returns>
		Vector3& operator=(const Vector3& v)
		{
			vec = v.vec;
			return *this;
		}

		/// <summary>
		/// 加算代入演算子。
		/// </summary>
		/// <param name="v"></param>
		/// <returns></returns>
		Vector3& operator+=(const Vector3& v)
		{
			Add(v);
			return *this;
		}

		/// <summary>
		/// 減算代入演算子。
		/// </summary>
		/// <param name="v"></param>
		/// <returns></returns>
		Vector3& operator-=(const Vector3& v)
		{
			Subtract(v);
			return *this;
		}

		/// <summary>
		/// 乗算代入演算子。
		/// </summary>
		/// <param name="s"></param>
		/// <returns></returns>
		Vector3& operator*=(const float s)
		{
			Scale(s);
			return *this;
		}

		/// <summary>
		/// 除算代入演算子。
		/// </summary>
		/// <param name="s"></param>
		/// <returns></returns>
		Vector3& operator/=(const float s)
		{
			Div(s);
			return *this;
		}
	};


	/// <summary>
	/// 四次元ベクトルクラス。
	/// </summary>
	class Vector4
	{
	public:
		static const Vector4 White;
		static const Vector4 Black;
		static const Vector4 Red;
		static const Vector4 Green;
		static const Vector4 Blue;
		static const Vector4 Gray;

	public:
		/// <summary>
		/// コンストラクタ。
		/// </summary>	
		explicit Vector4()
		{
			x = 0.0f;
			y = 0.0f;
			z = 0.0f;
			w = 0.0f;
		}
		Vector4(const float x, const float y, const float z, const float w)
		{
			this->x = x;
			this->y = y;
			this->z = z;
			this->w = w;
		}

		/// <summary>
		/// デストラクタ。
		/// </summary>
		~Vector4() {}

		union {
			glm::vec4 vec;
			struct { float x, y, z, w; };
			struct { float r, g, b, a; };
			float v[4];
		};

	public:
		/// <summary>
		/// ベクトル同士の加算。
		/// </summary>
		/// <param name="v"></param>
		void Add(const Vector4& v)
		{
			vec.x += v.x;
			vec.y += v.y;
			vec.z += v.z;
			vec.w += v.w;
		}

		/// <summary>
		/// ベクトル同士の減算。
		/// </summary>
		/// <param name="v"></param>
		void Subtract(const Vector4& v)
		{
			vec.x -= v.x;
			vec.y -= v.y;
			vec.z -= v.z;
			vec.w -= v.w;
		}

		/// <summary>
		/// ベクトルをスカラーで拡大。
		/// </summary>
		/// <param name="s"></param>
		void Scale(const float s)
		{
			vec.x *= s;
			vec.y *= s;
			vec.z *= s;
			vec.w *= s;
		}

		/// <summary>
		/// ベクトルをスカラーで除算。
		/// </summary>
		/// <param name="s"></param>
		void Div(const float s)
		{
			float scale = 1.0f / s;
			Scale(scale);
		}

		/// <summary>
		/// 正規化をする。
		/// </summary>
		void Normalize()
		{
			vec = glm::normalize(vec);
		}

		/// <summary>
		/// 内積を計算。
		/// </summary>
		/// <param name="v"></param>
		/// <returns></returns>
		const float Dot(const Vector4& v) const
		{
			return glm::dot(vec, v.vec);
		}


		/// <summary>
		/// ベクトルの長さを取得。
		/// </summary>
		/// <returns></returns>
		const float Length() const
		{
			return glm::length(vec);
		}

		/// <summary>
		/// ベクトルの長さの2乗を取得。
		/// </summary>
		/// <returns></returns>
		const float LengthSq() const
		{
			return glm::length2(vec);
		}

		/// <summary>
		/// 代入演算子。
		/// </summary>
		/// <param name="v"></param>
		/// <returns></returns>
		Vector4& operator=(const Vector4& v)
		{
			vec = v.vec;
			return *this;
		}

		/// <summary>
		/// 加算代入演算子。
		/// </summary>
		/// <param name="v"></param>
		/// <returns></returns>
		Vector4& operator+=(const Vector4& v)
		{
			Add(v);
			return *this;
		}

		/// <summary>
		/// 減算代入演算子。
		/// </summary>
		/// <param name="v"></param>
		/// <returns></returns>
		Vector4& operator-=(const Vector4& v)
		{
			Subtract(v);
			return *this;
		}

		/// <summary>
		/// 乗算代入演算子。
		/// </summary>
		/// <param name="s"></param>
		/// <returns></returns>
		Vector4& operator*=(const float s)
		{
			Scale(s);
			return *this;
		}

		/// <summary>
		/// 除算代入演算子。
		/// </summary>
		/// <param name="s"></param>
		/// <returns></returns>
		Vector4& operator/=(const float s)
		{
			Div(s);
			return *this;
		}
	};


	/// <summary>
	/// クォータニオンクラス。
	/// </summary>
	class Quaternion : public Vector4
	{
	public:
		static const Quaternion Identity;

		/// <summary>
		/// コンストラクタ。
		/// </summary>
		Quaternion()
		{
			x = y = z = 0.0f;
			w = 1.0f;
		}
		Quaternion(const float x, const float y, const float z, const float w)
		{
			Vector4(x, y, z, w);
		}

	public:
		/// <summary>
		/// 任意の軸周りの回転クォータニオンを作成。
		/// </summary>
		/// <param name="axis">回転軸</param>
		/// <param name="angle">回転角度。単位ラジアン</param>
		void SetRotation(const Vector3& axis, float angle)
		{
			float halfAngle = angle * 0.5f;
			float s = sinf(halfAngle);
			w = cosf(halfAngle);
			x = axis.x * s;
			y = axis.y * s;
			z = axis.z * s;
		}
	};


	/// <summary>
	/// ベクトル同士の加算。
	/// </summary>
	static Vector3 operator+(const Vector3& v0, const Vector3& v1)
	{
		Vector3 result;
		result.x = v0.x + v1.x;
		result.y = v0.y + v1.y;
		result.z = v0.z + v1.z;
		return result;
	}

	/// <summary>
	/// ベクトル同士の減算。
	/// </summary>
	static Vector3 operator-(const Vector3& v0, const Vector3& v1)
	{
		Vector3 result;
		result.x = v0.x - v1.x;
		result.y = v0.y - v1.y;
		result.z = v0.z - v1.z;
		return result;
	}

	/// <summary>
	/// ベクトルとスカラーの乗算。
	/// </summary>
	static Vector3 operator*(const Vector3& v, const float s)
	{
		Vector3 result = v;
		result.Scale(s);
		return result;
	}

	/// <summary>
	/// ベクトルとスカラーの乗算。
	/// </summary>
	static Vector3 operator*(const float s, const Vector3& v)
	{
		Vector3 result = v;
		result.Scale(s);
		return result;
	}

	/// <summary>
	/// ベクトルとスカラーの除算。
	/// </summary>
	static Vector3 operator/(const Vector3& v, const float s)
	{
		Vector3 result = v;
		result.Div(s);
		return result;
	}

	/// <summary>
	/// ベクトルとスカラーの除算。
	/// </summary>
	static Vector3 operator/(const float s, const Vector3& v)
	{
		Vector3 result = v;
		result.Div(s);
		return result;
	}
}