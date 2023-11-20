#pragma once

namespace nsKaEngine {

	/// <summary>
	/// �󂢃R�s�[�̋֎~�B
	/// </summary>
	struct Noncopyable {
		Noncopyable() = default;
		Noncopyable(const Noncopyable&) = delete;
		Noncopyable& operator=(const Noncopyable&) = delete;
	};
}