#include <iostream>
#include <memory>
#include <vector>
#include <tuple>
#include <unicode/ucnv.h>
#include <unicode/brkiter.h>

void disp(const icu::UnicodeString& s)
{
    std::cout << std::dec << "length = " << s.length() << std::endl;
    for(std::int32_t i = 0; i < s.length(); i++){
        std::cout << std::dec << "[" << i << "] " << std::hex << std::showbase << s.charAt(i) << std::endl;
    }
}

void disp_line_breaks(const icu::UnicodeString& s, const icu::Locale& locale, UErrorCode& status)
{
    using namespace icu;

    auto bi = std::unique_ptr<BreakIterator>(BreakIterator::createLineInstance(locale, status));
    bi->setText(s);
    auto p = bi->first();
    while(p != BreakIterator::DONE){
        std::cout << std::dec << "Boundary at position " << p << " (" << bi->getRuleStatus() << ")" << std::endl;
        p = bi->next();
    }
    /*
    typedef enum ULineBreakTag {
    171     UBRK_LINE_SOFT            = 0,
    173     UBRK_LINE_SOFT_LIMIT      = 100,
    175     UBRK_LINE_HARD            = 100,
    177     UBRK_LINE_HARD_LIMIT      = 200
    178 } ULineBreakTag;
    */
}

void disp_chunks(const std::u16string& u16)
{
    using namespace icu;

    UnicodeString s = UnicodeString((const char*)u16.c_str(), u16.size() * sizeof(char16_t), "UTF-16LE");
    UErrorCode status = U_ZERO_ERROR;
    auto bi = std::unique_ptr<BreakIterator>(BreakIterator::createLineInstance(Locale::getUS() , status));
    bi->setText(s);
    auto p = bi->first();
    while(p != BreakIterator::DONE){
        auto np = bi->next();
        if(np == BreakIterator::DONE)
            break;
        auto chunk = s.tempSubString(p, np - p);
        disp(chunk);
        p = np;
    }
}

using LineBreak = std::tuple<std::size_t, bool>;

std::vector<LineBreak>
find_line_breaks(const std::u16string& u16)
{
    using namespace icu;

    UErrorCode status = U_ZERO_ERROR;
    //auto bi = std::unique_ptr<BreakIterator>(BreakIterator::createLineInstance(Locale::getUS(), status));
    //auto bi = std::unique_ptr<BreakIterator>(BreakIterator::createLineInstance(Locale::getJapanese(), status));
    auto bi = std::unique_ptr<BreakIterator>(BreakIterator::createLineInstance(Locale::getDefault(), status));
    //auto bi = std::unique_ptr<BreakIterator>(BreakIterator::createSentenceInstance(Locale::getDefault(), status));
    //auto bi = std::unique_ptr<BreakIterator>(BreakIterator::createSentenceInstance(Locale::getUS(), status));

    UnicodeString s = UnicodeString((const char*)u16.c_str(), u16.size() * sizeof(char16_t), "UTF-16LE");
    bi->setText(s);
    std::vector<LineBreak> result;
    auto p = bi->first();
    while(p != BreakIterator::DONE){
        result.emplace_back(p, (bi->getRuleStatus() != UBRK_LINE_SOFT));
        p = bi->next();
    }
    return result;
}

/*
    要求:
    (1) 強制改行まで幅を超えない限り進め、複数のチャンクで一行分のテキストを構築する
    (2) チャンクを１つ確定した時点で幅を超えている場合、そのチャンクを一行分のテキストとし強制表示または非表示
*/
void func(const std::u16string& u16, std::size_t width)
{
    auto line = 0;
    auto lbs = find_line_breaks(u16);
    auto it = lbs.cbegin();
    while((it + 1) != lbs.cend()){
        auto s_pos = std::get<0>(*it);
        do{
            auto e_pos = std::get<0>(*(it + 1));
            auto chunk = u16.substr(s_pos, e_pos - s_pos);
            auto len = chunk.length();
            if(len > width){
                if(std::get<0>(*it) != s_pos)
                    break;
            }
            it++;
        }while(((it + 1) != lbs.cend()) && !std::get<1>(*it));

        auto e_pos = std::get<0>(*(it));
        auto chunk = u16.substr(s_pos, e_pos - s_pos);
        std::cout << std::dec << "[" << line << "] [" << s_pos << ", " << e_pos << ") len=" << chunk.length() << std::endl;
        line++;
#if 1
        auto s = icu::UnicodeString((const char*)chunk.c_str(), chunk.size() * sizeof(char16_t), "UTF-16LE");
        std::string u8;
        s.toUTF8String(u8);
        std::cout << u8 << std::endl;
#endif
    }
}

int main()
{
    using namespace icu;

    UErrorCode status = U_ZERO_ERROR;

    {
        std::cout << Locale::getDefault().getBaseName() << std::endl;
        std::cout << Locale::getRoot().getBaseName() << std::endl;
    }
    std::cout << "------------------------------" << std::endl;
    {
        std::u16string u16 = u"「あいうえお、かき\r\nくけこ。」";
        /*
            00:「   chunk0
            01:あ   chunk0
            02:い   chunk1
            03:う   chunk2
            04:え   chunk3
            05:お   chunk4
            06:、   chunk4
            07:か   chunk5
            08:き   chunk6
            09:\r   chunk6
            10:\n   chunk6
            11:く   chunk7
            12:け   chunk8
            13:こ   chunk9
            14:。   chunk9
            15:」   chunk9
        */
        UnicodeString s = UnicodeString((const char*)u16.c_str(), u16.size() * sizeof(char16_t), "UTF-16LE");
        disp(s);
        disp_line_breaks(s, Locale::getJapanese(), status);
        disp_chunks(u16);
    }
    std::cout << "------------------------------" << std::endl;
    {
        std::u16string u16 = u"あいうえお、かき\nくけこ。hello.";
        /*
            00:あ    chunk0
            01:い    chunk1
            02:う    chunk2
            03:え    chunk3
            04:お    chunk4
            05:、    chunk4
            06:か    chunk5
            07:き    chunk6
            08:\n    chunk6
            09:く    chunk7
            10:け    chunk8
            11:こ    chunk9
            12:。    chunk9
            13:h     chunk10
            14:e     chunk10
            15:l     chunk10
            16:l     chunk10
            17:o     chunk10
            18:.     chunk10
        */
        UnicodeString s = UnicodeString((const char*)u16.c_str(), u16.size() * sizeof(char16_t), "UTF-16LE");
        disp(s);
        disp_line_breaks(s, Locale::getJapanese(), status);
        disp_chunks(u16);
    }
    std::cout << "------------------------------" << std::endl;
    {
        //std::u16string u16 = u"abc-def.";
        //std::u16string u16 = u"abc\ndef.";
        //std::u16string u16 = u"あいうえお、かき\nくけこ。hello.";
        //std::u16string u16 = u"「あいうえお、かき\r\nくけこ。」";
        //std::u16string u16 = u"Abraham \"Bram\" Stoker (8 November 1847 – 20 April 1912) was an Irish author, best known today for his 1897 Gothic novel Dracula. During his lifetime, he was better known as the personal assistant of actor Henry Irving and business manager of the Lyceum Theatre in London, which Irving owned.";
        std::u16string u16 = u"3 May. Bistritz. __Left Munich at 8:35 P. M, on 1st May, arriving at Vienna early next morning; should have arrived at 6:46, but train was an hour late. Buda-Pesth seems a wonderful place, from the glimpse which I got of it from the train and the little I could walk through the streets. I feared to go very far from the station, as we had arrived late and would start as near the correct time as possible.";

        func(u16, 2);
    }
    return 0;
}