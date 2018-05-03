#ifndef ALBERTI_HPP
#define ALBERTI_HPP
#include <string>
#include <locale>
#include <algorithm>

namespace Alberti{
    template<class U = std::nullptr_t>
    class Alberti{
    public:
        static std::wstring en_alphabet;
        static std::wstring ru_alphabet;

        class Key: public std::wstring{
        public:
            Key();
            Key(const std::wstring& key);
            Key(const Key& obj);

            Key& operator=(const Key& obj);

            void rotate(std::size_t count);
            void rotate_back(std::size_t count);
        };

        Alberti(const Alberti<U>& obj);

        static Alberti<U> create(const std::wstring& key, const std::string& locale, unsigned char mode);
        static Alberti<U> create(const std::wstring& key, const std::string& locale, unsigned char mode, U additional_key);

        Alberti& operator=(const Alberti<U>& obj);

        std::string getLocale() const;
        std::wstring getAlphabet() const;
        Key getKey() const;
        U getAdditionalKey() const;
        unsigned char getMode() const;

        void setCondition(const std::wstring& key, const std::string& locale, unsigned char mode);
        //void setCondition(const std::wstring& key, const std::wstring& locale, unsigned char mode, U additional_key);

        std::wstring encrypt(const std::wstring& open_text);
        std::wstring decrypt(const std::wstring& open_text);
    private:
        Alberti();
        Alberti(const std::wstring& key, const std::string& locale, unsigned char mode);
        Alberti(const std::wstring& key, const std::string& locale, unsigned char mode, U additional_key);

        static bool checkKeyLocale(const std::wstring& key, const std::string& locale);
        static bool checkTextLocale(const std::wstring& text, const std::string& locale);

        std::wstring alphabet;
        Key key;
        std::string locale;
        unsigned char mode;
        U additional_key;
    };

    template<class U>
    std::wstring Alberti<U>::en_alphabet(L"abcdefghijklmnopqrstuvwxyz");

    template<class U>
    std::wstring Alberti<U>::ru_alphabet(L"абвгдеёжзийклмнопрстуфхцчшщъыьэюя");

    template<class U>
    Alberti<U> Alberti<U>::create(const std::wstring& key, const std::string& locale, unsigned char mode){
        if(std::setlocale(LC_ALL,locale.data())){
            std::wstring low_key = key;
            std::transform(low_key.begin(),low_key.end(),low_key.begin(),std::towlower);

            if((mode == 1 || mode == 2) && checkKeyLocale(low_key, locale))
                return Alberti<U>(low_key, locale, mode);
        }

        return Alberti<U>();
    }

    template<class U>
    Alberti<U> Alberti<U>::create(const std::wstring& key, const std::string& locale, unsigned char mode, U additional_key){
        if(std::setlocale(LC_ALL,locale.data())){
            std::wstring low_key = key;
            std::transform(low_key.begin(),low_key.end(),low_key.begin(),std::towlower);

            if(mode == 4 && checkKeyLocale(low_key, locale) && std::is_integral<U>::value && additional_key > 0)
                return Alberti<U>(low_key, locale, mode, additional_key);
        }

        return Alberti<U>();
    }

    template<>
    Alberti<std::wstring> Alberti<std::wstring>::create(const std::wstring& key, const std::string& locale, unsigned char mode, std::wstring additional_key){
        if(std::setlocale(LC_ALL,locale.data())){
            std::wstring low_key = key;
            std::transform(low_key.begin(),low_key.end(),low_key.begin(),std::towlower);
            std::wstring low_additional_key = additional_key;
            std::transform(low_additional_key.begin(),low_additional_key.end(),low_additional_key.begin(),std::towlower);

            if(mode == 5 && checkKeyLocale(low_key, locale) && checkTextLocale(additional_key, locale)){
                std::wstring buf = low_additional_key;
                std::transform(buf.begin(),buf.end(),buf.begin(),std::towlower);
                return Alberti<std::wstring>(low_key, locale, mode, buf);
            }
        }

        return Alberti<std::wstring>();
    }

    template<>
    Alberti<wchar_t> Alberti<wchar_t>::create(const std::wstring& key, const std::string& locale, unsigned char mode, wchar_t additional_key){
        if(std::setlocale(LC_ALL,locale.data())){
            std::wstring low_key = key;
            std::transform(low_key.begin(),low_key.end(),low_key.begin(),std::towlower);
            wchar_t low_additional_key = towlower(additional_key);

            if(mode == 3 && checkKeyLocale(low_key, locale))
                if((locale == "eng" && en_alphabet.find(low_additional_key) != std::string::npos)  ||
                   (locale == "rus" && ru_alphabet.find(low_additional_key) != std::string::npos))
                    return Alberti<wchar_t>(low_key, locale, mode, low_additional_key);
        }

        return Alberti<wchar_t>();
    }

    template<class U>
    class Alberti<U>::Key Alberti<U>::getKey() const{
        return key;
    }

    template<class U>
    unsigned char Alberti<U>::getMode() const{
        return mode;
    }

    template<class U>
    std::string Alberti<U>::getLocale() const{
        return locale;
    }

    template<class U>
    U Alberti<U>::getAdditionalKey() const{
        return additional_key;
    }

    template<class U>
    std::wstring Alberti<U>::getAlphabet() const{
        return alphabet;
    }

    template<class U>
    Alberti<U>::Alberti():
        key(),
        mode(),
        locale(),
        additional_key(),
        alphabet()
    {}

    template<class U>
    Alberti<U>::Alberti(const std::wstring& key, const std::string& locale, unsigned char mode):
        key(key),
        mode(mode),
        locale(locale),
        additional_key()
    {
        if(locale == "eng")
            alphabet = en_alphabet;
        else if (locale == "rus")
            alphabet = ru_alphabet;
    }

    template<class U>
    Alberti<U>::Alberti(const std::wstring& key, const std::string& locale, unsigned char mode, U additional_key):
        key(key),
        mode(mode),
        locale(locale),
        additional_key(additional_key)
    {
        if(locale == "eng")
            alphabet = en_alphabet;
        else if (locale == "rus")
            alphabet = ru_alphabet;
    }

    template<class U>
    Alberti<U>::Alberti(const Alberti<U>& obj):
        key(obj.getKey()),
        locale(obj.getLocale()),
        mode(obj.getMode()),
        additional_key(obj.getAdditionalKey()),
        alphabet(obj.getAlphabet())
    {}

    template<class U>
    Alberti<U>& Alberti<U>::operator=(const Alberti<U>& obj){
        key = obj.getKey();
        locale = obj.getLocale();
        mode = obj.getMode();
        additional_key = obj.getAdditionalKey();
        alphabet = obj.getAlphabet();

        return *this;
    }

    template<class U>
    bool Alberti<U>::checkKeyLocale(const std::wstring& key, const std::string& locale){
        if(locale == "eng"){
            for(std::size_t i = 0; i < key.length(); ++i)
                if(key.length() != en_alphabet.length() || en_alphabet.find(key[i]) == std::string::npos || std::count(key.begin(),key.end(),key[i]) > 1)
                    return false;
        }
        else if(locale == "rus"){
            for(std::size_t i = 0; i < key.length(); ++i)
                if(key.length() != ru_alphabet.length() || ru_alphabet.find(key[i]) == std::string::npos || std::count(key.begin(),key.end(),key[i]) > 1)
                    return false;
        }
        else
            return false;

        return true;
    }

    template<class U>
    bool Alberti<U>::checkTextLocale(const std::wstring& text, const std::string& locale){
        if(locale == "eng"){
            for(std::size_t i = 0; i < text.length(); ++i)
                if(en_alphabet.find(text[i]) == std::string::npos)
                    return false;
        }
        else if(locale == "rus"){
            for(std::size_t i = 0; i < text.length(); ++i)
                if(ru_alphabet.find(text[i]) == std::string::npos)
                    return false;
        }
        else
            return false;

        return true;
    }

    template<class U>
    void Alberti<U>::setCondition(const std::wstring& new_key, const std::string& new_locale, unsigned char new_mode){
        if(checkKeyLocale(new_key, new_locale)){
            key = new_key;
            locale = new_locale;
            std::transform(key.begin(),key.end(),key.begin(),std::towlower);
            mode = new_mode;
        }
    }

    template<class U>
    Alberti<U>::Key::Key():
        std::wstring()
    {}

    template<class U>
    Alberti<U>::Key::Key(const std::wstring& key):
        std::wstring(key)
    {}

    template<class U>
    Alberti<U>::Key::Key(const Alberti<U>::Key& obj):
        std::wstring(obj.c_str(),obj.length())
    {}

    template<class U>
    typename Alberti<U>::Key& Alberti<U>::Key::operator=(const Alberti<U>::Key& obj){
        this->assign(std::wstring(obj.c_str(),obj.length()));

        return *this;
    }

    template<class U>
    void Alberti<U>::Key::rotate(std::size_t count){
        std::wstring rotated(this->c_str(),this->length());

        for(std::size_t i = 0; i < count; ++i){
            std::rotate(rotated.rbegin(),rotated.rbegin()+1,rotated.rend());
        }

        this->assign(rotated);
    }

    template<class U>
    void Alberti<U>::Key::rotate_back(std::size_t count){
        std::wstring rotated(this->c_str(),this->length());

        for(std::size_t i = 0; i < count; ++i){
            std::rotate(rotated.begin(),rotated.begin()+1,rotated.end());
        }

        this->assign(rotated);
    }

    template<class U>
    std::wstring Alberti<U>::encrypt(const std::wstring& open_text){
        std::wstring cipher_text;

        for(std::size_t ch = 0; ch < open_text.length(); ++ch){
            if(!(ch % additional_key)){
                key.rotate(std::rand()%key.length());
                cipher_text.push_back(std::towupper(key[0]));
            }
            cipher_text.push_back(alphabet[key.find(open_text[ch])]);
        }

        return cipher_text;
    }

    template<>
    std::wstring Alberti<std::nullptr_t>::encrypt(const std::wstring& open_text){
        std::wstring cipher_text;

        switch(mode){
        case 1:
            while(key[0]!=open_text[0])
                key.rotate(1);
            break;
        case 2:
            while(key[0]!=alphabet[0])
                key.rotate(1);
            break;
        };

        for(std::size_t ch = 0; ch < open_text.length(); ++ch){
            cipher_text.push_back(alphabet[key.find(open_text[ch])]);
            key.rotate(1);
        }

        return cipher_text;
    }

    template<>
    std::wstring Alberti<wchar_t>::encrypt(const std::wstring& open_text){
        std::wstring cipher_text;

        while(key[0]!= additional_key)
            key.rotate(1);

        for(std::size_t ch = 0; ch < open_text.length(); ++ch){
            cipher_text.push_back(alphabet[key.find(open_text[ch])]);
            key.rotate(1);
        }

        return cipher_text;
    }

    template<>
    std::wstring Alberti<std::wstring>::encrypt(const std::wstring& open_text){
        std::wstring cipher_text;

        for(std::size_t ch = 0; ch < open_text.length(); ++ch){
            while(key[0]!=additional_key[ch % additional_key.length()])
                  key.rotate(1);
            cipher_text.push_back(alphabet[key.find(open_text[ch])]);
        }

        return cipher_text;
    }

    template<class U>
    std::wstring Alberti<U>::decrypt(const std::wstring& cipher_text){
        std::wstring open_text;

        wchar_t current_key;

        for(std::size_t ch = 0; ch < cipher_text.length(); ++ch){
            if(std::iswupper(cipher_text[ch])){
                current_key = std::towlower(cipher_text[ch]);
                while(key[0]!=current_key)
                    key.rotate(1);
                continue;
            }
            open_text.insert(open_text.begin(),key[alphabet.find(cipher_text[ch])]);
        }

        std::reverse(open_text.begin(),open_text.end());

        return open_text;
    }

    template<>
    std::wstring Alberti<std::nullptr_t>::decrypt(const std::wstring& cipher_text){
        std::wstring open_text;

        switch(mode){
        case 1:
            //нужно будет сохранять сдвинутый ключ
            while(key[0]!=cipher_text[0])
                key.rotate(1);
            break;
        case 2:
            while(key[0]!='a')
                key.rotate(1);
            break;
        };

        for(std::size_t ch = 0; ch < cipher_text.length() - 1; ++ch)
            key.rotate(1);

        for(std::size_t ch = cipher_text.length(); ch-- > 0;){
            open_text.insert(open_text.begin(),key[alphabet.find(cipher_text[ch])]);
            key.rotate_back(1);
        }

        return open_text;
    }

    template<>
    std::wstring Alberti<wchar_t>::decrypt(const std::wstring& cipher_text){
        std::wstring open_text;

        while(key[0]!=additional_key)
            key.rotate(1);

        for(std::size_t ch = 0; ch < cipher_text.length() - 1; ++ch)
            key.rotate(1);

        for(std::size_t ch = cipher_text.length(); ch-- > 0;){
            open_text.insert(open_text.begin(),key[alphabet.find(cipher_text[ch])]);
            key.rotate_back(1);
        }

        return open_text;
    }

    template<>
    std::wstring Alberti<std::wstring>::decrypt(const std::wstring& cipher_text){
        std::wstring open_text;

        for(std::size_t ch = 0; ch < cipher_text.length() - 1; ++ch){
            while(key[0]!=additional_key[ch % additional_key.length()])
                  key.rotate(1);
        }

        for(std::size_t ch = cipher_text.length(); ch-- > 0;){
            while(key[0]!=additional_key[ch % additional_key.length()])
                  key.rotate(1);
            open_text.insert(open_text.begin(),key[alphabet.find(cipher_text[ch])]);
        }

        return open_text;
    }
}

#endif
