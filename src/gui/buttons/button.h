#include <raylib.h>

#include <gui/ui_element.h>

#pragma once

class Button : public UIElement
{
public:
  Button() = default;
  ~Button() override = default;

  /*
   * The background color of the button.
   */
  Color background_color = { 40, 40, 40, 255 };

  /*
   * The text color of the button.
   */
  Color text_color = WHITE;
  /*
   * The text font of the button.
   */
  Font text_font = GetFontDefault();

  /*
   * The font size of the text.
   */
  int text_font_size = 16;
  /*
   * The spacing between the characters
   */
  int text_font_spacing = 2;

  /*
   * The text of the button
   */
  char *text_content = (char*)"Label";
  
  /*
   * If the button is hovered
   *
   * @return A boolean value indicating if the button is hovered
   */
  bool is_pressed() const;
  /*
   * If the button is pressed
   *
   * @return A boolean value indicating if the button is pressed
   */
  bool is_hovered() const;


  void on_render() override;
};
