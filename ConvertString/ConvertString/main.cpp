#include <locale>
#include <codecvt>
#include <iostream>
#include <assert.h>
#include <vector>

// utf8 to utf16
static std::u16string utf8_to_utf16(const std::string& s)
{
#if _MSC_VER <= 1900
    //  Workaround for missing char16_t/char32_t instantiations in MSVC2015.
    std::wstring_convert<std::codecvt_utf8_utf16<std::int16_t>, std::int16_t> conv;
    auto temp = conv.from_bytes(s);
    return std::u16string(temp.cbegin(), temp.cend());
#else
    std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> conv;
    return conv.from_bytes(s);
#endif
}

// utf16 to utf8
static std::string utf16_to_utf8(const std::u16string& s)
{
#if _MSC_VER <= 1900
    //  Workaround for missing char16_t/char32_t instantiations in MSVC2015.
    std::wstring_convert<std::codecvt_utf8_utf16<std::int16_t>, std::int16_t> conv;
    auto p = reinterpret_cast<const std::int16_t*>(s.data());
    return conv.to_bytes(p, p + s.length());
#else
    std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> conv;
    return conv.to_bytes(s);
#endif
}

// utf8 to utf32
static std::u32string utf8_to_utf32(const std::string& s)
{
#if _MSC_VER <= 1900
    //  Workaround for missing char16_t/char32_t instantiations in MSVC2015.
    std::wstring_convert<std::codecvt_utf8<std::int32_t>, std::int32_t> conv;
    auto temp = conv.from_bytes(s);
    return std::u32string(temp.cbegin(), temp.cend());
#else
    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> conv;
    return conv.from_bytes(s);
#endif
}

// utf32 to utf8
static std::string utf32_to_utf8(const std::u32string& s)
{
#if _MSC_VER <= 1900
    //  Workaround for missing char16_t/char32_t instantiations in MSVC2015.
    std::wstring_convert<std::codecvt_utf8<std::int32_t>, std::int32_t> conv;
    auto p = reinterpret_cast<const std::int32_t*>(s.data());
    return conv.to_bytes(p, p + s.length());
#else
    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> conv;
    return conv.to_bytes(s);
#endif
}

// utf16 to utf32(little-endian)
static std::u32string utf16_to_utf32_le(const std::u16string &s)
{
#if _MSC_VER <= 1900
    //  Workaround for missing char16_t/char32_t instantiations in MSVC2015.
    const char16_t* data = s.c_str();
    std::wstring_convert<std::codecvt_utf16<std::int32_t, 0x10ffff, std::codecvt_mode::little_endian>, std::int32_t> conv;
    auto bytes = conv.from_bytes(reinterpret_cast<const char*>(data), reinterpret_cast<const char*>(data + s.length()));
    return std::u32string(bytes.cbegin(), bytes.cend());
#else
    const char16_t* data = s.c_str();
    std::wstring_convert<std::codecvt_utf16<char32_t, 0x10ffff, std::codecvt_mode::little_endian>, char32_t> conv;
    return conv.from_bytes(reinterpret_cast<const char*>(data), reinterpret_cast<const char*>(data + s.length()));
#endif
}

// utf16 to utf32(big-endian)
static std::u32string utf16_to_utf32_be(const std::u16string &s)
{
#if _MSC_VER <= 1900
    //  Workaround for missing char16_t/char32_t instantiations in MSVC2015.
    const char16_t* data = s.c_str();
    std::wstring_convert<std::codecvt_utf16<std::int32_t, 0x10ffff>, std::int32_t> conv;
    auto bytes = conv.from_bytes(reinterpret_cast<const char*>(data), reinterpret_cast<const char*>(data + s.length()));
    return std::u32string(bytes.cbegin(), bytes.cend());
#else
    const char16_t* data = s.c_str();
    std::wstring_convert<std::codecvt_utf16<char32_t, 0x10ffff>, char32_t> conv;
    return conv.from_bytes(reinterpret_cast<const char*>(data), reinterpret_cast<const char*>(data + s.length()));
#endif
}

// utf32 to utf16(little-endian)
static std::u16string utf32_to_utf16_le(const std::u32string& s)
{
    //  Workaround for missing char16_t/char32_t instantiations in MSVC2015.
#if _MSC_VER <= 1900
    std::wstring_convert<std::codecvt_utf16<std::int32_t, 0x10ffff, std::codecvt_mode::little_endian>, std::int32_t> conv;
    auto p = reinterpret_cast<const std::int32_t*>(s.data());
    auto bytes = conv.to_bytes(p, p + s.length());
    return std::u16string(reinterpret_cast<const char16_t*>(bytes.c_str()), bytes.length() / sizeof(char16_t));
#else
    std::wstring_convert<std::codecvt_utf16<char32_t, 0x10ffff, std::codecvt_mode::little_endian>, char32_t> conv;
    auto bytes = conv.to_bytes(s);
    return std::u16string(reinterpret_cast<const char16_t*>(bytes.c_str()), bytes.length() / sizeof(char16_t));
#endif
}

// utf32 to utf16(big-endian)
static std::u16string utf32_to_utf16_be(const std::u32string& s)
{
    //  Workaround for missing char16_t/char32_t instantiations in MSVC2015.
#if _MSC_VER <= 1900
    std::wstring_convert<std::codecvt_utf16<std::int32_t, 0x10ffff>, std::int32_t> conv;
    auto p = reinterpret_cast<const std::int32_t*>(s.data());
    auto bytes = conv.to_bytes(p, p + s.length());
    return std::u16string(reinterpret_cast<const char16_t*>(bytes.c_str()), bytes.length() / sizeof(char16_t));
#else
    std::wstring_convert<std::codecvt_utf16<char32_t, 0x10ffff>, char32_t> conv;
    auto bytes = conv.to_bytes(s);
    return std::u16string(reinterpret_cast<const char16_t*>(bytes.c_str()), bytes.length() / sizeof(char16_t));
#endif
}

// ucs2 to utf8
static std::string ucs2_to_utf8(const std::u16string& s)
{
#if _MSC_VER <= 1900
    //  Workaround for missing char16_t/char32_t instantiations in MSVC2015.
    std::wstring_convert<std::codecvt_utf8<std::int16_t>, std::int16_t> conv;
    auto p = reinterpret_cast<const std::int16_t*>(s.data());
    return conv.to_bytes(p, p + s.length());
#else
    std::wstring_convert<std::codecvt_utf8<char16_t>, char16_t> conv;
    return conv.to_bytes(s);
#endif
}

// utf8 to ucs2
static std::u16string utf8_to_ucs2(const std::string& s)
{
#if _MSC_VER <= 1900
    //  Workaround for missing char16_t/char32_t instantiations in MSVC2015.
    std::wstring_convert<std::codecvt_utf8<std::int16_t>, std::int16_t> conv;
    auto temp = conv.from_bytes(s);
    return std::u16string(temp.cbegin(), temp.cend());
#else
    std::wstring_convert<std::codecvt_utf8<char16_t>, char16_t> conv;
    return conv.from_bytes(s);
#endif
}

class TestString
{
public:
    TestString(std::string utf8, std::u16string utf16, std::u32string utf32)
        : utf8(std::move(utf8)), utf16(std::move(utf16)), utf32(std::move(utf32))
    {
    }
    std::string utf8;
    std::u16string utf16;
    std::u32string utf32;
};

void Test(const TestString& s)
{
    // u8 <-> u16
    if(utf8_to_utf16(s.utf8) != s.utf16)
        std::cout << "Failed to convert: utf8_to_utf16" << std::endl;
    if(utf16_to_utf8(s.utf16) != s.utf8)
        std::cout << "Failed to convert: utf16_to_utf8" << std::endl;
    // u8 <-> u32
    if(utf8_to_utf32(s.utf8) != s.utf32)
        std::cout << "Failed to convert: utf8_to_utf32" << std::endl;
    if(utf32_to_utf8(s.utf32) != s.utf8)
        std::cout << "Failed to convert: utf32_to_utf8" << std::endl;
    // u16 <-> u32
    if(utf16_to_utf32_le(s.utf16) != s.utf32)
        std::cout << "Failed to convert: utf16_to_utf32_le" << std::endl;
    if(utf32_to_utf16_le(s.utf32) != s.utf16)
        std::cout << "Failed to convert: utf32_to_utf16_le" << std::endl;
    // ucs2 <-> utf8
    try{
        if(ucs2_to_utf8(s.utf16) != s.utf8)
            std::cout << "Failed to convert: ucs2_to_utf8" << std::endl;
    }catch (const std::range_error&){
        std::cout << "range_error: ucs2_to_utf8" << std::endl;
    }
    try{
        if(utf8_to_ucs2(s.utf8) != s.utf16)
            std::cout << "Failed to convert: utf8_to_ucs2" << std::endl;
    }
    catch(const std::range_error&){
        std::cout << "range_error: utf8_to_ucs2" << std::endl;
    }
    // ucs2 <-> utf16
}

void main()
{
    // https://social.msdn.microsoft.com/Forums/en-US/8f40dcd8-c67f-4eba-9134-a19b9178e481/vs-2015-rc-linker-stdcodecvt-error?forum=vcgeneral

    std::cout << "_MSC_VER=" << _MSC_VER << std::endl;
    std::cout << "_MSC_FULL_VER=" << _MSC_FULL_VER << std::endl;

    std::vector<TestString> strings = {
        //TestString(u8"abcABCあいうえお", u"abcABCあいうえお", U"abcABCあいうえお"),
        //TestString("\x61", u"\x0061", U"\x00000061"),
        //TestString("\xEF\xBD\x81", u"\xFF41", U"\x0000FF41"),
        //TestString("\xC4\x8D", u"\x010D", U"\x010D"),
        //TestString("\x63\xCC\x8C", u"\x0063\x030C", U"\x00000063\x0000030C"),
        //TestString("\xC4\xB3", u"\x0133", U"\x00000133"),
        //TestString("\x69\x6A", u"\x0069\x006A", U"\x00000069\x0000006A"),
        //TestString("\xCE\xA9", u"\x03A9", U"\x000003A9"),
        //TestString("\xE2\x84\xA6", u"\x2126", U"\x00002126"),
        TestString("\xF0\x9D\x93\x83", u"\xD835\xDCC3", U"\x0001D4C3")
    };
    for(auto s : strings){
        std::cout << "* " << s.utf8 << "" << std::endl;
        Test(s);
    }
}