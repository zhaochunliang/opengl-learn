#include "CGlmLearn.h"

#include <iostream>
#include <iomanip>

void CGlmLearn::output_vector(glm::vec4& vector)
{
	cout<<"------------------------------"<<endl;
	for (unsigned int i= 0; i < 4; ++i)
	{
		cout<<vector[i] << "      ";
	}
	cout<<endl;
	cout<<"##############################"<<endl;
}


void  CGlmLearn::output_matrix(glm::mat4& matrix, string matrixname /*=matrix*/)
{
	cout<<"------------"<< matrixname <<"-----------------"<<endl;
	for (unsigned int i= 0; i < matrix.row_size(); ++i)
	{
		for (unsigned int j=0; j < matrix.col_size(); ++j)
		{
			cout<<setw(15)<<setiosflags(ios::fixed)<<setprecision(10)<< matrix[j][i] << "    ";
		}
		cout<<endl;
	}
	cout<<"##############################"<<endl;
}

void CGlmLearn::learn()
{
	cout<<" CGlmLearn::learn() "<<endl;
	{
		/*
		glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
		output_vector(vec);

		glm::mat4 trans;
		output_matrix(trans);

		trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));
		output_matrix(trans);


		vec = trans * vec;
		output_vector(vec);

		std::cout << vec.x << vec.y << vec.z << std::endl;
		*/
	}


	{
		glm::mat4 trans;
		output_matrix(trans);

		trans = glm::rotate(trans, 90.0f, glm::vec3(0.0, 0.0, 1.0));
		output_matrix(trans);

		trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5)); 
		output_matrix(trans);

	}

	{
		glm::mat4 TranslateMat = glm::translate(glm::mat4(1.0), glm::vec3(10.0, 0.0, 0.0)); 

		glm::mat4 ScaleMat = glm::scale(glm::mat4(1.0), glm::vec3(2.0)); 

		glm::mat4 RotateMat = glm::rotate(glm::mat4(1.0), 20.0f, glm::vec3(0.0, 1.0, 0.0));

		//注意：首先执行缩放，接着旋转，最后才是平移。这就是矩阵乘法的工作方式。
		glm::mat4 WorldTransformMat = TranslateMat * RotateMat * ScaleMat;  


		//glm::mat4 MVP        = Projection * View * Model; // Remember, matrix multiplication is the other way around  

		


		// Generates a really hard-to-read matrix, but a normal, standard 4x4 matrix nonetheless  
		glm::mat4 projectionMatrix = glm::perspective(  
			50.0f,         // The horizontal Field of View, in degrees : the amount of "zoom". Think "camera lens". Usually between 90° (extra wide) and 30° (quite zoomed in)  
			4.0f / 3.0f, // Aspect Ratio. Depends on the size of your window. Notice that 4/3 == 800/600 == 1280/960, sounds familiar ?  
			0.1f,        // Near clipping plane. Keep as big as possible, or you'll get precision issues.  
			100.0f       // Far clipping plane. Keep as little as possible.  
			); 

	}
	cout<<"return ..."<<endl;

}