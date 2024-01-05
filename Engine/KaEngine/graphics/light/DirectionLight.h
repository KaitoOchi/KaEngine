#pragma once

namespace nsKaEngine {

	/// <summary>
	/// ディレクションライトの構造体。
	/// </summary>
	struct DirectionLightUB
	{
		Vector3 dirDirection;
		float pad;
		Vector3 dirColor;
		float ambient;
	};
}