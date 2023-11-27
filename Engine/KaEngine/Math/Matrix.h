#pragma once

namespace nsKaEngine {
	/// <summary>
	/// �s��N���X�B
	/// </summary>
	class Matrix
	{
	public:
		static const Matrix Identity;
	public:
		/// <summary>
		/// �R���X�g���N�^�B
		/// </summary>
		Matrix()
		{
			mat[0][0] = 1.0f;
			mat[0][1] = 0.0f;
			mat[0][2] = 0.0f;
			mat[0][3] = 0.0f;

			mat[0][0] = 0.0f;
			mat[1][1] = 1.0f;
			mat[1][2] = 0.0f;
			mat[1][3] = 0.0f;

			mat[2][0] = 0.0f;
			mat[2][1] = 0.0f;
			mat[2][2] = 1.0f;
			mat[2][3] = 0.0f;

			mat[3][0] = 0.0f;
			mat[3][1] = 0.0f;
			mat[3][2] = 0.0f;
			mat[3][3] = 1.0f;
		}
		Matrix(float m00, float m01, float m02, float m03,
			float m10, float m11, float m12, float m13,
			float m20, float m21, float m22, float m23,
			float m30, float m31, float m32, float m33
		) {
			mat = { m00, m01, m02, m03,
				m10, m11, m12, m13,
				m20, m21, m22, m23,
				m30, m31, m32, m33
			};
		}
		Matrix(const glm::mat4& m)
		{
			mat = m;
		}

		/// <summary>
		/// �f�X�g���N�^�B
		/// </summary>
		~Matrix() {}

		union {
			glm::mat4 mat;
			Vector4 v[4];
			float m[4][4];
		};

	public:
		/// <summary>
		/// �J�����s����쐬�B
		/// </summary>
		/// <param name="position">���W</param>
		/// <param name="forward">�O����</param>
		/// <param name="up">�����</param>
		void MakeLookAt(
			const Vector3& position,
			const Vector3& forward,
			const Vector3& up
		) {
			//mat = glm::lookAt(position.vec, position.vec + forward.vec, up.vec);
			mat = glm::lookAtLH(position.vec, forward.vec, up.vec);
		}

		/// <summary>
		/// �����ϊ��s����쐬�B
		/// </summary>
		/// <param name="fov">����p</param>
		/// <param name="aspect">�A�X�y�N�g��</param>
		/// <param name="near">�ߕ���</param>
		/// <param name="far">������</param>
		void MakeProjecionMatrix(
			const float fov,
			const float aspect,
			const float near,
			const float far)
		{
			mat = glm::perspective(glm::radians(fov), aspect, near, far);
		}

		/// <summary>
		/// �t�s����v�Z�B
		/// </summary>
		/// <param name="mat"></param>
		void Inverse(const Matrix& m)
		{
			mat = glm::inverse(m.mat);
		}

		/// <summary>
		/// �s�񓯎m�̏�Z�B
		/// </summary>
		/// <param name="m0"></param>
		/// <param name="m1"></param>
		void Multiply(const Matrix& m0, const Matrix& m1)
		{
			mat = m0.mat * m1.mat;
		}

		/// <summary>
		/// ������Z�q�B
		/// </summary>
		/// <param name="m0"></param>
		/// <returns></returns>
		Matrix& operator=(const Matrix& m0)
		{
			mat = m0.mat;
			return *this;
		}

		/// <summary>
		/// ��Z������Z�q�B
		/// </summary>
		/// <param name="m0"></param>
		/// <returns></returns>
		Matrix& operator*=(const Matrix& m0)
		{
			mat *= m0.mat;
			return *this;
		}
	};
}