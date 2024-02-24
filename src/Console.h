#pragma once

/*
    @brief Sapphire is a C++ library that provides a large set of tools for developers.
    Every Sapphire function is under this namespace.
 */
namespace Sapphire
{

    /*
        @brief A namespace containing functions for console manipulation.
     */
    namespace Console 
    {

        /*
            @brief A namespace containing color definitions for text.
         */
        namespace Colors 
        {

            #ifdef OS_WINDOWS
                /*
                    @brief The color white for console text.
                 */
                static int WHITE = 7;

                /*
                    @brief The color red for console text.
                 */
                static int RED = 12;

                /*
                    @brief The color yellow for console text.
                 */
                static int YELLOW = 6;

                /*
                    @brief The color green for console text.
                 */
                static int GREEN = 10;

                /*
                    @brief The color cyan for console text.
                 */
                static int CYAN = 11;

                /*
                    @brief The color blue for console text.
                 */
                static int BLUE = 3;

                /*
                    @brief The color magenta for console text.
                 */
                static int MAGENTA = 13;
            #else
                /*
                    @brief The color white for console text.
                 */
                static int WHITE = 37;

                /*
                    @brief The color red for console text.
                 */
                static int RED = 31;

                /*
                    @brief The color yellow for console text.
                 */
                static int YELLOW = 33;

                /*
                    @brief The color green for console text.
                 */
                static int GREEN = 32;

                /*
                    @brief The color cyan for console text.
                 */
                static int CYAN = 36;

                /*
                    @brief The color blue for console text.
                 */
                static int BLUE = 34;

                /*
                    @brief The color magenta for console text.
                 */
                static int MAGENTA = 35;
            #endif

            static int NO_COLOR = -1;
        }

        /*
            @brief Clears the console.
         */
        void Clear();

        /*
            @brief Sets the color of console text.
            @param color The color to set it to. Use definitions in Console::Colors.
         */
        void SetTextColor(int color);

        /*
            @brief Gets the color of console text.
            @return The color of console text.
         */
        int GetTextColor();

        /*
            @brief Makes the text italic.
         */
        void SetItalic();

        /*
            @brief Makes the text underlined.
         */
        void SetUnderline();

        /*
            @brief Resets the style of the console, including color, italics, and underline.
         */
        void ResetStyle();
    }
}