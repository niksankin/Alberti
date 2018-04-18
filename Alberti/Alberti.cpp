#include "includes/Alberti.hpp"

namespace Alberti{

    template<typename U>template<typename T>
    Alberti<U>::Mode<T>::Mode(unsigned char mode, const T& additional_key):
        mode(mode),
        additional_key(additional_key)
    {}

    template<typename U>template<typename T>
    Alberti<U>::Mode<T>& Alberti<U>::Mode<T>::operator=(const Mode<T>& obj)
    {
        mode = obj.getMode();
        additional_key = obj.getAdditionalKey();

        return *this;
    }

    template<typename U>template<typename T>
    void Alberti<U>::Mode<T>::setMode(unsigned char new_mode, const T& new_additional_key){
        mode = new_mode;
        additional_key = new_additional_key;
    }

    template<typename U>template<typename T>
    unsigned char Alberti<U>::Mode<T>::getMode() const{
        return mode;
    }

    template<typename U>template<typename T>
    T Alberti<U>::Mode<T>::getAdditionalKey() const{
        return additional_key;
    }

    template<typename U>
    Alberti<U>::Alberti(const std::string& key, const Mode<U>& mode):
        key(key),
        mode(mode)
    {}

    template<typename U>
    Alberti<U>::Alberti(const Alberti& obj):
        key(obj.getKey()),
        locale(obj.getLocale()),
        mode(obj.getMode())
    {}

    template<typename U>
    Alberti<U>& Alberti<U>::operator=(const Alberti& obj){
        key = obj.getKey();
        locale = obj.getLocale();
        mode = obj.getMode();

        return *this;
    }

    template<typename U>
    std::string Alberti<U>::getKey() const{
        return key;
    }

    template<typename U>
    Alberti<U>::Mode<U> Alberti<U>::getMode() const{
        return mode;
    }

    template<typename U>
    std::string Alberti<U>::getLocale() const{
        return locale;
    }

    template<typename U>
    void Alberti<U>::setKey(const std::string& new_key){
        key = new_key;
    }

    template<typename U>
    void Alberti<U>::setMode(const Mode<U>& new_mode){
        mode = new_mode;
    }

    template<typename U>
    std::string Alberti<U>::encrypt(const std::string& open_text){}

    template<typename U>
    std::string Alberti<U>::decrypt(const std::string& open_text){}
}
