#include <locale>
#include <codecvt>
#include <iostream>
#include <assert.h>

// utf8 to utf16
static std::u16string to_utf16(const std::string& s)
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
static std::string to_utf8(const std::u16string& s)
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
static std::u32string to_utf32(const std::string& s)
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
static std::string to_utf8(const std::u32string& s)
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

// TODO
//static constexpr std::codecvt_mode mode = (std::codecvt_mode)0;
static constexpr std::codecvt_mode mode = std::codecvt_mode::little_endian;

// utf16 to utf32
static std::u32string to_utf32(const std::u16string &s)
{
#if _MSC_VER <= 1900
    //  Workaround for missing char16_t/char32_t instantiations in MSVC2015.
    const char16_t* data = s.c_str();
    std::wstring_convert<std::codecvt_utf16<std::int32_t, 0x10ffff, mode>, std::int32_t> conv;
    auto bytes = conv.from_bytes(reinterpret_cast<const char*>(data), reinterpret_cast<const char*>(data + s.length()));
    return std::u32string(bytes.cbegin(), bytes.cend());
#else
    const char16_t* data = s.c_str();
    std::wstring_convert<std::codecvt_utf16<char32_t, 0x10ffff, mode>, char32_t> conv;
    return conv.from_bytes(reinterpret_cast<const char*>(data), reinterpret_cast<const char*>(data + s.length()));
#endif
}

// utf32 to utf16
static std::u16string to_utf16(const std::u32string& s)
{
    //  Workaround for missing char16_t/char32_t instantiations in MSVC2015.
#if _MSC_VER <= 1900
    std::wstring_convert<std::codecvt_utf16<std::int32_t, 0x10ffff, mode>, std::int32_t> conv;
    auto p = reinterpret_cast<const std::int32_t*>(s.data());
    auto bytes = conv.to_bytes(p, p + s.length());
    return std::u16string(reinterpret_cast<const char16_t*>(bytes.c_str()), bytes.length() / sizeof(char16_t));
#else
    std::wstring_convert<std::codecvt_utf16<char32_t, 0x10ffff, mode>, char32_t> conv;
    auto bytes = conv.to_bytes(s);
    return std::u16string(reinterpret_cast<const char16_t*>(bytes.c_str()), bytes.length() / sizeof(char16_t));
#endif
}

void main()
{
    // https://social.msdn.microsoft.com/Forums/en-US/8f40dcd8-c67f-4eba-9134-a19b9178e481/vs-2015-rc-linker-stdcodecvt-error?forum=vcgeneral

    std::cout << "_MSC_VER=" << _MSC_VER << std::endl;
    std::cout << "_MSC_FULL_VER=" << _MSC_FULL_VER << std::endl;
 
    std::string u8src = u8"abcABCあいうえお";
    std::u16string u16src = u"abcABCあいうえお";
    std::u32string u32src = U"abcABCあいうえお";

    // u8 <-> u16
    assert(to_utf16(u8src) == u16src);
    assert(to_utf8(to_utf16(u8src)) == u8src);
    assert(to_utf8(u16src) == u8src);
    assert(to_utf16(to_utf8(u16src)) == u16src);

    // u8 <-> u32
    assert(to_utf32(u8src) == u32src);
    assert(to_utf8(to_utf32(u8src)) == u8src);
    assert(to_utf8(u32src) == u8src);
    assert(to_utf32(to_utf8(u32src)) == u32src);
    // u16 <-> u32
    assert(to_utf32(u16src) == u32src);
    assert(to_utf16(to_utf32(u16src)) == u16src);
    assert(to_utf16(u32src) == u16src);
    assert(to_utf32(to_utf16(u32src)) == u32src);
}