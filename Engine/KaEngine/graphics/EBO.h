#pragma once

namespace nsKaEngine {

	class EBO
	{
	public:
		// ID reference of Elements Buffer Object
		GLuint ID;

		EBO();
		~EBO();

		// generates a Elements Buffer Object and links it to indices
		void Init(std::vector<GLuint>& indices);

		void Bind();
		void UnBind();
		void Delete();
	};
}