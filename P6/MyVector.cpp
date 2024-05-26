#include "MyVector.h"

namespace P6 {

    float MyVector::Magnitude() const {
        return std::sqrt(x * x + y * y + z * z);
    }

    MyVector MyVector::Direction() const {
        float mag = Magnitude();
        return MyVector(x / mag, y / mag, z / mag);
    }

    MyVector MyVector::ScalarMultiplication(float scalar) const {
        return MyVector(x * scalar, y * scalar, z * scalar);
    }

    float MyVector::ScalarProduct(MyVector b) const {
        return (x * b.x + y * b.y + z * b.z);
    }

    MyVector MyVector::VectorProduct(MyVector b) const {
        return MyVector(
            y * b.z - z * b.y,
            z * b.x - x * b.z,
            x * b.y - y * b.x
        );
    }

    void P6::P6Particle::Update(float time) {
		this->UpdatePosition(time);
		this->UpdateVelocity(time);
	}

    void P6::P6Particle::UpdatePosition(float time) {
        //this->position = this->position + (this->velocity * time) + ((1.0f / 2.0f) * (this->acceleration * (time * time)));
    }

    void P6::P6Particle::UpdateVelocity(float time) {
        this->velocity = this->velocity + (this->acceleration * time);
    }

}
