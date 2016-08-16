#include <fstream>
#include <sstream>
#include <regex>
#include <iostream>
#include <cassert>
#include "fnt.h"

namespace fnt{
#if 0
template <typename T, typename = std::enable_if_t<std::is_integral<T>::value>>
T GetValue(const std::string& source, const std::string& name, T default_value)
{
    std::smatch match;
    if(std::regex_search(source, match, std::regex(name + R"(=([-]{0,1}[\d]+))")))
        return static_cast<T>(std::stoi(match[1]));
    return default_value;
}

template <>
long GetValue(const std::string& source, const std::string& name, long default_value)
{
    std::smatch match;
    if(std::regex_search(source, match, std::regex(name + R"(=([-]{0,1}[\d]+))")))
        return std::stol(match[1]);
    return default_value;
}

template <>
bool GetValue(const std::string& source, const std::string& name, bool default_value)
{
    std::smatch match;
    if(std::regex_search(source, match, std::regex(name + R"(=([-]{0,1}[\d]+))")))
        return std::stoi(match[1]) > 0;
    return default_value;
}
#endif

static std::int32_t GetValue1i(const std::string& source, const std::string& name, std::int32_t default_value = 0)
{
    std::smatch match;
    if(std::regex_search(source, match, std::regex(name + R"(=([-]{0,1}[\d]+))")))
        return static_cast<std::int32_t>(std::stoi(match[1]));
    return default_value;
}

static std::tuple<std::int32_t, std::int32_t>
GetValue2i(const std::string& source, const std::string& name, const std::tuple<std::int32_t, std::int32_t>& default_value = { 0,0 })
{
    std::smatch match;
    if(std::regex_search(source, match, std::regex(name + R"(=([-]{0,1}[\d]+),([-]{0,1}[\d]+))")))
        return std::make_tuple(
            static_cast<std::int32_t>(std::stoi(match[1])),
            static_cast<std::int32_t>(std::stoi(match[2])));
    return default_value;
}

static std::tuple<std::int32_t, std::int32_t, std::int32_t, std::int32_t>
GetValue4i(const std::string& source, const std::string& name, const std::tuple<std::int32_t, std::int32_t, std::int32_t, std::int32_t>& default_value = { 0,0,0,0 })
{
    std::smatch match;
    if(std::regex_search(source, match, std::regex(name + R"(=([-]{0,1}[\d]+),([-]{0,1}[\d]+),([-]{0,1}[\d]+),([-]{0,1}[\d]+))")))
        return std::make_tuple(
            static_cast<std::int32_t>(std::stoi(match[1])),
            static_cast<std::int32_t>(std::stoi(match[2])),
            static_cast<std::int32_t>(std::stoi(match[3])),
            static_cast<std::int32_t>(std::stoi(match[4])));
    return default_value;
}

static bool GetValue1b(const std::string& source, const std::string& name, bool default_value = false)
{
    std::smatch match;
    if(std::regex_search(source, match, std::regex(name + R"(=([\d]))")))
        return std::stoi(match[1]) > 0;
    return default_value;
}

static std::string GetString(const std::string& source, const std::string& name)
{
    std::smatch match;
    if(std::regex_search(source, match, std::regex(name + R"(=\"([\w|\s|\+|-]*)\")")))
        return match[1];
    return "";
}

void Info::Parse(const std::string& source)
{
    face = GetString(source, "face");
    size = GetValue1i(source, "size");
    bold = GetValue1b(source, "bold");
    italic = GetValue1b(source, "italic");
    charset = GetString(source, "charset");
    unicode = GetValue1b(source, "unicode");
    stretchH = GetValue1i(source, "stretchH");
    smooth = GetValue1b(source, "smooth");
    aa = GetValue1b(source, "aa");
    padding = GetValue4i(source, "padding");
    spacing = GetValue2i(source, "spacing");
}

void Common::Parse(const std::string& source)
{
    lineHeight = GetValue1i(source, "lineHeight");
    base = GetValue1i(source, "base");
    scaleW = GetValue1i(source, "scaleW");
    scaleH = GetValue1i(source, "scaleH");
    pages = GetValue1i(source, "pages");
    packed = GetValue1i(source, "packed");
}

void Character::Parse(const std::string& source)
{
#if 0
    // debug mode では異常に遅い.
    x = GetValue1i(source, "x");
    y = GetValue1i(source, "y");
    width = GetValue1i(source, "width");
    height = GetValue1i(source, "height");
    xoffset = GetValue1i(source, "xoffset");
    yoffset = GetValue1i(source, "yoffset");
    xadvance = GetValue1i(source, "xadvance");
    page = GetValue1i(source, "page");
    chnl = GetValue1i(source, "chnl");
#else
    static const std::string x_tag = "x=";
    static const std::string y_tag = "y=";
    static const std::string width_tag = "width=";
    static const std::string height_tag = "height=";
    static const std::string xoffset_tag = "xoffset=";
    static const std::string yoffset_tag = "yoffset=";
    static const std::string xadvance_tag = "xadvance=";
    static const std::string page_tag = "page=";
    static const std::string chnl_tag = "chnl=";

    std::size_t start = 0;
    std::string delim = " ";
    auto end = source.find(delim);
    while(end != std::string::npos){
        auto sub = source.substr(start, end - start);
        if(!sub.empty()){
            if(sub.compare(0, x_tag.length(), x_tag) == 0){
                x = std::stoi(sub.substr(x_tag.length()));
            }
            else
            if(sub.compare(0, y_tag.length(), y_tag) == 0){
                y = std::stoi(sub.substr(y_tag.length()));
            }
            else
            if(sub.compare(0, width_tag.length(), width_tag) == 0){
                width = std::stoi(sub.substr(width_tag.length()));
            }
            else
            if(sub.compare(0, height_tag.length(), height_tag) == 0){
                height = std::stoi(sub.substr(height_tag.length()));
            }
            else
            if(sub.compare(0, xoffset_tag.length(), xoffset_tag) == 0){
                xoffset = std::stoi(sub.substr(xoffset_tag.length()));
            }
            else
            if(sub.compare(0, yoffset_tag.length(), yoffset_tag) == 0){
                yoffset = std::stoi(sub.substr(yoffset_tag.length()));
            }
            else
            if(sub.compare(0, xadvance_tag.length(), xadvance_tag) == 0){
                xadvance = std::stoi(sub.substr(xadvance_tag.length()));
            }
            else
            if(sub.compare(0, page_tag.length(), page_tag) == 0){
                page = std::stoi(sub.substr(page_tag.length()));
            }
            else
            if(sub.compare(0, chnl_tag.length(), chnl_tag) == 0){
                chnl = std::stoi(sub.substr(chnl_tag.length()));
            }
        }
        start = end + delim.length();
        end = source.find(delim, start);
    }
#endif
}

bool Fnt::Load(const std::tr2::sys::path& filepath)
{
    std::ifstream ifs(filepath.string(), std::ios::in | std::ios::binary);
    if(ifs.fail()){
        return false;
    }
    const std::string info_tag = "info ";
    const std::string common_tag = "common ";
    const std::string page_tag = "page ";
    const std::string chars_tag = "chars ";
    const std::string char_tag = "char ";

    Character c;
    int num_chars = 0;
    std::string field;
    while(std::getline(ifs, field, '\n')){
        if(field.compare(0, info_tag.length(), info_tag) == 0){
            info.Parse(field);
        }
        else
        if(field.compare(0, common_tag.length(), common_tag) == 0){
            common.Parse(field);
        }
        else
        if(field.compare(0, page_tag.length(), page_tag) == 0){
            std::smatch match;
            std::uint32_t id = 0;
            if(std::regex_search(field, match, std::regex(R"(id=([\d]+))"))){
                id = std::stoi(match[1]);
            }
            std::string file;
            if(std::regex_search(field, match, std::regex(R"(file=\"([\w|\.|-]+)\")"))){
                file = match[1];
            }
            page.emplace(
                std::piecewise_construct,
                std::forward_as_tuple(id),
                std::forward_as_tuple(file)
            );
        }
        else
        if(field.compare(0, chars_tag.length(), chars_tag) == 0){
            std::smatch match;
            if(std::regex_search(field, match, std::regex(R"(count=([\d]+))"))){
                num_chars = std::stoi(match[1]);
            }
        }
        else
        if(field.compare(0, char_tag.length(), char_tag) == 0){
            std::smatch match;
            std::uint32_t id = 0;
            if(std::regex_search(field, match, std::regex(R"(id=([\d]+))"))){
                id = std::stoi(match[1]);
            }
            c.Parse(field);
            character.emplace(
                std::piecewise_construct,
                std::forward_as_tuple(id),
                std::forward_as_tuple(c)
            );
        }
    }
    assert(character.size() == (num_chars+1));
    return true;
}

};