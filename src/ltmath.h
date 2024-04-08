namespace LTMath
{
  /*
   * Wraps value between min and max
   *
   * @param value The value to wrap
   * @param min The minimum value
   * @param max The maximum value
   *
   * @returns The wrapped value
   */
  int wrap(int value, int min, int max);
  /*
   * Wraps value between min and max except for floats
   *
   * @param value The value to wrap
   * @param min The minimum value
   * @param max The maximum value
   *
   * @returns The wrapped value
   */
  float wrapf(float value, float min, float max);

  /*
   * Clamps the value between min and max
   *
   * @param value The value to clamp
   * @param min The minimum value
   * @param max The maximum value
   *
   * @returns The clamped value
   */
  int clamp(int value, int min, int max);
  /*
   * Clamps the value between min and max except for floats
   *
   * @param value The value to clamp
   * @param min The minimum value
   * @param max The maximum value
   *
   * @returns The clamped value
   */
  float clampf(float value, float min, float max);
}
