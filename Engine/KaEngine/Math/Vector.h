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

		union {
			glm::vec2 vec;
			struct { float x, y; };
			float v[2];
		};

	public:
		/// <summary>
		/// ベクトル同士の加算。
		/// </summary>
		/// <param name="v"></param>
		void Add(const Vector2& v)
		{
			vec.x += v.x;
			vec.y += v.y;
		}

		/// <summary>
		/// ベクトル同士の減算。
		/// </summary>
		/// <param name="v"></param>
		void Subtract(const Vector2& v)
		{
			vec.x -= v.x;
			vec.y -= v.y;
		}

		/// <summary>
		/// ベクトルをスカラーで拡大。
		/// </summary>
		/// <param name="s"></param>
		void Scale(const float s)
		{
			vec.x *= s;
			vec.y *= s;
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
			glm::vec2 v;
			v = glm::normalize(vec);
			if (!isnan(v.x)) {
				vec = v;
			}
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
		/// 線形補間。
		/// </summary>
		/// <param name="v0">補完開始のベクトル</param>
		/// <param name="v1">補完終了のベクトル</param>
		/// <param name="t">補完率</param>
		/// <returns></returns>
		void Lerp(const Vector2& v0, const Vector2& v1, const float t)
		{
			vec = glm::mix(v0.vec, v1.vec, t);
		}

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

		/// <summary>
		/// 加算代入演算子。
		/// </summary>
		/// <param name="v"></param>
		/// <returns></returns>
		Vector2& operator+=(const Vector2& v)
		{
			Add(v);
			return *this;
		}

		/// <summary>
		/// 減算代入演算子。
		/// </summary>
		/// <param name="v"></param>
		/// <returns></returns>
		Vector2& operator-=(const Vector2& v)
		{
			Subtract(v);
			return *this;
		}

		/// <summary>
		/// 乗算代入演算子。
		/// </summary>
		/// <param name="s"></param>
		/// <returns></returns>
		Vector2& operator*=(const float s)
		{
			Scale(s);
			return *this;
		}

		/// <summary>
		/// 除算代入演算子。
		/// </summary>
		/// <param name="s"></param>
		/// <returns></returns>
		Vector2& operator/=(const float s)
		{
			Div(s);
			return *this;
		}

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
		static const Vector3 AxisX;
		static const Vector3 AxisY;
		static const Vector3 AxisZ;

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
		/// ベクトルを設定。
		/// </summary>
		/// <param name="x"></param>
		/// <param name="y"></param>
		/// <param name="z"></param>
		void Set(const float x, const float y, const float z)
		{
			vec.x = x;
			vec.y = y;
			vec.z = z;
		}

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
			glm::vec3 v;
			v = glm::normalize(vec);
			if (!isnan(v.x)) {
				vec = v;
			}
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
		/// 線形補間。
		/// </summary>
		/// <param name="v0">補完開始のベクトル</param>
		/// <param name="v1">補完終了のベクトル</param>
		/// <param name="t">補完率</param>
		/// <returns></returns>
		void Lerp(const Vector3& v0, const Vector3& v1, const float t)
		{
			vec = glm::mix(v0.vec, v1.vec, t);
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
		/// ベクトルを設定。
		/// </summary>
		/// <param name="x"></param>
		/// <param name="y"></param>
		/// <param name="z"></param>
		/// <param name="w"></param>
		void Set(const float x, const float y, const float z, const float w)
		{
			vec.x = x;
			vec.y = y;
			vec.z = z;
			vec.w = w;
		}


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
		/// 線形補間。
		/// </summary>
		/// <param name="v0">補完開始のベクトル</param>
		/// <param name="v1">補完終了のベクトル</param>
		/// <param name="t">補完率</param>
		/// <returns></returns>
		void Lerp(const Vector4& v0, const Vector4& v1, const float t)
		{
			vec = glm::mix(v0.vec, v1.vec, t);
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
		/// クォータニオン同士の乗算。
		/// </summary>
		/// <param name="rot0"></param>
		/// <param name="rot1"></param>
		void Multiply(const Quaternion& rot0, const Quaternion& rot1)
		{
			float pw, px, py, pz;
			float qw, qx, qy, qz;

			qw = rot0.w; qx = rot0.x; qy = rot0.y; qz = rot0.z;
			pw = rot1.w; px = rot1.x; py = rot1.y; pz = rot1.z;

			w = pw * qw - px * qx - py * qy - pz * qz;
			x = pw * qx + px * qw + py * qz - pz * qy;
			y = pw * qy - px * qz + py * qw + pz * qx;
			z = pw * qz + px * qy - py * qx + pz * qw;
		}

		/// <summary>
		/// X軸周りの回転クォータニオンを作成(単位Radian)。
		/// </summary>
		/// <param name="angle"></param>
		void SetRotationX(const float angle)
		{
			SetRotation(Vector3::AxisX, angle);
		}

		/// <summary>
		/// X軸周りの回転クォータニオンを作成(単位Degree)。
		/// </summary>
		/// <param name="angle"></param>
		void SetRotationDegX(const float angle)
		{
			SetRotation(Vector3::AxisX, Mathf::DegToRad(angle));
		}

		/// <summary>
		/// Y軸周りの回転クォータニオンを作成(単位Radian)。
		/// </summary>
		/// <param name="angle"></param>
		void SetRotationY(const float angle)
		{
			SetRotation(Vector3::AxisY, angle);
		}

		/// <summary>
		/// Y軸周りの回転クォータニオンを作成(単位Degree)。
		/// </summary>
		/// <param name="angle"></param>
		void SetRotationDegY(const float angle)
		{
			SetRotation(Vector3::AxisY, Mathf::DegToRad(angle));
		}

		/// <summary>
		/// Z軸周りの回転クォータニオンを作成(単位Radian)。
		/// </summary>
		/// <param name="angle"></param>
		void SetRotationZ(const float angle)
		{
			SetRotation(Vector3::AxisZ, angle);
		}

		/// <summary>
		/// Z軸周りの回転クォータニオンを作成(単位Degree)。
		/// </summary>
		/// <param name="angle"></param>
		void SetRotationDegZ(const float angle)
		{
			SetRotation(Vector3::AxisZ, Mathf::DegToRad(angle));
		}

		/// <summary>
		/// X軸周りの回転クォータニオンを加算(単位Radian)。
		/// </summary>
		/// <param name="angle"></param>
		void AddRotationX(float angle)
		{
			Quaternion addRot;
			addRot.SetRotation(Vector3::AxisX, angle);
			*this *= addRot;
		}

		/// <summary>
		/// X軸周りの回転クォータニオンを加算(単位Degree)。
		/// </summary>
		/// <param name="angle"></param>
		void AddRotationDegX(float angle)
		{
			Quaternion addRot;
			addRot.SetRotation(Vector3::AxisX, Mathf::DegToRad(angle));
			*this *= addRot;
		}

		/// <summary>
		/// Y軸周りの回転クォータニオンを加算(単位Radian)。
		/// </summary>
		/// <param name="angle"></param>
		void AddRotationY(float angle)
		{
			Quaternion addRot;
			addRot.SetRotation(Vector3::AxisY, angle);
			*this *= addRot;
		}

		/// <summary>
		/// Y軸周りの回転クォータニオンを加算(単位Degree)。
		/// </summary>
		/// <param name="angle"></param>
		void AddRotationDegY(float angle)
		{
			Quaternion addRot;
			addRot.SetRotation(Vector3::AxisY, Mathf::DegToRad(angle));
			*this *= addRot;
		}

		/// <summary>
		/// Z軸周りの回転クォータニオンを加算(単位Radian)。
		/// </summary>
		/// <param name="angle"></param>
		void AddRotationZ(float angle)
		{
			Quaternion addRot;
			addRot.SetRotation(Vector3::AxisZ, angle);
			*this *= addRot;
		}

		/// <summary>
		/// Z軸周りの回転クォータニオンを加算(単位Degree)。
		/// </summary>
		/// <param name="angle"></param>
		void AddRotationDegZ(float angle)
		{
			Quaternion addRot;
			addRot.SetRotation(Vector3::AxisZ, Mathf::DegToRad(angle));
			*this *= addRot;
		}

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

		/// <summary>
		/// fromベクトルからtoベクトルに回転させるクォータニオンを作成。
		/// </summary>
		/// <param name="from"></param>
		/// <param name="to"></param>
		void SetRotationFromVector(const Vector3& from, const Vector3& to)
		{
			glm::quat quat;
			quat.x = vec.x;
			quat.y = vec.y;
			quat.z = vec.z;
			quat.w = vec.w;
			quat = glm::rotation(to.vec, from.vec);
			Set(quat.x, quat.y, quat.z, quat.w);
		}

		/// <summary>
		/// ベクトルにクォータニオンを適用。
		/// </summary>
		/// <param name="v"></param>
		void Apply(Vector3& v)
		{
			glm::quat quat;
			quat.x = vec.x;
			quat.y = vec.y;
			quat.z = vec.z;
			quat.w = vec.w;
			v.vec = glm::rotate(quat, v.vec);
		}

		/// <summary>
		/// 乗算代入演算子。
		/// </summary>
		const Quaternion& operator*=(const Quaternion& rot)
		{
			Multiply(rot, *this);
			return *this;
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
}