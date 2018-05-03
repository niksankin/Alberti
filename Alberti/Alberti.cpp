//#include "includes/Alberti.hpp"
//#include <algorithm>

//namespace Alberti{

//    template<typename U>template<typename T>
//    Alberti<U>::Mode<T>::Mode(unsigned char mode):
//        mode(mode)
//    {
//    }

//    template<typename U>template<typename T>
//    Alberti<U>::Mode<T>::Mode(unsigned char mode, const T& new_additional_key):
//        mode(mode)
//    {
//        if(std::is_same<U,std::string>::value)
//            additional_key = std::transform(new_additional_key.begin(),new_additional_key.end(),new_additional_key.begin(),std::towlower);
//        else
//            additional_key = new_additional_key;
//    }

//    template<typename U>template<typename T>
//    Alberti<U>::Mode<T>::Mode(const Mode<T>& obj){
//        mode = obj.getMode();
//        additional_key = obj.getAdditionalKey();
//    }

//    template<typename U>template<typename T>
//    Alberti<U>::Mode<T>& Alberti<U>::Mode<T>::operator=(const Mode<T>& obj){
//        mode = obj.getMode();
//        additional_key = obj.getAdditionalKey();

//        return *this;
//    }

//    template<typename U>template<typename T>
//    void Alberti<U>::Mode<T>::setMode(unsigned char new_mode, const T& new_additional_key){
//        mode = new_mode;
//        if(std::is_same<U,std::string>::value)
//            additional_key = std::transform(new_additional_key.begin(),new_additional_key.end(),new_additional_key.begin(),std::towlower);
//        else
//            additional_key = new_additional_key;
//    }

//    template<typename U>template<typename T>
//    unsigned char Alberti<U>::Mode<T>::getMode() const{
//        return mode;
//    }

//    template<typename U>template<typename T>
//    T Alberti<U>::Mode<T>::getAdditionalKey() const{
//        return additional_key;
//    }

//    template<typename U>
//    void Alberti<U>::Key::rotate(std::size_t count){
//        std::string rotated(this->c_str(),this->length());

//        for(std::size_t i = 0; i < count; ++i){
//            rotated.insert(rotated.begin(),rotated.back());
//            rotated.pop_back();
//        }

//        this->assign(rotated);
//    }

//    template<typename U>
//    Alberti<U>::Alberti(const std::string& key, const Mode<U>& mode):
//        key(std::transform(key.begin(),key.end(),key.begin(),std::towlower)),
//        mode(mode)
//    {}

//    template<typename U>
//    Alberti<U>::Alberti(const Alberti& obj):
//        key(obj.getKey()),
//        locale(obj.getLocale()),
//        mode(obj.getMode())
//    {}

//    template<typename U>
//    Alberti<U>& Alberti<U>::operator=(const Alberti& obj){
//        key = obj.getKey();
//        locale = obj.getLocale();
//        mode = obj.getMode();

//        return *this;
//    }

//    template<typename U>
//    typename Alberti<U>::Key Alberti<U>::getKey() const{
//        return key;
//    }

//    template<typename U>
//    Alberti<U>::Mode<U> Alberti<U>::getMode() const{
//        return mode;
//    }

//    template<typename U>
//    std::string Alberti<U>::getLocale() const{
//        return locale;
//    }

//    template<typename U>
//    void Alberti<U>::setCondition(const std::string& new_key, const Mode<U>& new_mode){
//        key = Key(std::transform(new_key.begin(),new_key.end(),new_key.begin(),std::towlower));
//        mode = new_mode;
//    }

//    template<typename U>
//    std::string Alberti<U>::encrypt(const std::string& open_text){
//        std::string cipher_text;

//        switch(mode.getMode()){
//        case 1:
//            while(key[0]!=open_text[0])
//                key.rotate(1);
//            break;
//        case 2:
//            while(key[0]!="a")
//                key.rotate(1);
//            break;
//        case 3:
//            while(key[0]!=mode.getAdditionalKey())
//                key.rotate(1);
//            break;
//        };

//        switch(mode.getMode()){
//        case 1:
//        case 2:
//        case 3:
//            for(std::size_t ch = 0; ch < open_text.length(); ++ch){
//                cipher_text.push_back(alphabet[key.find(open_text[ch])]);
//                key.rotate(1);
//            }
//            break;
//        case 4:
//            for(std::size_t ch = 0; ch < open_text.length(); ++ch){
//                if(!(ch % mode.getAdditionalKey())){
//                    key.rotate(std::rand()%key.length());
//                    cipher_text.push_back(std::towupper(key[0]));
//                }
//                cipher_text.push_back(alphabet[key.find(open_text[ch])]);
//            }
//            break;
//        case 5:
//            for(std::size_t ch = 0; ch < open_text.length(); ++ch){
//                while(key[0]!=mode.getAdditionalKey()[ch])
//                      key.rotate(1);
//                cipher_text.push_back(alphabet[key.find(open_text[ch])]);
//                key.rotate(1);
//            }
//            break;
//        }

//        return cipher_text;
//    }

//    template<typename U>
//    std::string Alberti<U>::decrypt(const std::string& open_text){

//    }
//}
