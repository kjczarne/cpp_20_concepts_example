#include <string>
#include <iostream>
#include <sstream>
#include <concepts>


template <typename T>
concept Person = requires (T person) {
    { person.get_name() } -> std::same_as<std::string>;
};

template <typename T>
requires Person<T>
auto get_person_name(T person) {
    return person.get_name();
}


class Mom {
    private:
        std::string _name;
    public:
        Mom(std::string name) {
            _name = name;
        }
        std::string get_name() {
            return _name;
        }
};


template <Person T>
class NameGetter {
    public:
        std::string get_name(T person) {
            return person.get_name();
        }
};


template <typename T>
concept WithStreamOperator = requires (T instance, std::string str) {
    instance << str;
};

void my_print(WithStreamOperator auto& stream, std::string contents) {
    stream << contents;
}


int main() {
    auto name_getter = NameGetter<Mom>();
    auto mom = Mom("Mamechka");
    auto moms_name = get_person_name(mom);
    auto moms_name2 = name_getter.get_name(mom);
    std::cout << moms_name << std::endl;
    std::cout << moms_name2 << std::endl;
    std::stringbuf sb;
    std::ostream stream (&sb);

    my_print(stream, "wow");
    std::cout << sb.str();
    return 0;
}
