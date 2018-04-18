#ifndef ALBERTI_HPP
#define ALBERTI_HPP
#include <string>
#include <locale>

namespace Alberti{
    template<typename U>
    class Alberti{
    public:
        template<typename T>
        class Mode{
            unsigned char mode;
            T additional_key;
        public:
            Mode() = delete;
            Mode(unsigned char mode, const T& additional_key);

            Mode& operator=(const Mode& obj);

            void setMode(unsigned char new_mode, const T& new_additional_key);

            unsigned char getMode() const;
            T getAdditionalKey() const;
        };

        Alberti() = delete;

        //less lazy way to implement mode passing
        Alberti(const std::string& key, const Mode<U>& mode);
        Alberti(const Alberti& obj);

        Alberti& operator=(const Alberti& obj);

        std::string getKey() const;
        Mode<U> getMode() const;
        std::string getLocale() const;

        void setKey(const std::string& key);
        void setMode(const Mode<U>& mode);

        std::string encrypt(const std::string& open_text);
        std::string decrypt(const std::string& open_text);
    private:
        std::string key;
        std::locale locale;
        Mode<U> mode;
    };
}

#endif
