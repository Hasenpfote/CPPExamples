#pragma once
#include <cinttypes>
#include <string>
#include <tuple>
#include <unordered_map>
#include <filesystem>   // std::tr2::sys::path etc.

namespace fnt{

class Info final
{
public:
    Info() = default;
    ~Info() = default;
    void Parse(const std::string& source);

private:
    std::string face;
    std::uint32_t size;
    bool bold;
    bool italic;
    std::string charset;
    bool unicode;
    std::uint32_t stretchH;
    bool smooth;
    bool aa;
    std::tuple<std::uint32_t, std::uint32_t, std::uint32_t, std::uint32_t> padding;
    std::tuple<std::uint32_t, std::uint32_t> spacing;
};

class Common final
{
public:
    Common() = default;
    ~Common() = default;
    void Parse(const std::string& source);

private:
    std::uint32_t lineHeight;
    std::uint32_t base;
    std::uint32_t scaleW;
    std::uint32_t scaleH;
    std::uint32_t pages;
    std::uint32_t packed;
};

class Character final
{
public:
    Character() = default;
    ~Character() = default;
    void Parse(const std::string& source);

private:
    std::uint32_t x;
    std::uint32_t y;
    std::uint32_t width;
    std::uint32_t height;
    std::int32_t xoffset;
    std::int32_t yoffset;
    std::uint32_t xadvance;
    std::uint32_t page;
    std::uint32_t chnl;
};

class Fnt final
{
public:
    bool Load(const std::tr2::sys::path& filepath);

private:
    Info info;
    Common common;
    std::unordered_map<std::uint32_t, std::string> page;
    std::unordered_map<std::uint32_t, Character> character;
};

}