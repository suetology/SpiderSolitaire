#pragma once

class VertexArray
{
public:
	VertexArray();
	~VertexArray();

	void Bind() const;
	void Unbind() const;

private:
	unsigned int m_Id;
};

