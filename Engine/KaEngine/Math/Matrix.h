#pragma once

namespace nsKaEngine {
	/// <summary>
	/// 行列クラス。
	/// </summary>
	class Matrix
	{
	public:
		static const Matrix Identity;
		static const Matrix One;
	public:
		/// <summary>
		/// コンストラクタ。
		/// </summary>
		Matrix()
		{
			mat[0][0] = 1.0f;
			mat[0][1] = 0.0f;
			mat[0][2] = 0.0f;
			mat[0][3] = 0.0f;

			mat[1][0] = 0.0f;
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
		/// デストラクタ。
		/// </summary>
		~Matrix() {}

		union {
			glm::mat4 mat;
			Vector4 v[4];
			float m[4][4];
		};

	public:
		/// <summary>
		/// 平行移動行列を作成。
		/// </summary>
		/// <param name="v0"></param>
		void MakeTranslate(const Vector3& v0)
		{
			mat = glm::translate(mat, v0.vec);
		}

		/// <summary>
		/// カメラ行列を作成。
		/// </summary>
		/// <param name="position">座標</param>
		/// <param name="forward">前方向</param>
		/// <param name="up">上方向</param>
		void MakeLookAt(
			const Vector3& position,
			const Vector3& forward,
			const Vector3& up
		) {
			//mat = glm::lookAt(position.vec, position.vec + forward.vec, up.vec);
			mat = glm::lookAtLH(position.vec, forward.vec, up.vec);
		}

		/// <summary>
		/// 透視変換行列を作成。
		/// </summary>
		/// <param name="fov">視野角</param>
		/// <param name="aspect">アスペクト比</param>
		/// <param name="near">近平面</param>
		/// <param name="far">遠平面</param>
		void MakeProjecionMatrix(
			const float fov,
			const float aspect,
			const float nearV,
			const float farV)
		{
			mat = glm::perspective(glm::radians(fov), aspect, nearV, farV);
		}

		/// <summary>
		/// 平行投影行列を作成。
		/// </summary>
		/// <param name="width"></param>
		/// <param name="height"></param>
		/// <param name="nearV"></param>
		/// <param name="farV"></param>
		void MakeOrthoProjectionMatrix(
			const float width,
			const float height,
			const float nearV,
			const float farV
		) {
			mat = glm::orthoLH_ZO(-width, width, -height, height, nearV, farV);
		}

		/// <summary>
		/// クォータニオンから回転行列を作成。
		/// </summary>
		/// <param name="q"></param>
		void MakeRotationFromQuaternion(const Quaternion& q)
		{
			mat = glm::toMat4(static_cast<glm::quat>(q.vec));
		}

		/// <summary>
		/// 拡大行列を作成。
		/// </summary>
		/// <param name="scale"></param>
		void MakeScaling(const Vector3& scale)
		{
			mat = glm::scale(scale.vec);
		}

		/// <summary>
		/// 逆行列を計算。
		/// </summary>
		/// <param name="mat"></param>
		void Inverse(const Matrix& m)
		{
			mat = glm::inverse(m.mat);
		}

		/// <summary>
		/// 行列同士の乗算。
		/// </summary>
		/// <param name="m0"></param>
		/// <param name="m1"></param>
		void Multiply(const Matrix& m0, const Matrix& m1)
		{
			mat = m0.mat * m1.mat;
		}

		/// <summary>
		/// 代入演算子。
		/// </summary>
		/// <param name="m0"></param>
		/// <returns></returns>
		Matrix& operator=(const Matrix& m0)
		{
			mat = m0.mat;
			return *this;
		}

		/// <summary>
		/// 乗算代入演算子。
		/// </summary>
		/// <param name="m0"></param>
		/// <returns></returns>
		Matrix& operator*=(const Matrix& m0)
		{
			mat *= m0.mat;
			return *this;
		}
	};

	/// <summary>
	/// 行列同士の乗算。
	/// </summary>
	/// <param name="m1"></param>
	/// <param name="m2"></param>
	/// <returns></returns>
	static inline Matrix operator*(const Matrix& m0, const Matrix m1)
	{
		Matrix m;
		m.Multiply(m0, m1);
		return m;
	}
}