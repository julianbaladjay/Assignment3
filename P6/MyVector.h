#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

namespace P6 {
	class MyVector
	{
		public:
			float x, y, z;

			MyVector() : x(0), y(0), z(0) {}
			MyVector(const float _x, const float _y, const float _z) : x(_x), y(_y), z(_z) {}

			explicit operator glm::vec3() const { return glm::vec3(x, y, z); }

			MyVector Add(MyVector b);
			MyVector Subtract(MyVector b);
			MyVector Multiply(MyVector b);
			MyVector Divide(MyVector b);

			float Magnitude() const;
			MyVector Direction() const;
			MyVector ScalarMultiplication(float scalar) const;
			float ScalarProduct(MyVector b) const;
			MyVector VectorProduct(MyVector b) const;

		private:
			glm::vec3 toGLM() const;
			static MyVector fromGLM(const glm::vec3& vec);
	};

	class P6Particle {
	public:
		//mass of particle
		float mass = 0;
		//current position
		MyVector position;
		//current velocity
		MyVector velocity;
		//current acceleration
		MyVector acceleration;

	protected:
		//update position
		void UpdatePosition(float time);
		//update velocity
		void UpdateVelocity(float time);

	public:
		//update particle
		void Update(float time);
	};

}

