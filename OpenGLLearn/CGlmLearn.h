#ifndef OPENGL_LEARN_GLM_H
#define OPENGL_LEARN_GLM_H

#include "Glm/glm.hpp"
#include "Glm/ext.hpp"
#include <string>
using namespace std;

class  CGlmLearn
{
public:
	void learn();

public:
	static void output_vector(glm::vec4& vector);
	static void output_matrix(glm::mat4& matrix, string matrixname = "matrix");
};
#endif // OPENGL_LEARN_GLM_H