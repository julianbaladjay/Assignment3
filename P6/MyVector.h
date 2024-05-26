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

			MyVector operator+ (const MyVector& v) {
				return MyVector(this->x + v.x, 
								this->y + v.y, 
								this->z + v.z);
			}

			MyVector operator- (const MyVector& v) {
				return MyVector(this->x - v.x,
								this->y - v.y,
								this->z - v.z);
			}

			MyVector operator* (const MyVector& v) {
				return MyVector(this->x * v.x,
								this->y * v.y,
								this->z * v.z);
			}

			MyVector operator*(const float scalar) {
				return MyVector(this->x * scalar, 
								this->y * scalar, 
								this->z * scalar);
			}

			MyVector operator/ (const MyVector& v) {
				return MyVector(this->x / v.x,
								this->y / v.y,
								this->z / v.z);
			}

			MyVector Add(MyVector b) {
				return MyVector(
					this->x + b.x,
					this->y + b.y,
					this->z + b.z
				);
			}
			MyVector Subtract(MyVector b) {
				return MyVector(
					this->x - b.x,
					this->y - b.y,
					this->z - b.z
				);
			}
			MyVector Multiply(MyVector b) {
				return MyVector(
					this->x * b.x,
					this->y * b.y,
					this->z * b.z
				);
			}

			MyVector Divide(MyVector b) {
				return MyVector(
					this->x / b.x,
					this->y / b.y,
					this->z / b.z
				);
			}

			float Magnitude() const;
			MyVector Direction() const;
			MyVector ScalarMultiplication(float scalar) const;
			float ScalarProduct(MyVector b) const;
			MyVector VectorProduct(MyVector b) const;
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

