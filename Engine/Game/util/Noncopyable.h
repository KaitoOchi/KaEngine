#pragma once

namespace nsKaEngine {

	/// <summary>
	/// 浅いコピーの禁止。
	/// </summary>
	struct Noncopyable {
		Noncopyable() = default;
		Noncopyable(const Noncopyable&) = delete;
		Noncopyable& operator=(const Noncopyable&) = delete;
	};
}