// TODO(you): Include header guards
#include <iostream>
#include <vector>
#include <list>
#include <iterator>
#include <assert.h>
#include <cmath>

#include <exception>
#include <memory>
#include <string>
#include <utility>

class EuclideanVectorError : public std::exception {
 public:
  explicit EuclideanVectorError(const std::string& what) : what_(what) {}
  const char* what() const noexcept { return what_.c_str(); }

 private:
  std::string what_;
};

class EuclideanVector {
 public:
  // Constructors
  // 1st constructor
  explicit EuclideanVector(int i);

  // 2nd constructor
  EuclideanVector(int dimensions, double magnitudes);

  // 3rd constructor
  EuclideanVector(std::vector<double>::const_iterator start, std::vector<double>::const_iterator end);

  // 4th constructor: copy constructor
  EuclideanVector(const EuclideanVector& old_ev);

  // 5th constructor: move constructor
  EuclideanVector(EuclideanVector&& old_ev);

  // Destructor
  ~EuclideanVector();

  // Operations
  // Copy Assignment
  EuclideanVector& operator=(const EuclideanVector& other);

  // Move Assignment
  EuclideanVector& operator=(EuclideanVector&& other);

  // Subscript
  // for const objects: can only be used for access
  const double& operator[] (const int index) const;

  // for non-const objects: can only be used for assignment
  double& operator[] (const int index);

  // Addition
  EuclideanVector& operator+=(const EuclideanVector& another_ev);

  // Subtraction
  EuclideanVector& operator-=(const EuclideanVector& another_ev);

  // Multiplication
  EuclideanVector& operator*=(const double scalar);

  // Division
  EuclideanVector& operator/=(const double scalar);

  // Vector Type Conversion
  explicit operator std::vector<double>();

  // List Type Conversion
  explicit operator std::list<double>();

  // Methods
  // Return the value of the magnitude
  double at(int index) const;

  // Return the reference of the magnitude
  double& at(int index);

  // Return the number of dimensions
  int GetNumDimensions() const;

  // Return the Euclidean norm of the vector
  double GetEuclideanNorm();

  // CreateUnitVector
  EuclideanVector CreateUnitVector();

  // Friends
  // Equal
  friend bool operator==(const EuclideanVector& ev1, const EuclideanVector& ev2);

  // Not equal
  friend bool operator!=(const EuclideanVector& ev1, const EuclideanVector& ev2);

  // Addition
  friend EuclideanVector operator+(const EuclideanVector& ev1, const EuclideanVector& ev2);

  // Subtraction
  friend EuclideanVector operator-(const EuclideanVector& ev1, const EuclideanVector& ev2);

  // Multiplication
  friend double operator*(const EuclideanVector& ev1, const EuclideanVector& ev2);

  // Multiply_1
  friend EuclideanVector operator*(const EuclideanVector& ev, double scalar);
  // Multiply_2
  friend EuclideanVector operator*(double scalar, const EuclideanVector& ev);

  // Divide
  friend EuclideanVector operator/(const EuclideanVector& ev, double scalar);

  // Output stream
  friend std::ostream& operator<<(std::ostream& os, const EuclideanVector& v);

 private:
  std::unique_ptr<double[]> magnitudes_;
  int dimensions_;
};
