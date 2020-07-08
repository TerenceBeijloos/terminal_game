#include "Renderer.h"

#include <iostream>

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

void Renderer::set_cursor_position(int x, int y) const
{
    std::cout.flush();
    COORD coord = { (SHORT)x, (SHORT)(y - FIELD_HEIGHT) };
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

void Renderer::draw_thread(const Field& field)
{
    for (unsigned int x = 0; x < field.size(); x++)
    {
        int runStart = -1;
        for (unsigned int y = 0; y < field[0].size(); y++) {
            if (field[x][y] == m_prev_field[x][y])
            {
                if (runStart != -1) {
                    this->set_cursor_position(runStart, x);
                    std::cout.write(&field[x][runStart], (std::streamsize)y - runStart);
                    runStart = -1;
                }
            }
            else if (runStart == -1) {
                runStart = y;
            }
        }
        if (runStart != -1) {
            this->set_cursor_position(runStart, x);
            std::cout.write(&field[x][runStart], (std::streamsize)field.size() - runStart);
        }
    }

    std::cout.flush();
    m_prev_field = field;
}

void Renderer::full_screen()
{
    #pragma comment(lib, "user32")
    ::SendMessage(::GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000);

}

void Renderer::join()
{
    if (m_Draw_thd.joinable())
    {
        m_Draw_thd.join();
    }
}

void Renderer::draw(const Field& field, bool big_change)
{
    m_Draw_thd = std::thread(&Renderer::draw_thread, this, field);
}

Renderer::Renderer(bool set_full_screen)
{
    m_prev_field.fill(' ');

    if (set_full_screen)
    {
        this->full_screen();
    }
    HOUT = GetStdHandle(STD_OUTPUT_HANDLE);

}

Renderer::~Renderer()
{
}
