#pragma once
#include <memory>

namespace nsKaEngine {

	/// <summary>
	/// データを保存するためのクラステンプレート。
	/// </summary>
	/// <typeparam name="TResource"></typeparam>
	template<class TResource>
	class TResourceBank : Noncopyable
	{
	public:
		/// <summary>
		/// バンクに登録されているか。
		/// </summary>
		/// <param name="filePath"></param>
		/// <returns></returns>
		TResource* Get(const char* filePath)
		{
			auto it = m_resourceMap.find(filePath);
			if (it != m_resourceMap.end()) {
				return it->second.get();
			}
			return nullptr;
		}

		/// <summary>
		/// バンクに登録する。
		/// </summary>
		/// <param name="filePath"></param>
		/// <param name="resource"></param>
		void Regist(const char* filePath, TResource* resource)
		{
			auto it = m_resourceMap.find(filePath);
			if (it == m_resourceMap.end()) {
				//未登録。
				m_resourceMap.insert(
					std::pair<std::string, TResourcePtr>(filePath, resource)
				);
			}
		}

	private:
		using TResourcePtr = std::unique_ptr<TResource>;
		std::map<std::string, TResourcePtr> m_resourceMap;
	};
}