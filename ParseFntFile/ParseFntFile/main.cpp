#include <filesystem>   // std::tr2::sys::path etc.
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <regex>
#include <tuple>
#include "fnt.h"

namespace sys = std::tr2::sys;

bool parse(const sys::path& filepath)
{
    std::ifstream ifs(filepath.string(), std::ios::in | std::ios::binary);
    if(ifs.fail()){
        return false;
    }
    std::istreambuf_iterator<char> it(ifs);
    std::istreambuf_iterator<char> last;
    std::string source(it, last);

    std::istringstream iss(source);
    std::string field;

#if 1
    std::regex info_re(R"(^info[\s]+)");
    std::smatch match;
    while(std::getline(iss, field, '\n')){
        if(std::regex_search(field, match, info_re)){
            std::cout << "aaa" << std::endl;
            for(auto sub : match){
                std::cout << *sub.first << std::endl;
                std::cout << *sub.second << std::endl;
            }
        }
    }
#else
    std::regex info_re(R"(^info[\s]+face=\"([\w|\+|\s]+)\"[\s]+size=([\d]+)[\s]+bold=([\d]+)[\s]+italic=([\d]+)[\s]+charset=\"([\w]*)\"[\s]+unicode=([\d]+)[\s]+stretchH=([\d]+)[\s]+smooth=([\d]+)[\s]+aa=([\d]+)[\s]+padding=([\d]+,[\d]+,[\d]+,[\d]+)[\s]+spacing=([\d]+,[\d]+)[\s]*$)");
    std::regex common_re(R"(^common[\s]+lineHeight=([\d]+)[\s]+base=([\d]+)[\s]+scaleW=([\d]+)[\s]+scaleH=([\d]+)[\s]+pages=([\d]+)[\s]+packed=([\d]+)[\s]*$)");
    std::regex page_re(R"(^page[\s]+id=([\d]+)[\s]+file=\"([\w|\.|-]+)\"$)");
    std::regex char_re(R"(^char[\s]+id=([\d]+)[\s]+x=([\d]+)[\s]+y=([\d]+)[\s]+width=([\d]+)[\s]+height=([\d]+)[\s]+xoffset=([-]{0,1}[\d]+)[\s]+yoffset=([-]{0,1}[\d]+)[\s]+xadvance=([\d]+)[\s]+page=([\d]+)[\s]+chnl=([\d]+)[\s]*$)");
    std::regex chars_re(R"(^chars[\s]+count=([\d]+)[\s]*$)");
    std::smatch match;
    int count = 0;
    while(std::getline(iss, field, '\n')){
        if(regex_match(field, match, info_re)){
            for (auto str : match) {
                std::cout << str << std::endl;
            }
        }
        if(regex_match(field, match, common_re)){
            for(auto str : match){
                std::cout << str << std::endl;
            }
        }
        if(regex_match(field, match, page_re)){
            for(auto str : match){
                std::cout << str << std::endl;
            }
        }
        if(regex_match(field, match, chars_re)){
            for(auto str : match){
                std::cout << str << std::endl;
            }
        }
        if(regex_match(field, match, char_re)){
            count++;
        }
    }
    std::cout << "Count=" << count << std::endl;
    std::cout << "Done." << std::endl;
#endif
    return true;
}

void main()
{
    const sys::path filepath = "mp1mm16tir.fnt";
#if 0
    auto result = parse(filepath);
#else
    fnt::Fnt f;
    f.Load(filepath);
#endif
}