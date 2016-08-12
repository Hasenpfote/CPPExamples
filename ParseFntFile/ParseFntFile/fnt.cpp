#include <fstream>
#include <sstream>
#include <regex>
#include <iostream>
#include <cassert>
#include "fnt.h"

namespace fnt{

void Info::Parse(const std::string& source)
{
    std::smatch match;
    if(std::regex_search(source, match, std::regex(R"(face=\"([\w|\+|\s]+)\")"))){
        face = match[1];
    }
    if(std::regex_search(source, match, std::regex(R"(size=([\d]+))"))){
        size = std::stoi(match[1]);
    }
    if(std::regex_search(source, match, std::regex(R"(bold=([\d]+))"))){
        bold = std::stoi(match[1]) > 0;
    }
    if(std::regex_search(source, match, std::regex(R"(italic=([\d]+))"))){
        italic = std::stoi(match[1]) > 0;
    }
    if(std::regex_search(source, match, std::regex(R"(charset=\"([\w|-]*)\")"))){
        charset = match[1];
    }
    if(std::regex_search(source, match, std::regex(R"(unicode=([\d]+))"))){
        unicode = std::stoi(match[1]) > 0;
    }
    if(std::regex_search(source, match, std::regex(R"(stretchH=([\d]+))"))){
        stretchH = std::stoi(match[1]);
    }
    if(std::regex_search(source, match, std::regex(R"(smooth=([\d]+))"))){
        smooth = std::stoi(match[1]) > 0;
    }
    if(std::regex_search(source, match, std::regex(R"(aa=([\d]+))"))){
        aa = std::stoi(match[1]) > 0;
    }
    if(std::regex_search(source, match, std::regex(R"(padding=([\d]+),([\d]+),([\d]+),([\d]+))"))) {
        std::get<0>(padding) = std::stoi(match[1]);
        std::get<1>(padding) = std::stoi(match[2]);
        std::get<2>(padding) = std::stoi(match[3]);
        std::get<3>(padding) = std::stoi(match[4]);
    }
    if(std::regex_search(source, match, std::regex(R"(spacing=([\d]+),([\d]+))"))){
        std::get<0>(spacing) = std::stoi(match[1]);
        std::get<1>(spacing) = std::stoi(match[2]);
    }
}

void Common::Parse(const std::string& source)
{
    std::smatch match;
    if(std::regex_search(source, match, std::regex(R"(lineHeight=([\d]+))"))){
        lineHeight = std::stoi(match[1]);
    }
    if(std::regex_search(source, match, std::regex(R"(base=([\d]+))"))){
        base = std::stoi(match[1]);
    }
    if(std::regex_search(source, match, std::regex(R"(scaleW=([\d]+))"))){
        scaleW = std::stoi(match[1]);
    }
    if(std::regex_search(source, match, std::regex(R"(scaleH=([\d]+))"))){
        scaleH = std::stoi(match[1]);
    }
    if(std::regex_search(source, match, std::regex(R"(pages=([\d]+))"))){
        pages = std::stoi(match[1]);
    }
    if(std::regex_search(source, match, std::regex(R"(packed=([\d]+))"))){
        packed = std::stoi(match[1]);
    }
}

void Character::Parse(const std::string& source)
{
#if 0
    // debug mode では異常に遅い.
    static const std::regex x_re(R"(x=([\d]+))");
    static const std::regex y_re(R"(y=([\d]+))");
    static const std::regex width_re(R"(width=([\d]+))");
    static const std::regex height_re(R"(height=([\d]+))");
    static const std::regex xoffset_re(R"(xoffset=([-]{0,1}[\d]+))");
    static const std::regex yoffset_re(R"(yoffset=([-]{0,1}[\d]+))");
    static const std::regex xadvance_re(R"(xadvance=([\d]+))");
    static const std::regex page_re(R"(page=([\d]+))");
    static const std::regex chnl_re(R"(chnl=([\d]+))");

    std::smatch match;
    if(std::regex_search(source, match, x_re)){
        x = std::stoi(match[1]);
    }
    if(std::regex_search(source, match, y_re)){
        y = std::stoi(match[1]);
    }
    if(std::regex_search(source, match, width_re)){
        width = std::stoi(match[1]);
    }
    if(std::regex_search(source, match, height_re)){
        height = std::stoi(match[1]);
    }
    if(std::regex_search(source, match, xoffset_re)){
        xoffset = std::stoi(match[1]);
    }
    if(std::regex_search(source, match, yoffset_re)){
        yoffset = std::stoi(match[1]);
    }
    if(std::regex_search(source, match, xadvance_re)){
        xadvance = std::stoi(match[1]);
    }
    if(std::regex_search(source, match, page_re)){
        page = std::stoi(match[1]);
    }
    if(std::regex_search(source, match, chnl_re)){
        chnl = std::stoi(match[1]);
    }
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