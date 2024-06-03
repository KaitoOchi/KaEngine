#pragma once

namespace nsKaEngine {

	/// <summary>
	/// �񎟌��x�N�g���N���X�B
	/// </summary>
	template<typename T>
	class Vector2Common
	{
	public:
		/// <summary>
		/// �R���X�g���N�^�B
		/// </summary>
		explicit Vector2Common()
		{
			x = T{};
			y = T{};
		}
		Vector2Common(const T x, const T y)
		{
			this->x = x;
			this->y = y;
		}

		/// <summary>
		/// �f�X�g���N�^�B
		/// </summary>
		~Vector2Common() {}

		union {
			glm::vec<2, T, glm::defaultp> vec;
			struct { T x, y; };
			T v[2];
		};

	public:
		/// <summary>
		/// �x�N�g����ݒ�B
		/// </summary>
		/// <param name="x"></param>
		/// <param name="y"></param>
		void Set(const T x, const T y)
		{
			vec.x = x;
			vec.y = y;
		}

		/// <summary>
		/// �x�N�g�����m�̉��Z�B
		/// </summary>
		/// <param name="v"></param>
		void Add(const Vector2Common& v)
		{
			vec.x += v.x;
			vec.y += v.y;
		}

		/// <summary>
		/// �x�N�g�����m�̌��Z�B
		/// </summary>
		/// <param name="v"></param>
		void Subtract(const Vector2Common& v)
		{
			vec.x += v.x;
			vec.y += v.y;
		}

		/// <summary>
		/// �x�N�g�����X�J���[�Ŋg��B
		/// </summary>
		/// <param name="s"></param>
		void Scale(const float s)
		{
			vec.x *= static_cast<T>(s);
			vec.y *= static_cast<T>(s);
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
			glm::vec2 v;
			v = glm::normalize(vec);
			if (!isnan(v.x)) {
				vec = v;
			}
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
		/// ���`��ԁB
		/// </summary>
		/// <param name="v0">�⊮�J�n�̃x�N�g��</param>
		/// <param name="v1">�⊮�I���̃x�N�g��</param>
		/// <param name="t">�⊮��</param>
		/// <returns></returns>
		void Lerp(const Vector2Common& v0, const Vector2Common& v1, const float t)
		{
			vec = glm::mix(v0.vec, v1.vec, t);
		}

		/// <summary>
		/// �ŏ�����ő�̊ԂŒl�����߂�B
		/// </summary>
		/// <param name="v0"></param>
		/// <param name="v1"></param>
		void Clamp(const float min, const float max)
		{
			vec =  glm::clamp(vec, min, max);
		}
	};

	/// <summary>
	/// �e���v���[�g�̕������ꉻ���g����Vector2���`�B
	/// </summary>
	/// <typeparam name="T"></typeparam>
	template<typename T>
	class Vector2Tmp : public Vector2Common<T> {
	public:
		/// <summary>
		/// �R���X�g���N�^�̌p��
		/// </summary>
		using Vector2Common<T>::Vector2Common;

		/// <summary>
		/// ������Z�q�B
		/// </summary>
		/// <typeparam name="U"></typeparam>
		/// <param name="other"></param>
		/// <returns></returns>
		template<typename U>
		Vector2Tmp<T>& operator=(const Vector2Tmp<U>& other)
		{
			this->x = static_cast<T>(other.x);
			this->y = static_cast<T>(other.y);
			return *this;
		}

		/// <summary>
		/// ���Z������Z�q�B
		/// </summary>
		/// <param name="v"></param>
		/// <returns></returns>
		template<typename U>
		Vector2Tmp<T>& operator+=(const Vector2Tmp<U>& v)
		{
			this->x += static_cast<T>(v.x);
			this->y += static_cast<T>(v.y);
			return *this;
		}

		/// <summary>
		/// ���Z������Z�q�B
		/// </summary>
		/// <param name="v"></param>
		/// <returns></returns>
		template<typename U>
		Vector2Tmp<T>& operator-=(const Vector2Tmp<U>& v)
		{
			this->x -= static_cast<T>(v.x);
			this->y -= static_cast<T>(v.y);
			return *this;
		}

		/// <summary>
		/// ��Z������Z�q�B
		/// </summary>
		/// <param name="v"></param>
		/// <returns></returns>
		Vector2Tmp<T>& operator*=(const T s)
		{
			this->x *= static_cast<T>(s);
			this->y *= static_cast<T>(s);
			return *this;
		}

		/// <summary>
		/// ���Z������Z�q�B
		/// </summary>
		/// <param name="v"></param>
		/// <returns></returns>
		Vector2Tmp<T>& operator/=(const T d)
		{
			this->x /= static_cast<T>(d);
			this->y /= static_cast<T>(d);
			return *this;
		}

		static const Vector2Tmp<T> Zero;
		static const Vector2Tmp<T> One;
	};

	using Vector2 = Vector2Tmp<float>;
	using Vector2Int = Vector2Tmp<int>;
	using Vector2Double = Vector2Tmp<double>;

	/// <summary>
	/// �O�����x�N�g���N���X�B
	/// </summary>
	template<typename T>
	class Vector3Common
	{
	public:
		/// <summary>
		/// �R���X�g���N�^�B
		/// </summary>	
		explicit Vector3Common()
		{
			x = T{};
			y = T{};
			z = T{};
		}
		Vector3Common(const T x, const T y, const T z)
		{
			this->x = x;
			this->y = y;
			this->z = z;
		}

		/// <summary>
		/// �f�X�g���N�^�B
		/// </summary>
		~Vector3Common() {}

		union {
			glm::vec<3, T, glm::defaultp> vec;
			struct { T x, y, z; };
			T v[3];
		};

	public:
		/// <summary>
		/// �x�N�g����ݒ�B
		/// </summary>
		/// <param name="x"></param>
		/// <param name="y"></param>
		/// <param name="z"></param>
		void Set(const T x, const T y, const T z)
		{
			vec.x = x;
			vec.y = y;
			vec.z = z;
		}

		/// <summary>
		/// �x�N�g�����m�̉��Z�B
		/// </summary>
		/// <param name="v"></param>
		void Add(const Vector3Common& v)
		{
			vec.x += v.x;
			vec.y += v.y;
			vec.z += v.z;
		}

		/// <summary>
		/// �x�N�g�����m�̌��Z�B
		/// </summary>
		/// <param name="v"></param>
		void Subtract(const Vector3Common& v)
		{
			vec.x -= v.x;
			vec.y -= v.y;
			vec.z -= v.z;
		}

		/// <summary>
		/// �x�N�g�����X�J���[�Ŋg��B
		/// </summary>
		/// <param name="s"></param>
		void Scale(const T s)
		{
			vec.x *= static_cast<T>(s);
			vec.y *= static_cast<T>(s);
			vec.z *= static_cast<T>(s);
		}

		/// <summary>
		/// �x�N�g�����X�J���[�ŏ��Z�B
		/// </summary>
		/// <param name="s"></param>
		void Div(const T s)
		{
			T scale = 1.0f / s;
			Scale(scale);
		}

		/// <summary>
		/// ���K��������B
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
		/// ���ς��v�Z�B
		/// </summary>
		/// <param name="v"></param>
		/// <returns></returns>
		const float Dot(const Vector3Common& v) const
		{
			return glm::dot(vec, v.vec);
		}

		/// <summary>
		/// �O�ς��v�Z�B
		/// </summary>
		/// <param name="v"></param>
		void Cross(const Vector3Common& v)
		{
			vec = glm::cross(vec, v.vec);
		}

		/// <summary>
		/// �O�ς��v�Z�B
		/// </summary>
		/// <param name="v0"></param>
		/// <param name="v1"></param>
		void Cross(const Vector3Common& v0, const Vector3Common& v1)
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
		/// ���`��ԁB
		/// </summary>
		/// <param name="v0">�⊮�J�n�̃x�N�g��</param>
		/// <param name="v1">�⊮�I���̃x�N�g��</param>
		/// <param name="t">�⊮��</param>
		/// <returns></returns>
		void Lerp(const Vector3Common& v0, const Vector3Common& v1, const float t)
		{
			vec = glm::mix(v0.vec, v1.vec, t);
		}
	};

	/// <summary>
	/// �e���v���[�g�̕������ꉻ���g����Vector3���`�B
	/// </summary>
	/// <typeparam name="T"></typeparam>
	template<typename T>
	class Vector3Tmp : public Vector3Common<T> {
	public:
		/// <summary>
		/// �R���X�g���N�^�̌p��
		/// </summary>
		using Vector3Common<T>::Vector3Common;

		/// <summary>
		/// ������Z�q�B
		/// </summary>
		/// <typeparam name="U"></typeparam>
		/// <param name="other"></param>
		/// <returns></returns>
		template<typename U>
		Vector3Tmp<T>& operator=(const Vector3Tmp<U>& other)
		{
			this->x = static_cast<T>(other.x);
			this->y = static_cast<T>(other.y);
			this->z = static_cast<T>(other.z);
			return *this;
		}

		/// <summary>
		/// ���Z������Z�q�B
		/// </summary>
		/// <param name="v"></param>
		/// <returns></returns>
		template<typename U>
		Vector3Tmp<T>& operator+=(const Vector3Tmp<U>& v)
		{
			this->x += static_cast<T>(v.x);
			this->y += static_cast<T>(v.y);
			this->z += static_cast<T>(v.z);
			return *this;
		}

		/// <summary>
		/// ���Z������Z�q�B
		/// </summary>
		/// <param name="v"></param>
		/// <returns></returns>
		template<typename U>
		Vector3Tmp<T>& operator-=(const Vector3Tmp<U>& v)
		{
			this->x -= static_cast<T>(v.x);
			this->y -= static_cast<T>(v.y);
			this->z -= static_cast<T>(v.z);
			return *this;
		}

		/// <summary>
		/// ��Z������Z�q�B
		/// </summary>
		/// <param name="v"></param>
		/// <returns></returns>
		Vector3Tmp<T>& operator*=(const T s)
		{
			this->x *= static_cast<T>(s);
			this->y *= static_cast<T>(s);
			this->z *= static_cast<T>(s);
			return *this;
		}

		/// <summary>
		/// ���Z������Z�q�B
		/// </summary>
		/// <param name="v"></param>
		/// <returns></returns>
		Vector3Tmp<T>& operator/=(const T d)
		{
			this->x /= static_cast<T>(d);
			this->y /= static_cast<T>(d);
			this->z /= static_cast<T>(d);
			return *this;
		}

		static const Vector3Tmp<T> Zero;
		static const Vector3Tmp<T> One;
		static const Vector3Tmp<T> Up;
		static const Vector3Tmp<T> Forward;
		static const Vector3Tmp<T> Backward;
		static const Vector3Tmp<T> AxisX;
		static const Vector3Tmp<T> AxisY;
		static const Vector3Tmp<T> AxisZ;
	};

	using Vector3 = Vector3Tmp<float>;
	using Vector3Int = Vector3Tmp<int>;
	using Vector3Double = Vector3Tmp<double>;


	/// <summary>
	/// �l�����x�N�g���N���X�B
	/// </summary>
	template<typename T>
	class Vector4Common
	{
	public:
		/// <summary>
		/// �R���X�g���N�^�B
		/// </summary>	
		explicit Vector4Common()
		{
			x = T{};
			y = T{};
			z = T{};
			w = T{};
		}
		Vector4Common(const T x, const T y, const T z, const T w)
		{
			this->x = x;
			this->y = y;
			this->z = z;
			this->w = w;
		}

		/// <summary>
		/// �f�X�g���N�^�B
		/// </summary>
		~Vector4Common() {}

		union {
			glm::vec<4, T, glm::defaultp> vec;
			struct { T x, y, z, w; };
			struct { T r, g, b, a; };
			T v[4];
		};

	public:
		/// <summary>
		/// �x�N�g����ݒ�B
		/// </summary>
		/// <param name="x"></param>
		/// <param name="y"></param>
		/// <param name="z"></param>
		/// <param name="w"></param>
		void Set(const T x, const T y, const T z, const T w)
		{
			vec.x = x;
			vec.y = y;
			vec.z = z;
			vec.w = w;
		}


		/// <summary>
		/// �x�N�g�����m�̉��Z�B
		/// </summary>
		/// <param name="v"></param>
		void Add(const Vector4Common& v)
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
		void Subtract(const Vector4Common& v)
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
		void Scale(const T s)
		{
			vec.x *= static_cast<T>(s);
			vec.y *= static_cast<T>(s);
			vec.z *= static_cast<T>(s);
			vec.w *= static_cast<T>(s);
		}

		/// <summary>
		/// �x�N�g�����X�J���[�ŏ��Z�B
		/// </summary>
		/// <param name="s"></param>
		void Div(const T s)
		{
			T scale = 1.0f / s;
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
		const float Dot(const Vector4Common& v) const
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
		/// ���`��ԁB
		/// </summary>
		/// <param name="v0">�⊮�J�n�̃x�N�g��</param>
		/// <param name="v1">�⊮�I���̃x�N�g��</param>
		/// <param name="t">�⊮��</param>
		/// <returns></returns>
		void Lerp(const Vector4Common& v0, const Vector4Common& v1, const float t)
		{
			vec = glm::mix(v0.vec, v1.vec, t);
		}
	};

	/// <summary>
	/// �e���v���[�g�̕������ꉻ���g����Vector4���`�B
	/// </summary>
	/// <typeparam name="T"></typeparam>
	template<typename T>
	class Vector4Tmp : public Vector4Common<T> {
	public:
		/// <summary>
		/// �R���X�g���N�^�̌p��
		/// </summary>
		using Vector4Common<T>::Vector4Common;

		/// <summary>
		/// ������Z�q�B
		/// </summary>
		/// <typeparam name="U"></typeparam>
		/// <param name="other"></param>
		/// <returns></returns>
		template<typename U>
		Vector4Tmp<T>& operator=(const Vector4Tmp<U>& other)
		{
			this->x = static_cast<T>(other.x);
			this->y = static_cast<T>(other.y);
			this->z = static_cast<T>(other.z);
			this->w = static_cast<T>(other.w);
			return *this;
		}

		/// <summary>
		/// ���Z������Z�q�B
		/// </summary>
		/// <param name="v"></param>
		/// <returns></returns>
		template<typename U>
		Vector4Tmp<T>& operator+=(const Vector4Tmp<U>& v)
		{
			this->x += static_cast<T>(v.x);
			this->y += static_cast<T>(v.y);
			this->z += static_cast<T>(v.z);
			this->w += static_cast<T>(v.w);
			return *this;
		}

		/// <summary>
		/// ���Z������Z�q�B
		/// </summary>
		/// <param name="v"></param>
		/// <returns></returns>
		template<typename U>
		Vector4Tmp<T>& operator-=(const Vector4Tmp<U>& v)
		{
			this->x -= static_cast<T>(v.x);
			this->y -= static_cast<T>(v.y);
			this->z -= static_cast<T>(v.z);
			this->w -= static_cast<T>(v.w);
			return *this;
		}

		/// <summary>
		/// ��Z������Z�q�B
		/// </summary>
		/// <param name="v"></param>
		/// <returns></returns>
		Vector4Tmp<T>& operator*=(const T s)
		{
			this->x *= static_cast<T>(s);
			this->y *= static_cast<T>(s);
			this->z *= static_cast<T>(s);
			this->w *= static_cast<T>(s);
			return *this;
		}

		/// <summary>
		/// ���Z������Z�q�B
		/// </summary>
		/// <param name="v"></param>
		/// <returns></returns>
		Vector4Tmp<T>& operator/=(const T d)
		{
			this->x /= static_cast<T>(d);
			this->y /= static_cast<T>(d);
			this->z /= static_cast<T>(d);
			this->w /= static_cast<T>(d);
			return *this;
		}

		static const Vector4Tmp<T> Zero;
		static const Vector4Tmp<T> White;
		static const Vector4Tmp<T> Black;
		static const Vector4Tmp<T> Red;
		static const Vector4Tmp<T> Green;
		static const Vector4Tmp<T> Blue;
		static const Vector4Tmp<T> Gray;
	};

	using Vector4 = Vector4Tmp<float>;
	using Vector4Int = Vector4Tmp<int>;
	using Vector4Double = Vector4Tmp<double>;

	/// <summary>
	/// �N�H�[�^�j�I���N���X�B
	/// </summary>
	class Quaternion : public Vector4Common<float>
	{
	public:
		static const Quaternion Identity;

		/// <summary>
		/// �R���X�g���N�^�B
		/// </summary>
		explicit Quaternion()
		{
			x = y = z = 0.0f;
			w = 1.0f;
		}
		Quaternion(const float x, const float y, const float z, const float w)
		{
			this->x = x;
			this->y = y;
			this->z = z;
			this->w = w;
		}

	public:
		/// <summary>
		/// �N�H�[�^�j�I�����m�̏�Z�B
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
		/// X������̉�]�N�H�[�^�j�I�����쐬(�P��Radian)�B
		/// </summary>
		/// <param name="angle"></param>
		void SetRotationX(const float angle)
		{
			SetRotation(Vector3::AxisX, angle);
		}

		/// <summary>
		/// X������̉�]�N�H�[�^�j�I�����쐬(�P��Degree)�B
		/// </summary>
		/// <param name="angle"></param>
		void SetRotationDegX(const float angle)
		{
			SetRotation(Vector3::AxisX, Mathf::DegToRad(angle));
		}

		/// <summary>
		/// Y������̉�]�N�H�[�^�j�I�����쐬(�P��Radian)�B
		/// </summary>
		/// <param name="angle"></param>
		void SetRotationY(const float angle)
		{
			SetRotation(Vector3::AxisY, angle);
		}

		/// <summary>
		/// Y������̉�]�N�H�[�^�j�I�����쐬(�P��Degree)�B
		/// </summary>
		/// <param name="angle"></param>
		void SetRotationDegY(const float angle)
		{
			SetRotation(Vector3::AxisY, Mathf::DegToRad(angle));
		}

		/// <summary>
		/// Z������̉�]�N�H�[�^�j�I�����쐬(�P��Radian)�B
		/// </summary>
		/// <param name="angle"></param>
		void SetRotationZ(const float angle)
		{
			SetRotation(Vector3::AxisZ, angle);
		}

		/// <summary>
		/// Z������̉�]�N�H�[�^�j�I�����쐬(�P��Degree)�B
		/// </summary>
		/// <param name="angle"></param>
		void SetRotationDegZ(const float angle)
		{
			SetRotation(Vector3::AxisZ, Mathf::DegToRad(angle));
		}

		/// <summary>
		/// X������̉�]�N�H�[�^�j�I�������Z(�P��Radian)�B
		/// </summary>
		/// <param name="angle"></param>
		void AddRotationX(float angle)
		{
			Quaternion addRot;
			addRot.SetRotation(Vector3::AxisX, angle);
			*this *= addRot;
		}

		/// <summary>
		/// X������̉�]�N�H�[�^�j�I�������Z(�P��Degree)�B
		/// </summary>
		/// <param name="angle"></param>
		void AddRotationDegX(float angle)
		{
			Quaternion addRot;
			addRot.SetRotation(Vector3::AxisX, Mathf::DegToRad(angle));
			*this *= addRot;
		}

		/// <summary>
		/// Y������̉�]�N�H�[�^�j�I�������Z(�P��Radian)�B
		/// </summary>
		/// <param name="angle"></param>
		void AddRotationY(float angle)
		{
			Quaternion addRot;
			addRot.SetRotation(Vector3::AxisY, angle);
			*this *= addRot;
		}

		/// <summary>
		/// Y������̉�]�N�H�[�^�j�I�������Z(�P��Degree)�B
		/// </summary>
		/// <param name="angle"></param>
		void AddRotationDegY(float angle)
		{
			Quaternion addRot;
			addRot.SetRotation(Vector3::AxisY, Mathf::DegToRad(angle));
			*this *= addRot;
		}

		/// <summary>
		/// Z������̉�]�N�H�[�^�j�I�������Z(�P��Radian)�B
		/// </summary>
		/// <param name="angle"></param>
		void AddRotationZ(float angle)
		{
			Quaternion addRot;
			addRot.SetRotation(Vector3::AxisZ, angle);
			*this *= addRot;
		}

		/// <summary>
		/// Z������̉�]�N�H�[�^�j�I�������Z(�P��Degree)�B
		/// </summary>
		/// <param name="angle"></param>
		void AddRotationDegZ(float angle)
		{
			Quaternion addRot;
			addRot.SetRotation(Vector3::AxisZ, Mathf::DegToRad(angle));
			*this *= addRot;
		}

		/// <summary>
		/// �C�ӂ̎�����̉�]�N�H�[�^�j�I�����쐬�B
		/// </summary>
		/// <param name="axis">��]��</param>
		/// <param name="angle">��]�p�x�B�P�ʃ��W�A��</param>
		void SetRotation(const Vector3Common<float>& axis, float angle)
		{
			float halfAngle = angle * 0.5f;
			float s = sinf(halfAngle);
			w = cosf(halfAngle);
			x = axis.x * s;
			y = axis.y * s;
			z = axis.z * s;
		}

		/// <summary>
		/// from�x�N�g������to�x�N�g���ɉ�]������N�H�[�^�j�I�����쐬�B
		/// </summary>
		/// <param name="from"></param>
		/// <param name="to"></param>
		void SetRotationFromVector(const Vector3Common<float>& from, const Vector3Common<float>& to)
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
		/// �x�N�g���ɃN�H�[�^�j�I����K�p�B
		/// </summary>
		/// <param name="v"></param>
		void Apply(Vector3Common<float>& v)
		{
			glm::quat quat;
			quat.x = vec.x;
			quat.y = vec.y;
			quat.z = vec.z;
			quat.w = vec.w;
			v.vec = glm::rotate(quat, v.vec);
		}

		/// <summary>
		/// ��Z������Z�q�B
		/// </summary>
		const Quaternion& operator*=(const Quaternion& rot)
		{
			Multiply(rot, *this);
			return *this;
		}
	};

	/// <summary>
	/// �x�N�g�����m�̉��Z�B
	/// </summary>
	static Vector3 operator+(const Vector3& v0, const Vector3& v1)
	{
		Vector3 result = v0;
		result.Add(v1);
		return result;
	}

	/// <summary>
	/// �x�N�g�����m�̌��Z�B
	/// </summary>
	static Vector3 operator-(const Vector3& v0, const Vector3& v1)
	{
		Vector3 result = v1;
		result.Subtract(v1);
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
}
