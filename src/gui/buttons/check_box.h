#include <raylib.h>

#include <gui/ui_element.h>

#pragma once

class CheckBox : public UIElement
{
public:
  CheckBox() = default;
  ~CheckBox() = default;

  /*
   * If the checkbox is checked
   *
   * @returns A boolean value representing if the checkbox is checked
   */
  inline bool get_checked() { return this->checked; };
  /*
   * Sets the checkbox as checked or not
   *
   * @param checked A boolean value representing the state to set the checkbox
   */
  inline void set_checked(bool checked) { this->checked = checked; };

  void on_update(float delta) override;
  void on_render() override;

private:
  bool checked = false;
};
