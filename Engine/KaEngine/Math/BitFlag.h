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
		/// �R���X�g���N�^�B
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
		/// �f�X�g���N�^�B
		/// </summary>
		~BitFlag() {}

		/// <summary>
		/// �t���O�𗧂Ă�B
		/// </summary>
		/// <param name="flag"></param>
		void SetFlag(const int flag)
		{
			bit |= BIT_FLAG_ARRAY[flag];
		}

		/// <summary>
		/// �t���O��܂�B
		/// </summary>
		/// <param name="flag"></param>
		void FoldFlag(const int flag)
		{
			bit &= ~BIT_FLAG_ARRAY[flag];
		}

		/// <summary>
		/// �t���O�������Ă��邩�ǂ����B
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
		/// �t���O���������Ă��邩���擾�B
		/// </summary>
		/// <returns></returns>
		const int GetFlagNumber() const
		{
			return std::popcount(bit);
		}

		/// <summary>
		/// �t���O���܂Ƃ߂ė��Ă�B
		/// </summary>
		/// <param name="b"></param>
		void SetMaskFlag(const BitFlag& b)
		{
			bit |= b.bit;
		}

		/// <summary>
		/// �t���O���܂Ƃ߂Đ܂�B
		/// </summary>
		/// <param name="b"></param>
		void FoldMaskFlag(const BitFlag& b)
		{
			bit &= ~b.bit;
		}

		/// <summary>
		/// �����̃t���O�̂ǂꂩ�������Ă��邩���擾�B
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
		/// �����̃t���O�̂��ׂĂ������Ă��邩���擾�B
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
		/// ������Z�q�B
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
