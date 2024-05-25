/*#include "MyVector.h"

namespace P6 {

    // Addition
    MyVector MyVector::Add(MyVector b) {
        glm::vec3 a_vec = static_cast<glm::vec3>(*this);
        glm::vec3 b_vec = static_cast<glm::vec3>(b);
        glm::vec3 result = a_vec + b_vec;
        return MyVector(result.x, result.y, result.z);
    }

    // Subtraction
    MyVector MyVector::Subtract(MyVector b) {
        glm::vec3 a_vec = static_cast<glm::vec3>(*this);
        glm::vec3 b_vec = static_cast<glm::vec3>(b);
        glm::vec3 result = a_vec - b_vec;
        return MyVector(result.x, result.y, result.z);
    }

    // Component-wise Multiplication
    MyVector MyVector::Multiply(MyVector b) {
        glm::vec3 a_vec = static_cast<glm::vec3>(*this);
        glm::vec3 b_vec = static_cast<glm::vec3>(b);
        glm::vec3 result = a_vec * b_vec;
        return MyVector(result.x, result.y, result.z);
    }

    // Component-wise Division
    MyVector MyVector::Divide(MyVector b) {
        glm::vec3 a_vec = static_cast<glm::vec3>(*this);
        glm::vec3 b_vec = static_cast<glm::vec3>(b);
        glm::vec3 result = a_vec / b_vec;
        return MyVector(result.x, result.y, result.z);
    }

    // Magnitude
    float MyVector::Magnitude() const {
        glm::vec3 vec = static_cast<glm::vec3>(*this);
        return glm::length(vec);
    }

    // Direction (Normalization)
    MyVector MyVector::Direction() const {
        glm::vec3 vec = static_cast<glm::vec3>(*this);
        glm::vec3 result = glm::normalize(vec);
        return MyVector(result.x, result.y, result.z);
    }

    // Scalar Multiplication
    MyVector MyVector::ScalarMultiplication(float scalar) const {
        glm::vec3 vec = static_cast<glm::vec3>(*this);
        glm::vec3 result = vec * scalar;
        return MyVector(result.x, result.y, result.z);
    }

    // Scalar (Dot) Product
    float MyVector::ScalarProduct(MyVector b) const {
        glm::vec3 a_vec = static_cast<glm::vec3>(*this);
        glm::vec3 b_vec = static_cast<glm::vec3>(b);
        return glm::dot(a_vec, b_vec);
    }

    // Vector (Cross) Product
    MyVector MyVector::VectorProduct(MyVector b) const {
        glm::vec3 a_vec = static_cast<glm::vec3>(*this);
        glm::vec3 b_vec = static_cast<glm::vec3>(b);
        glm::vec3 result = glm::cross(a_vec, b_vec);
        return MyVector(result.x, result.y, result.z);
    }

}*/

#include "MyVector.h"

namespace P6 {

    glm::vec3 MyVector::toGLM() const {
        return glm::vec3(x, y, z);
    }

    MyVector MyVector::fromGLM(const glm::vec3& vec) {
        return MyVector(vec.x, vec.y, vec.z);
    }

    // Addition
    MyVector MyVector::Add(MyVector b) {
        glm::vec3 result = toGLM() + b.toGLM();
        return fromGLM(result);
    }

    // Subtraction
    MyVector MyVector::Subtract(MyVector b) {
        glm::vec3 result = toGLM() - b.toGLM();
        return fromGLM(result);
    }

    // Component-wise Multiplication
    MyVector MyVector::Multiply(MyVector b) {
        glm::vec3 result = toGLM() * b.toGLM();
        return fromGLM(result);
    }

    // Component-wise Division
    MyVector MyVector::Divide(MyVector b) {
        glm::vec3 result = toGLM() / b.toGLM();
        return fromGLM(result);
    }

    // Magnitude
    float MyVector::Magnitude() const {
        return glm::length(toGLM());
    }

    // Direction (Normalization)
    MyVector MyVector::Direction() const {
        glm::vec3 result = glm::normalize(toGLM());
        return fromGLM(result);
    }

    // Scalar Multiplication
    MyVector MyVector::ScalarMultiplication(float scalar) const {
        glm::vec3 result = toGLM() * scalar;
        return fromGLM(result);
    }

    // Scalar (Dot) Product
    float MyVector::ScalarProduct(MyVector b) const {
        return glm::dot(toGLM(), b.toGLM());
    }

    // Vector (Cross) Product
    MyVector MyVector::VectorProduct(MyVector b) const {
        glm::vec3 result = glm::cross(toGLM(), b.toGLM());
        return fromGLM(result);
    }

    void P6::P6Particle::UpdatePosition(float time) {
        //position = position + (velocity * time);
    }

}
