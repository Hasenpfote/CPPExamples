#include <locale>
#include <codecvt>
#include <iostream>

// utf8 to utf16
static std::u16string to_utf16(const std::string& s)
{
    std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> conv;
    return conv.from_bytes(s);
}

// utf16 to utf8
static std::string to_utf8(const std::u16string& s)
{
    std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> conv;
    return conv.to_bytes(s);
}

// utf8 to utf32
static std::u32string to_utf32(const std::string& s)
{
    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> conv;
    return conv.from_bytes(s);
}

// utf32 to utf8
static std::string to_utf8(const std::u32string& s)
{
    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> conv;
    return conv.to_bytes(s);
}

// utf16 to utf32
static std::u32string to_utf32(const std::u16string &s)
{
    const char16_t* pData = s.c_str();
    std::wstring_convert<std::codecvt_utf16<char32_t>, char32_t> conv;
    return conv.from_bytes(reinterpret_cast<const char*>(pData), reinterpret_cast<const char*>(pData + s.length()));
}

// utf32 to utf16
static std::u16string to_utf16(const std::u32string& s)
{
    std::wstring_convert<std::codecvt_utf16<char32_t>, char32_t> conv;
    std::string bytes = conv.to_bytes(s);
    return std::u16string(reinterpret_cast<const char16_t*>(bytes.c_str()), bytes.length() / sizeof(char16_t));
}

void main()
{
    // https://social.msdn.microsoft.com/Forums/en-US/8f40dcd8-c67f-4eba-9134-a19b9178e481/vs-2015-rc-linker-stdcodecvt-error?forum=vcgeneral
    //auto u16s = to_utf16(u8"abc");
    //auto u32s = to_utf32(u8"abc");
#if 0
    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> converter;
    std::string u8str = u8"あいうえお";
    std::u32string u32str = converter.from_bytes(u8str);
    std::size_t codepoint_count = u32str.size();
    std::cout << codepoint_count << std::endl;
#endif
}