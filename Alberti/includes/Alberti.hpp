#ifndef ALBERTI_HPP
#define ALBERTI_HPP
#include <string>
#include <cstddef>

namespace Alberti{
    class Alberti{
        std::string key;
        std::locale locale;
        std::byte mode;
        std::string pass_phrase;
        std::size_t block_size;
        wchar_t chosen_letter;

        Alberti() = delete;

        //lazy way to implement mode passing
        Alberti(const std::string& key, std::byte mode);
        Alberti(const std::string& key, std::byte mode, wchar_t letter);
        Alberti(const std::string& key, std::byte mode, const std::string& pass_phrase);
        Alberti(const std::string& key, std::byte mode, std::size_t block_size);

        Alberti(const Alberti& obj);
        Alberti& operator=(const Alberti& obj);

        void setKey(const std::string& key);
        void setMode(std::byte mode, wchar_t letter);
        void setMode(std::byte mode, const std::string& pass_phrase);
        void setMode(std::byte mode, std::size_t block_size);

        std::string& encrypt(const std::string& open_text);
        std::string& decrypt(const std::string& open_text);
    };
}

#endif
