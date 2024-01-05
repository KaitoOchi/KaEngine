#pragma once

namespace nsKaEngine {

	/// <summary>
	/// ポイントライト用の構造体。
	/// </summary>
	struct PointLightUB
	{
		Vector3 ptPosition;
		float pad0;
		Vector3 ptColor;
		float ptRange;
	};
}

