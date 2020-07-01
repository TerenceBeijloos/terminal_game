#include "Renderer.h"

#include <iostream>

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

void Renderer::set_cursor_position(int x, int y) const
{
    std::cout.flush();
    COORD coord = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(HOUT, coord);
}

void Renderer::cls() const
{
    // Get the Win32 handle representing standard output.
    // This generally only has to be done once, so we make it static.

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    COORD topLeft = { 0, 0 };

    // std::cout uses a buffer to batch writes to the underlying console.
    // We need to flush that to the console because we're circumventing
    // std::cout entirely; after we clear the console, we don't want
    // stale buffered text to randomly be written out.
    std::cout.flush();

    // Figure out the current width and height of the console window
    if (!GetConsoleScreenBufferInfo(HOUT, &csbi)) {
        // TODO: Handle failure!
        abort();
    }
    DWORD length = csbi.dwSize.X * csbi.dwSize.Y;

    DWORD written;

    // Flood-fill the console with spaces to clear it
    FillConsoleOutputCharacter(HOUT, TEXT(' '), length, topLeft, &written);

    // Reset the attributes of every character to the default.
    // This clears all background colour formatting, if any.
    FillConsoleOutputAttribute(HOUT, csbi.wAttributes, length, topLeft, &written);

    // Move the cursor back to the top left for the next sequence of writes
    SetConsoleCursorPosition(HOUT, topLeft);
}

void Renderer::draw_thread()
{
    for (unsigned int x = 0; x < m_field.size(); x++)
    {
        int runStart = -1;
        for (unsigned int y = 0; y < m_field[0].size(); y++) {
            if (m_field[x][y] == m_prev_field[x][y])
            {
                if (runStart != -1) {
                    this->set_cursor_position(runStart, x);
                    std::cout.write(&m_field[x][runStart], (std::streamsize)y - runStart);
                    runStart = -1;
                }
            }
            else if (runStart == -1) {
                runStart = y;
            }
        }
        if (runStart != -1) {
            this->set_cursor_position(runStart, x);
            std::cout.write(&m_field[x][runStart], (std::streamsize)m_field.size() - runStart);
        }
    }

    std::cout.flush();
    m_prev_field = m_field;
}

void Renderer::full_screen()
{
    #pragma comment(lib, "user32")
    ::SendMessage(::GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000);

}

void Renderer::set_field(const Field_type field)
{
    m_field = field;
}

void Renderer::draw(bool big_change)
{
}

Renderer::Renderer(bool set_full_screen)
{
    for (unsigned int i = 0; i < m_field.size(); i++)
    {
        m_field[i].fill(' ');
        m_prev_field[i].fill(' ');
    }

    if (set_full_screen)
    {
        this->full_screen();
    }
    HOUT = GetStdHandle(STD_OUTPUT_HANDLE);

}

Renderer::~Renderer()
{
}
