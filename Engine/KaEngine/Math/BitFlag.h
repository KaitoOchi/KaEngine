#pragma once
#include <bitset>
#include <bit>

namespace nsKaEngine {

	namespace
	{
		const unsigned char BIT_FLAG_ARRAY[8] = { 
			(1 << 0),
			(1 << 1),
			(1 << 2),
			(1 << 3),
			(1 << 4),
			(1 << 5),
			(1 << 6),
			(1 << 7)
		};
	}

	class BitFlag
	{
	public:
		static const BitFlag All;

	public:
		/// <summary>
		/// コンストラクタ。
		/// </summary>
		explicit BitFlag()
		{
			bit = 0;
		}
		BitFlag(const unsigned char b)
		{
			bit = b;
		}

		/// <summary>
		/// デストラクタ。
		/// </summary>
		~BitFlag() {}

		/// <summary>
		/// フラグを立てる。
		/// </summary>
		/// <param name="flag"></param>
		void SetFlag(const int flag)
		{
			bit |= BIT_FLAG_ARRAY[flag];
		}

		/// <summary>
		/// フラグを折る。
		/// </summary>
		/// <param name="flag"></param>
		void FoldFlag(const int flag)
		{
			bit &= ~BIT_FLAG_ARRAY[flag];
		}

		/// <summary>
		/// フラグが立っているかどうか。
		/// </summary>
		/// <param name="flag"></param>
		/// <returns></returns>
		const bool IsSetFlag(const int flag) const
		{
			if (bit & BIT_FLAG_ARRAY[flag]) {
				return true;
			}
			return false;
		}

		/// <summary>
		/// フラグが何個立っているかを取得。
		/// </summary>
		/// <returns></returns>
		const int GetFlagNumber() const
		{
			return std::popcount(bit);
		}

		/// <summary>
		/// フラグをまとめて立てる。
		/// </summary>
		/// <param name="b"></param>
		void SetMaskFlag(const BitFlag& b)
		{
			bit |= b.bit;
		}

		/// <summary>
		/// フラグをまとめて折る。
		/// </summary>
		/// <param name="b"></param>
		void FoldMaskFlag(const BitFlag& b)
		{
			bit &= ~b.bit;
		}

		/// <summary>
		/// 複数のフラグのどれかが立っているかを取得。
		/// </summary>
		/// <param name="b"></param>
		/// <returns></returns>
		const bool IsSetMaskFlagOR(const BitFlag& b) const
		{
			if (bit & b.bit) {
				return true;
			}
			return false;
		}

		/// <summary>
		/// 複数のフラグのすべてが立っているかを取得。
		/// </summary>
		/// <param name="b"></param>
		/// <returns></returns>
		const bool IsSetMaskFlagAND(const BitFlag& b) const
		{
			if ((bit & b.bit) == b.bit) {
				return true;
			}
			return false;
		}

		/// <summary>
		/// 代入演算子。
		/// </summary>
		/// <param name="b"></param>
		/// <returns></returns>
		BitFlag& operator=(const BitFlag& b)
		{
			bit = b.bit;
			return *this;
		}

		void Log()
		{
			std::cout << std::bitset<8>(bit) << '\n';
		}

	private:
		unsigned char bit;
	};
}
