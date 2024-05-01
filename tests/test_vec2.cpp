#include <cmath>
#include <iostream>

#include <framework/math.h>

const auto test_vec2 = Vec2{2.6f, -1.2f};

class test_failed : public std::runtime_error {
public:
  using std::runtime_error::runtime_error;
  test_failed(const test_failed &) = default;
  test_failed(test_failed &&) = default;
  test_failed &operator=(const test_failed &) = default;
  test_failed &operator=(test_failed &&) = default;;
};

void test_vec2_addition() {
  const float epsilon = 0.15f;
  Vec2 sum{0.0f, 0.0f};

  // Test the vec2 + vec2 version
  sum = vec2_add(test_vec2, Vec2{1.0f, 2.0f});

  if (std::fabs(sum.x - 3.6f) > epsilon || std::fabs(sum.y - 0.8f) > epsilon) {
    throw test_failed("Vec2 addition failed (Vec2 + Vec2)");
  }

  // Test the vec2 + float version
  sum = vec2_add(test_vec2, 1.0f);

  if (std::fabs(sum.x - 3.6f) > epsilon || std::fabs(sum.y - -0.2f) > epsilon) {
    throw test_failed("Vec2 addition failed (Vec2 + float)");
  }
}

void test_vec2_subtraction() {
  Vec2 difference;
  const float epsilon = 0.15f;

  // Test the vec2 - vec2 version
  difference = vec2_sub(test_vec2, Vec2{1.0f, 2.0f});

  if (std::fabs(difference.x - 1.6f) > epsilon || std::fabs(difference.y - -3.2f) > epsilon) {
    throw test_failed("Vec2 subtraction failed (Vec2 - Vec2)");
  }

  // Test the vec2 - float version
  difference = vec2_sub(test_vec2, 1.0f);

  if (std::fabs(difference.x - 1.6f) > epsilon || std::fabs(difference.y - -2.2f) > epsilon) {
    throw test_failed("Vec2 subtraction failed (Vec2 - float)");
  }
}

void test_vec2_division() {
  Vec2 divided;
  const float epsilon = 0.15f;

  // Test the vec2 / vec2 version
  divided = vec2_div(test_vec2, Vec2{1.0f, 2.0f});

  if (std::fabs(divided.x - 2.6f) > epsilon || std::fabs(divided.y - -0.6f) > epsilon) {
    throw test_failed("Vec2 division failed (Vec2 / Vec2)");
  }

  // Test the vec2 / float version
  divided = vec2_div(test_vec2, 2.0f);

  if (std::fabs(divided.x - 1.3f) > epsilon || std::fabs(divided.y - -0.6f) > epsilon) {
    throw test_failed("Vec2 division failed (Vec2 / float)");
  }
}

void test_vec2_multiplication() {
  Vec2 multiplied;
  const float epsilon = 0.15f;

  // Test the vec2 * vec2 version
  multiplied = vec2_mul(test_vec2, Vec2{2.0f, 3.0f});

  if (std::fabs(multiplied.x - 5.2f) > epsilon || std::fabs(multiplied.y - -3.6f) > epsilon) {
    throw test_failed("Vec2 multiplication failed (Vec2 * Vec2)");
  }

  // Test the vec2 * float version
  multiplied = vec2_mul(test_vec2, 2.0f);

  if (std::fabs(multiplied.x - 5.2f) > epsilon || std::fabs(multiplied.y - -2.4f) > epsilon) {
    throw test_failed("Vec2 multiplication failed (Vec2 * float)");
  }
}

void test_vec2_normalize() {
  Vec2 normalized;
  const float epsilon = 0.15f;

  normalized = vec2_normalize(test_vec2);

  if (std::fabs(normalized.x - 0.907f) > epsilon || std::fabs(normalized.y - -0.419f) > epsilon) {
    throw test_failed("Vec2 normalization failed");
  }
}

int main(int argc, char** argv) { 
  std::cout << "Testing vector addition.." << std::endl;
  test_vec2_addition();

  std::cout << "Testing vector subtraction.." << std::endl;
  test_vec2_subtraction();

  std::cout << "Testing vector division.." << std::endl;
  test_vec2_division();

  std::cout << "Testing vector multiplication.." << std::endl;
  test_vec2_multiplication();

  std::cout << "Testing vector normalization.." << std::endl;
  test_vec2_normalize();
  return 0;
}
