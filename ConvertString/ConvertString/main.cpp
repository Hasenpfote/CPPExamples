// https://social.msdn.microsoft.com/Forums/en-US/8f40dcd8-c67f-4eba-9134-a19b9178e481/vs-2015-rc-linker-stdcodecvt-error?forum=vcgeneral

#include <locale>
#include <codecvt>
#include <iostream>
#include <assert.h>
#include <vector>

static constexpr std::codecvt_mode mode = std::codecvt_mode::little_endian;
//static constexpr std::codecvt_mode mode = (std::codecvt_mode)0;

// utf8 to utf16
// gcc7.0.0 ... ---
// gcc6.1.0 ... ---
// gcc5.3.0 ... ---
// gcc5.2.0 ... need endianness.
// gcc5.1.0 ... ---
// clang4.0.0 . ---
static std::u16string utf8_to_utf16(const std::string& s)
{
#if defined(_MSC_VER) && (_MSC_VER <= 1900)
    //  Workaround for missing char16_t/char32_t instantiations in MSVC2015.
    std::wstring_convert<std::codecvt_utf8_utf16<std::uint16_t, 0x10ffff, mode>, std::uint16_t> conv;
    auto temp = conv.from_bytes(s);
    return std::u16string(temp.cbegin(), temp.cend());
#else
    std::wstring_convert<std::codecvt_utf8_utf16<char16_t, 0x10ffff, mode>, char16_t> conv;
    return conv.from_bytes(s);
#endif
}

// utf16 to utf8
// gcc7.0.0 ... ---
// gcc6.1.0 ... ---
// gcc5.3.0 ... ---
// gcc5.2.0 ... ---
// gcc5.1.0 ... ---
// clang4.0.0 . ---
static std::string utf16_to_utf8(const std::u16string& s)
{
#if defined(_MSC_VER) && (_MSC_VER <= 1900)
    //  Workaround for missing char16_t/char32_t instantiations in MSVC2015.
    std::wstring_convert<std::codecvt_utf8_utf16<std::uint16_t, 0x10ffff, mode>, std::uint16_t> conv;
    auto p = reinterpret_cast<const std::uint16_t*>(s.c_str());
    return conv.to_bytes(p, p + s.length());
#else
    std::wstring_convert<std::codecvt_utf8_utf16<char16_t, 0x10ffff, mode>, char16_t> conv;
    return conv.to_bytes(s);
#endif
}

// utf8 to utf32
// gcc7.0.0 ... ---
// gcc6.1.0 ... ---
// gcc5.3.0 ... ---
// gcc5.2.0 ... ---
// gcc5.1.0 ... ---
// clang4.0.0 . ---
static std::u32string utf8_to_utf32(const std::string& s)
{
#if defined(_MSC_VER) && (_MSC_VER <= 1900)
    //  Workaround for missing char16_t/char32_t instantiations in MSVC2015.
    std::wstring_convert<std::codecvt_utf8<std::uint32_t, 0x10ffff, mode>, std::uint32_t> conv;
    auto temp = conv.from_bytes(s);
    return std::u32string(temp.cbegin(), temp.cend());
#else
    std::wstring_convert<std::codecvt_utf8<char32_t, 0x10ffff, mode>, char32_t> conv;
    return conv.from_bytes(s);
#endif
}

// utf32 to utf8
// gcc7.0.0 ... ---
// gcc6.1.0 ... ---
// gcc5.3.0 ... ---
// gcc5.2.0 ... ---
// gcc5.1.0 ... ---
// clang4.0.0 . ---
static std::string utf32_to_utf8(const std::u32string& s)
{
#if defined(_MSC_VER) && (_MSC_VER <= 1900)
    //  Workaround for missing char16_t/char32_t instantiations in MSVC2015.
    std::wstring_convert<std::codecvt_utf8<std::uint32_t, 0x10ffff, mode>, std::uint32_t> conv;
    auto p = reinterpret_cast<const std::uint32_t*>(s.c_str());
    return conv.to_bytes(p, p + s.length());
#else
    std::wstring_convert<std::codecvt_utf8<char32_t, 0x10ffff, mode>, char32_t> conv;
    return conv.to_bytes(s);
#endif
}

// utf16 to utf32
// gcc7.0.0 ... need endianness.
// gcc6.1.0 ... need endianness.
// gcc5.3.0 ... need endianness.
// gcc5.2.0 ... need endianness.
// gcc5.1.0 ... need endianness.
// clang4.0.0 . need endianness.
static std::u32string utf16_to_utf32(const std::u16string &s)
{
#if defined(_MSC_VER) && (_MSC_VER <= 1900)
    //  Workaround for missing char16_t/char32_t instantiations in MSVC2015.
    std::wstring_convert<std::codecvt_utf16<std::uint32_t, 0x10ffff, mode>, std::uint32_t> conv;
    const char16_t* data = s.c_str();
    auto bytes = conv.from_bytes(reinterpret_cast<const char*>(data), reinterpret_cast<const char*>(data + s.length()));
    return std::u32string(bytes.cbegin(), bytes.cend());
#else
    std::wstring_convert<std::codecvt_utf16<char32_t, 0x10ffff, mode>, char32_t> conv;
    const char16_t* data = s.c_str();
    return conv.from_bytes(reinterpret_cast<const char*>(data), reinterpret_cast<const char*>(data + s.length()));
#endif
}

// utf32 to utf16
// gcc7.0.0 ... need endianness.
// gcc6.1.0 ... need endianness.
// gcc5.3.0 ... need endianness.
// gcc5.2.0 ... need endianness.
// gcc5.1.0 ... ---
// clang4.0.0 . need endianness.
static std::u16string utf32_to_utf16(const std::u32string& s)
{
#if defined(_MSC_VER) && (_MSC_VER <= 1900)
    //  Workaround for missing char16_t/char32_t instantiations in MSVC2015.
    std::wstring_convert<std::codecvt_utf16<std::uint32_t, 0x10ffff, mode>, std::uint32_t> conv;
    auto p = reinterpret_cast<const std::uint32_t*>(s.c_str());
    auto bytes = conv.to_bytes(p, p + s.length());
    return std::u16string(reinterpret_cast<const char16_t*>(bytes.c_str()), bytes.length() / sizeof(char16_t));
#else
    std::wstring_convert<std::codecvt_utf16<char32_t, 0x10ffff, mode>, char32_t> conv;
    auto bytes = conv.to_bytes(s);
    return std::u16string(reinterpret_cast<const char16_t*>(bytes.c_str()), bytes.length() / sizeof(char16_t));
#endif
}

// ucs2 to utf8
// gcc7.0.0 ... ---
// gcc6.1.0 ... ---
// gcc5.3.0 ... ---
// gcc5.2.0 ... ---
// gcc5.1.0 ... ---
// clang4.0.0 . ---
static std::string ucs2_to_utf8(const std::u16string& s)
{
#if defined(_MSC_VER) && (_MSC_VER <= 1900)
    //  Workaround for missing char16_t/char32_t instantiations in MSVC2015.
    std::wstring_convert<std::codecvt_utf8<std::uint16_t, 0x10ffff, mode>, std::uint16_t> conv;
    auto p = reinterpret_cast<const std::uint16_t*>(s.c_str());
    return conv.to_bytes(p, p + s.length());
#else
    std::wstring_convert<std::codecvt_utf8<char16_t, 0x10ffff, mode>, char16_t> conv;
    return conv.to_bytes(s);
#endif
}

// utf8 to ucs2
// gcc7.0.0 ... ---
// gcc6.1.0 ... need endianness.
// gcc5.3.0 ... need endianness.
// gcc5.2.0 ... need endianness.
// gcc5.1.0 ... ---
// clang4.0.0 . ---
static std::u16string utf8_to_ucs2(const std::string& s)
{
#if defined(_MSC_VER) && (_MSC_VER <= 1900)
    //  Workaround for missing char16_t/char32_t instantiations in MSVC2015.
    std::wstring_convert<std::codecvt_utf8<std::uint16_t, 0x10ffff, mode>, std::uint16_t> conv;
    auto temp = conv.from_bytes(s);
    return std::u16string(temp.cbegin(), temp.cend());
#else
    std::wstring_convert<std::codecvt_utf8<char16_t, 0x10ffff, mode>, char16_t> conv;
    return conv.from_bytes(s);
#endif
}

// ucs2 to utf16
// gcc7.0.0 ... need endianness.
// gcc6.1.0 ... need endianness.
// gcc5.3.0 ... need endianness.
// gcc5.2.0 ... need endianness.
// gcc5.1.0 ... need endianness.
// clang4.0.0 . need endianness.
static std::u16string ucs2_to_utf16(const std::u16string &s)
{
#if defined(_MSC_VER) && (_MSC_VER <= 1900)
    //  Workaround for missing char16_t/char32_t instantiations in MSVC2015.
    std::wstring_convert<std::codecvt_utf16<std::uint16_t, 0x10ffff, mode>, std::uint16_t> conv;
    auto p = reinterpret_cast<const std::uint16_t*>(s.c_str());
    auto bytes = conv.to_bytes(p, p + s.length());
    return std::u16string(reinterpret_cast<const char16_t*>(bytes.c_str()), bytes.length() / sizeof(char16_t));
#else
#if 1
    std::wstring_convert<std::codecvt_utf16<char16_t, 0x10ffff, mode>, char16_t> conv;
    auto bytes = conv.to_bytes(s);
    return std::u16string(reinterpret_cast<const char16_t*>(bytes.c_str()), bytes.length() / sizeof(char16_t));
#else
    std::wstring_convert<std::codecvt_utf16<char16_t>, char16_t> convert;
    std::string bytes = convert.to_bytes(s);

    std::u16string result;
    result.reserve(bytes.size() / 2);

    for (size_t i = 0; i < bytes.size(); i += 2) {
        result.push_back(static_cast<char16_t>(static_cast<unsigned char>(bytes[i]) * 256 + static_cast<unsigned char>(bytes[i + 1])));
    }

    return result;
#endif
#endif
}

// utf16 to ucs2
// gcc7.0.0 ... need endianness.
// gcc6.1.0 ... need endianness.
// gcc5.3.0 ... need endianness.
// gcc5.2.0 ... need endianness.
// gcc5.1.0 ... need endianness.
// clang4.0.0 . need endianness.
static std::u16string utf16_to_ucs2(const std::u16string &s)
{
#if defined(_MSC_VER) && (_MSC_VER <= 1900)
    //  Workaround for missing char16_t/char32_t instantiations in MSVC2015.
    std::wstring_convert<std::codecvt_utf16<std::uint16_t, 0x10ffff, mode>, std::uint16_t> conv;
    const char16_t* data = s.c_str();
    auto bytes = conv.from_bytes(reinterpret_cast<const char*>(data), reinterpret_cast<const char*>(data + s.length()));
    return std::u16string(bytes.cbegin(), bytes.cend());
#else
#if 1
    std::wstring_convert<std::codecvt_utf16<char16_t, 0x10ffff, mode>, char16_t> conv;
    const char16_t* data = s.c_str();
    auto temp = conv.from_bytes(reinterpret_cast<const char*>(data), reinterpret_cast<const char*>(data + s.length()));
    return std::u16string(temp.cbegin(), temp.cend());
#else
    std::string bytes;
    bytes.reserve(s.size() * 2);

    for (const char16_t c : s) {
        bytes.push_back(static_cast<char>(c / 256));
        bytes.push_back(static_cast<char>(c % 256));
    }

    std::wstring_convert<std::codecvt_utf16<char16_t>, char16_t> convert;
    return convert.from_bytes(bytes);
#endif
#endif
}

class TestItem
{
public:
    TestItem(std::string utf8, std::u16string utf16, std::u32string utf32)
        : utf8(std::move(utf8)), utf16(std::move(utf16)), utf32(std::move(utf32))
    {
    }
    std::string utf8;
    std::u16string utf16;
    std::u32string utf32;
};

void Test(const TestItem& item)
{
    // u8 <-> u16
    if(utf8_to_utf16(item.utf8) != item.utf16)
        std::cout << "Failed to convert: utf8_to_utf16" << std::endl;
    if(utf16_to_utf8(item.utf16) != item.utf8)
        std::cout << "Failed to convert: utf16_to_utf8" << std::endl;
    // u8 <-> u32
    if(utf8_to_utf32(item.utf8) != item.utf32)
        std::cout << "Failed to convert: utf8_to_utf32" << std::endl;
    if(utf32_to_utf8(item.utf32) != item.utf8)
        std::cout << "Failed to convert: utf32_to_utf8" << std::endl;
    // u16 <-> u32
    if(utf16_to_utf32(item.utf16) != item.utf32)
        std::cout << "Failed to convert: utf16_to_utf32" << std::endl;
    if(utf32_to_utf16(item.utf32) != item.utf16)
        std::cout << "Failed to convert: utf32_to_utf16" << std::endl;
    // ucs2 <-> utf8
    try{
        if(ucs2_to_utf8(item.utf16) != item.utf8)
            std::cout << "Failed to convert: ucs2_to_utf8" << std::endl;
    }
    catch(const std::range_error&){
        std::cout << "range_error: ucs2_to_utf8" << std::endl;
    }
    try{
        if(utf8_to_ucs2(item.utf8) != item.utf16)
            std::cout << "Failed to convert: utf8_to_ucs2" << std::endl;
    }
    catch(const std::range_error&){
        std::cout << "range_error: utf8_to_ucs2" << std::endl;
    }
    // ucs2 <-> utf16
    try{
        if(ucs2_to_utf16(item.utf16) != item.utf16)
            std::cout << "Failed to convert: ucs2_to_utf16" << std::endl;
    }
    catch(const std::range_error&){
        std::cout << "range_error: ucs2_to_utf16" << std::endl;
    }
    try{
        if(utf16_to_ucs2(item.utf16) != item.utf16)
            std::cout << "Failed to convert: utf16_to_ucs2" << std::endl;
    }
    catch (const std::range_error&){
        std::cout << "range_error: utf16_to_ucs2" << std::endl;
    }
}

bool isLittleEndianSystem()
{
    char16_t test = 0x0102;
    return (reinterpret_cast<char *>(&test))[0] == 0x02;
}

int main(void)
{
#if defined(_MSC_VER)
    std::cout << "_MSC_VER=" << _MSC_VER << std::endl;
    std::cout << "_MSC_FULL_VER=" << _MSC_FULL_VER << std::endl;
#endif
    std::cout << "is littele-endian? " << std::boolalpha << isLittleEndianSystem() << std::endl;
    std::cout << "char16_t is signed? " << std::boolalpha << std::is_signed<char16_t>::value << std::endl;
    std::cout << "char16_t size = " << sizeof(char16_t) << std::endl;
    std::cout << "char32_t is signed? " << std::boolalpha << std::is_signed<char32_t>::value << std::endl;
    std::cout << "char32_t size = " << sizeof(char32_t) << std::endl;
    std::cout << "wchar_t is signed? " << std::boolalpha << std::is_signed<wchar_t>::value << std::endl;
    std::cout << "wchar_t size = " << sizeof(wchar_t) << std::endl;

    std::vector<TestItem> items = {
        TestItem(u8"abcABCあいうえお", u"abcABCあいうえお", U"abcABCあいうえお"),
        TestItem("\x61", u"\x0061", U"\x00000061"),								// a 
        TestItem("\xEF\xBD\x81", u"\xFF41", U"\x0000FF41"),						// ａ 
        TestItem("\xC4\x8D", u"\x010D", U"\x010D"),								// č̌
        TestItem("\x63\xCC\x8C", u"\x0063\x030C", U"\x00000063\x0000030C"),		// c 
        TestItem("\xC4\xB3", u"\x0133", U"\x00000133"),							// ĳ 
        TestItem("\x69\x6A", u"\x0069\x006A", U"\x00000069\x0000006A"),			// ij 
        TestItem("\xCE\xA9", u"\x03A9", U"\x000003A9"),							// Ω 
        TestItem("\xE2\x84\xA6", u"\x2126", U"\x00002126"),						// Ω 
        TestItem("\xF0\x9D\x93\x83", u"\xD835\xDCC3", U"\x0001D4C3")			// 𝓃 
    };
    for(auto item : items){
        std::cout << "* " << item.utf8 << "" << std::endl;
        Test(item);
    }
    return 0;
}