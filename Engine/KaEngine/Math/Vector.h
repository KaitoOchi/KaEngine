#pragma once

namespace nsKaEngine {

	/// <summary>
	/// �񎟌��x�N�g���N���X�B
	/// </summary>
	class Vector2
	{
	public:
		static const Vector2 Zero;
		static const Vector2 One;
		static const Vector2 DEFAULT_PIVOT;

	public:
		/// <summary>
		/// �R���X�g���N�^�B
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
		/// �f�X�g���N�^�B
		/// </summary>
		~Vector2() {}

		/// <summary>
		/// ������Z�q�B
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
	/// �O�����x�N�g���N���X�B
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
		/// �R���X�g���N�^�B
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
		/// �f�X�g���N�^�B
		/// </summary>
		~Vector3() {}

		union {
			glm::vec3 vec;
			struct { float x, y, z; };
			float v[3];
		};

	public:
		/// <summary>
		/// �x�N�g�����m�̉��Z�B
		/// </summary>
		/// <param name="v"></param>
		void Add(const Vector3& v)
		{
			vec.x += v.x;
			vec.y += v.y;
			vec.z += v.z;
		}

		/// <summary>
		/// �x�N�g�����m�̌��Z�B
		/// </summary>
		/// <param name="v"></param>
		void Subtract(const Vector3& v)
		{
			vec.x -= v.x;
			vec.y -= v.y;
			vec.z -= v.z;
		}

		/// <summary>
		/// �x�N�g�����X�J���[�Ŋg��B
		/// </summary>
		/// <param name="s"></param>
		void Scale(const float s)
		{
			vec.x *= s;
			vec.y *= s;
			vec.z *= s;
		}

		/// <summary>
		/// �x�N�g�����X�J���[�ŏ��Z�B
		/// </summary>
		/// <param name="s"></param>
		void Div(const float s)
		{
			float scale = 1.0f / s;
			Scale(scale);
		}

		/// <summary>
		/// ���K��������B
		/// </summary>
		void Normalize()
		{
			vec = glm::normalize(vec);
		}

		/// <summary>
		/// ���ς��v�Z�B
		/// </summary>
		/// <param name="v"></param>
		/// <returns></returns>
		const float Dot(const Vector3& v) const
		{
			return glm::dot(vec, v.vec);
		}

		/// <summary>
		/// �O�ς��v�Z�B
		/// </summary>
		/// <param name="v"></param>
		void Cross(const Vector3& v)
		{
			vec = glm::cross(vec, v.vec);
		}

		/// <summary>
		/// �O�ς��v�Z�B
		/// </summary>
		/// <param name="v0"></param>
		/// <param name="v1"></param>
		void Cross(const Vector3& v0, const Vector3& v1)
		{
			vec = glm::cross(v0.vec, v1.vec);
		}

		/// <summary>
		/// �x�N�g���̒������擾�B
		/// </summary>
		/// <returns></returns>
		const float Length() const
		{
			return glm::length(vec);
		}

		/// <summary>
		/// �x�N�g���̒�����2����擾�B
		/// </summary>
		/// <returns></returns>
		const float LengthSq() const
		{
			return glm::length2(vec);
		}

		/// <summary>
		/// ������Z�q�B
		/// </summary>
		/// <param name="v"></param>
		/// <returns></returns>
		Vector3& operator=(const Vector3& v)
		{
			vec = v.vec;
			return *this;
		}

		/// <summary>
		/// ���Z������Z�q�B
		/// </summary>
		/// <param name="v"></param>
		/// <returns></returns>
		Vector3& operator+=(const Vector3& v)
		{
			Add(v);
			return *this;
		}

		/// <summary>
		/// ���Z������Z�q�B
		/// </summary>
		/// <param name="v"></param>
		/// <returns></returns>
		Vector3& operator-=(const Vector3& v)
		{
			Subtract(v);
			return *this;
		}

		/// <summary>
		/// ��Z������Z�q�B
		/// </summary>
		/// <param name="s"></param>
		/// <returns></returns>
		Vector3& operator*=(const float s)
		{
			Scale(s);
			return *this;
		}

		/// <summary>
		/// ���Z������Z�q�B
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
	/// �l�����x�N�g���N���X�B
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
		/// �R���X�g���N�^�B
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
		/// �f�X�g���N�^�B
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
		/// �x�N�g�����m�̉��Z�B
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
		/// �x�N�g�����m�̌��Z�B
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
		/// �x�N�g�����X�J���[�Ŋg��B
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
		/// �x�N�g�����X�J���[�ŏ��Z�B
		/// </summary>
		/// <param name="s"></param>
		void Div(const float s)
		{
			float scale = 1.0f / s;
			Scale(scale);
		}

		/// <summary>
		/// ���K��������B
		/// </summary>
		void Normalize()
		{
			vec = glm::normalize(vec);
		}

		/// <summary>
		/// ���ς��v�Z�B
		/// </summary>
		/// <param name="v"></param>
		/// <returns></returns>
		const float Dot(const Vector4& v) const
		{
			return glm::dot(vec, v.vec);
		}


		/// <summary>
		/// �x�N�g���̒������擾�B
		/// </summary>
		/// <returns></returns>
		const float Length() const
		{
			return glm::length(vec);
		}

		/// <summary>
		/// �x�N�g���̒�����2����擾�B
		/// </summary>
		/// <returns></returns>
		const float LengthSq() const
		{
			return glm::length2(vec);
		}

		/// <summary>
		/// ������Z�q�B
		/// </summary>
		/// <param name="v"></param>
		/// <returns></returns>
		Vector4& operator=(const Vector4& v)
		{
			vec = v.vec;
			return *this;
		}

		/// <summary>
		/// ���Z������Z�q�B
		/// </summary>
		/// <param name="v"></param>
		/// <returns></returns>
		Vector4& operator+=(const Vector4& v)
		{
			Add(v);
			return *this;
		}

		/// <summary>
		/// ���Z������Z�q�B
		/// </summary>
		/// <param name="v"></param>
		/// <returns></returns>
		Vector4& operator-=(const Vector4& v)
		{
			Subtract(v);
			return *this;
		}

		/// <summary>
		/// ��Z������Z�q�B
		/// </summary>
		/// <param name="s"></param>
		/// <returns></returns>
		Vector4& operator*=(const float s)
		{
			Scale(s);
			return *this;
		}

		/// <summary>
		/// ���Z������Z�q�B
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
	/// �N�H�[�^�j�I���N���X�B
	/// </summary>
	class Quaternion : public Vector4
	{
	public:
		static const Quaternion Identity;

		/// <summary>
		/// �R���X�g���N�^�B
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
		/// �C�ӂ̎�����̉�]�N�H�[�^�j�I�����쐬�B
		/// </summary>
		/// <param name="axis">��]��</param>
		/// <param name="angle">��]�p�x�B�P�ʃ��W�A��</param>
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
	/// �x�N�g�����m�̉��Z�B
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
	/// �x�N�g�����m�̌��Z�B
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
	/// �x�N�g���ƃX�J���[�̏�Z�B
	/// </summary>
	static Vector3 operator*(const Vector3& v, const float s)
	{
		Vector3 result = v;
		result.Scale(s);
		return result;
	}

	/// <summary>
	/// �x�N�g���ƃX�J���[�̏�Z�B
	/// </summary>
	static Vector3 operator*(const float s, const Vector3& v)
	{
		Vector3 result = v;
		result.Scale(s);
		return result;
	}

	/// <summary>
	/// �x�N�g���ƃX�J���[�̏��Z�B
	/// </summary>
	static Vector3 operator/(const Vector3& v, const float s)
	{
		Vector3 result = v;
		result.Div(s);
		return result;
	}

	/// <summary>
	/// �x�N�g���ƃX�J���[�̏��Z�B
	/// </summary>
	static Vector3 operator/(const float s, const Vector3& v)
	{
		Vector3 result = v;
		result.Div(s);
		return result;
	}
}