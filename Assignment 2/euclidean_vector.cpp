//#include "assignments/ev/euclidean_vector.h"
#include "euclidean_vector.h"

#include <algorithm>  // Look at these - they are helpful https://en.cppreference.com/w/cpp/algorithm

std::unique_ptr<double[]> myVector(int n) {
    return std::make_unique<double[]>(n);
}

// 1st constructor
EuclideanVector::EuclideanVector(int i = 1): EuclideanVector(i, 0.0) {}

// 2nd constructor
EuclideanVector::EuclideanVector(int dimensions, double magnitudes) {
  dimensions_ = dimensions;
  magnitudes_ = myVector(dimensions_);
  for (int i = 0; i != dimensions_; ++i) {
    magnitudes_[i] = magnitudes;
  }
}

// 3rd constructor
EuclideanVector::EuclideanVector(std::vector<double>::const_iterator start, std::vector<double>::const_iterator end) {
  dimensions_ = std::distance(start, end);
  magnitudes_ = myVector(dimensions_);
  int i = 0;
  for (std::vector<double>::const_iterator myIter = start; myIter != end; ++myIter, ++i) {
    magnitudes_[i] = *myIter;
  }
}

// 4th constructor: copy constructor
EuclideanVector::EuclideanVector(const EuclideanVector& old_ev) {
  dimensions_ = old_ev.dimensions_;
  magnitudes_ = myVector(dimensions_);
  for (int i = 0; i != dimensions_; ++i) {
    magnitudes_[i] = old_ev.magnitudes_[i];
  }
}

// 5th constructor: move constructor
EuclideanVector::EuclideanVector(EuclideanVector&& old_ev) {
  dimensions_ = std::move(old_ev.dimensions_);
  magnitudes_ = myVector(dimensions_);
  magnitudes_ = std::move(old_ev.magnitudes_);
  old_ev.dimensions_ = 0;
  old_ev.magnitudes_ = nullptr;
}

// Destructor
EuclideanVector::~EuclideanVector() {
  magnitudes_.reset();
}

// Copy Assignment
EuclideanVector& EuclideanVector::operator=(const EuclideanVector& other) {
  if (this != &other) {
    dimensions_ = other.dimensions_;
    magnitudes_ = myVector(dimensions_);
    for (int i = 0; i != dimensions_; ++i) {
      magnitudes_[i] = other.magnitudes_[i];
    }
  }
  return *this;
}

// Move Assignment
EuclideanVector& EuclideanVector::operator=(EuclideanVector&& other) {
  if (this != &other) {
    magnitudes_.reset();  // delete original data
    dimensions_ = std::move(other.dimensions_);  // copy the data
    magnitudes_ = myVector(dimensions_);
    magnitudes_ = std::move(other.magnitudes_);
    other.dimensions_ = 0;  // reset the other's data
    other.magnitudes_ = nullptr;
  }
  return *this;
}

// Subscript for const objects: can only be used for access
const double& EuclideanVector::operator[] (const int index) const {
  assert(index >= 0);  // assert for valid index passed
  assert(index < dimensions_);
  return magnitudes_[index];
}

// Subscript for non-const objects: can only be used for assignment
double& EuclideanVector::operator[] (const int index) {
  assert(index >= 0);  // assert for valid index passed
  assert(index < dimensions_);
  return magnitudes_[index];
}

// Addition
EuclideanVector& EuclideanVector::operator+=(const EuclideanVector& another_ev) {
  if (dimensions_ != another_ev.dimensions_) {
    int X = dimensions_;
    int Y = another_ev.dimensions_;
    // throw std::invalid_argument("Dimensions of LHS(X) and RHS(Y) do not match");
    throw std::invalid_argument("Dimensions of LHS(" + std::to_string(X) +") and RHS(" + std::to_string(Y) + ") do not match");
  }

  for (int i = 0; i != dimensions_; ++i) {
    magnitudes_[i] += another_ev[i];
  }
  return *this;
}

// Subtraction
EuclideanVector& EuclideanVector::operator-=(const EuclideanVector& another_ev) {
  if (dimensions_ != another_ev.dimensions_) {
    // throw std::invalid_argument("Dimensions of LHS(X) and RHS(Y) do not match");
    int X = dimensions_;
    int Y = another_ev.dimensions_;
    throw std::invalid_argument("Dimensions of LHS(" + std::to_string(X) +") and RHS(" + std::to_string(Y) + ") do not match");
  }

  for (int i = 0; i != dimensions_; ++i) {
    magnitudes_[i] -= another_ev[i];
  }
  return *this;
}

// Multiplication
EuclideanVector& EuclideanVector::operator*=(const double scalar) {
  for (int i = 0; i != dimensions_; ++i) {
    magnitudes_[i] *= scalar;
  }
  return *this;
}

// Division
EuclideanVector& EuclideanVector::operator/=(const double scalar) {
  if (scalar == 0.0) {
    throw std::invalid_argument("Invalid vector division by 0");
  }

  for (int i = 0; i != dimensions_; ++i) {
    magnitudes_[i] /= scalar;
  }
  return *this;
}

// Vector Type Conversion
EuclideanVector::operator std::vector<double>() {
  std::vector<double> converted_vector;
  for (int i = 0; i != dimensions_; ++i) {
    converted_vector.push_back(magnitudes_[i]);
  }
  return converted_vector;
}

// List Type Conversion
EuclideanVector::operator std::list<double>() {
  std::list<double> converted_list;
  for (int i = 0; i != dimensions_; ++i) {
    converted_list.push_back(magnitudes_[i]);
  }
  return converted_list;
}

// Return the value of the magnitude
double EuclideanVector::at(int index) const {
  if (index < 0 || index >= dimensions_) {
    // throw std::invalid_argument("Index X is not valid for this EuclideanVector object");
    throw std::invalid_argument("Index " + std::to_string(index) + " is not valid for this EuclideanVector object");
  } 

  return magnitudes_[index];
}

// Return the reference of the magnitude
double& EuclideanVector::at(int index) {
  if (index < 0 || index >= dimensions_) {
    // throw std::invalid_argument("Index X is not valid for this EuclideanVector object");
    throw std::invalid_argument("Index " + std::to_string(index) + " is not valid for this EuclideanVector object");
  }

  return magnitudes_[index];
}

// Return the number of dimensions
int EuclideanVector::GetNumDimensions() const {
  return this->dimensions_;
}

// Return the Euclidean norm of the vector
double EuclideanVector::GetEuclideanNorm() {
  if (this->GetNumDimensions() == 0) {
    throw std::invalid_argument("EuclideanVector with no dimensions does not have a norm");
  }

  double sum = 0.0;
  for (int i = 0; i != dimensions_; ++i) {
    sum += magnitudes_[i] * magnitudes_[i];
  }
  return std::sqrt(sum);
}

// CreateUnitVector
EuclideanVector EuclideanVector::CreateUnitVector() {
  if (this->GetNumDimensions() == 0) {
    throw std::invalid_argument("EuclideanVector with no dimensions does not have a unit vector");
  }
  if (this->GetEuclideanNorm() == 0) {
    throw std::invalid_argument("EuclideanVector with euclidean normal of 0 does not have a unit vector");
  }

  double norm = GetEuclideanNorm();
  EuclideanVector unitVector(dimensions_);
  for (int i = 0; i < dimensions_; ++i) {
    unitVector.magnitudes_[i] = magnitudes_[i] / norm;
  }
  return unitVector;
}

// Equal
bool operator==(const EuclideanVector& ev1, const EuclideanVector& ev2) {
  if (ev1.dimensions_ != ev2.dimensions_) {
    return false;
  }
  for (int i = 0; i != ev1.dimensions_; ++i) {
    if (ev1.magnitudes_[i] != ev2.magnitudes_[i]) {
      return false;
    }
  }
  return true;
}

// Not equal
bool operator!=(const EuclideanVector& ev1, const EuclideanVector& ev2) {
  if (ev1 == ev2) {
    return false;
  } else {
    return true;
  }
}

// Addition
EuclideanVector operator+(const EuclideanVector& ev1, const EuclideanVector& ev2) {
  if (ev1.dimensions_ != ev2.dimensions_) {
    // throw std::invalid_argument("Dimensions of LHS(X) and RHS(Y) do not match");
    int X = ev1.dimensions_;
    int Y = ev2.dimensions_;
    throw std::invalid_argument("Dimensions of LHS(" + std::to_string(X) +") and RHS(" + std::to_string(Y) + ") do not match");
  }

  EuclideanVector myEV = ev1;
  myEV += ev2;
  return myEV;
}

// Subtraction
EuclideanVector operator-(const EuclideanVector& ev1, const EuclideanVector& ev2) {
  if (ev1.dimensions_ != ev2.dimensions_) {
    // throw std::invalid_argument("Dimensions of LHS(X) and RHS(Y) do not match");
    int X = ev1.dimensions_;
    int Y = ev2.dimensions_;
    throw std::invalid_argument("Dimensions of LHS(" + std::to_string(X) +") and RHS(" + std::to_string(Y) + ") do not match");
  }

  EuclideanVector myEV = ev1;
  myEV -= ev2;
  return myEV;
}

// Multiplication
double operator*(const EuclideanVector& ev1, const EuclideanVector& ev2) {
  if (ev1.dimensions_ != ev2.dimensions_) {
    // throw std::invalid_argument("Dimensions of LHS(X) and RHS(Y) do not match");
    int X = ev1.dimensions_;
    int Y = ev2.dimensions_;
    throw std::invalid_argument("Dimensions of LHS(" + std::to_string(X) +") and RHS(" + std::to_string(Y) + ") do not match");
  }

  double result = 0.0;
  for (int i = 0; i != ev1.dimensions_; ++i) {
    result += ev1.magnitudes_[i] * ev2.magnitudes_[i];
  }
  return result;
}

// Multiply_1
EuclideanVector operator*(const EuclideanVector& ev, double scalar) {
  EuclideanVector myEV = ev;
  for (int i = 0; i != myEV.dimensions_; ++i) {
    myEV.magnitudes_[i] *= scalar;
  }
  return myEV;
}

// Multiply_2
EuclideanVector operator*(double scalar, const EuclideanVector& ev) {
  EuclideanVector myEV = ev;
  for (int i = 0; i != myEV.dimensions_; ++i) {
    myEV.magnitudes_[i] *= scalar;
  }
  return myEV;
}

// Divide
EuclideanVector operator/(const EuclideanVector& ev, double scalar) {
  if (scalar == 0.0) {
    throw std::invalid_argument("Invalid vector division by 0");
  }

  EuclideanVector myEV = ev;
  for (int i = 0; i != myEV.dimensions_; ++i) {
    myEV.magnitudes_[i] /= scalar;
  }
  return myEV;
}

// Output stream
std::ostream& operator<<(std::ostream& os, const EuclideanVector& v) {
  os << "[";
  for (int i = 0; i < v.dimensions_; ++i) {
    os << v.magnitudes_[i];
    if (i < v.dimensions_ - 1) {
      os << " ";
    }
  }
  os << "]";
  return os;
}
