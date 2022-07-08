#include "Observer.hpp"
#include <iostream>
#include <unistd.h>

class Button
{
public:
    Events<std::function<void()>> clicked;

public:
    void click()
    {
        clicked.Notify();
    }
};

class TextEditor
{
public:
    Events<std::function<void(const std::string& text)>> text_changed;

public:
    void set_text(const std::string& text)
    {
        if (text != m_text)
        {
            m_text = text;
            text_changed.Notify(m_text);
        }
    }

    const std::string& get_text() const
    {
        return m_text;
    }

private:
    std::string m_text;
};

void test_observer()
{
    Button buttonIncrease;
    Button buttonDecrease;
    TextEditor editor;

    int value = 0;
    editor.set_text(std::to_string(value));

    editor.text_changed.Connect([](const std::string& text) {
      std::cout << "editor text_changed: " << text << std::endl;
    });

    editor.text_changed.Connect([](const std::string& text) {
      if (text == "0")
      {
          std::cout << "editor is 0" << std::endl;
      }
    });

    buttonIncrease.clicked.Connect([&] {
      editor.set_text(std::to_string(++value));
    });

    buttonDecrease.clicked.Connect([&] {
      editor.set_text(std::to_string(--value));
    });

    buttonIncrease.click();
    sleep(1);
    buttonIncrease.click();
    sleep(1);
    buttonDecrease.click();
    sleep(1);
    buttonDecrease.click();
}

int main()
{
    test_observer();
    return 0;
}
