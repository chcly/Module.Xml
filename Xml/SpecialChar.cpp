/*
-------------------------------------------------------------------------------
    Copyright (c) Charles Carley.

  This software is provided 'as-is', without any express or implied
  warranty. In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
-------------------------------------------------------------------------------
*/
#include "Xml/SpecialChar.h"

namespace Rt2::Xml
{

    struct LookupTable
    {
        const char* code;
        int         n;
    };

    // -----------
    // 1 2 3 4 5
    // -----------
    // l t ;
    // g t ;
    // a m p ;
    // q u o t ;
    // a p o s ;
    // -----------
    constexpr LookupTable Chars[] = {
        {"lgaq", 4},
        {"tmup", 4},
        { ";po", 3},
        { ";ts", 3},
        {   ";", 1},
    };

    union ComputedLookup
    {
        constexpr ComputedLookup() = default;
        constexpr ComputedLookup(const char a, const char b, const char c, const char d, const char e)
        {
            code[0] = a;
            code[1] = b;
            code[2] = c;
            code[3] = d;
            code[4] = e;
            code[5] = 0xFF;
            code[6] = 0xFF;
            code[7] = 0xFF;
        }
        uint8_t  code[8]{0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF};
        uint64_t index;
    };

    constexpr ComputedLookup Lt   = {'l', 't', ';', 0, 0};
    constexpr ComputedLookup Gt   = {'g', 't', ';', 0, 0};
    constexpr ComputedLookup Amp  = {'a', 'm', 'p', ';', 0};
    constexpr ComputedLookup Quot = {'q', 'u', 'o', 't', ';'};
    constexpr ComputedLookup APos = {'a', 'p', 'o', 's', ';'};

    bool contains(const int ch, const char* code, const int n)
    {
        bool res = false;
        for (int i = 0; i < n && !res; ++i)
            res = code[i] == ch;
        return res;
    }

    char SpecialChar::check(const int in, IStream* stream)
    {
        if (in == '&')
        {
            int u = 0;

            ComputedLookup tested;
            for (const auto& [code, n] : Chars)
            {
                if (contains(stream->peek(), code, n))
                {
                    tested.code[u++] = (char)stream->get();
                    if (tested.index == Lt.index)
                        return '<';
                    if (tested.index == Gt.index)
                        return '>';
                    if (tested.index == Quot.index)
                        return '"';
                    if (tested.index == APos.index)
                        return '\'';
                    if (tested.index == Amp.index)
                        return '&';
                }
                else
                    break;
            }
            for (int i = u - 1; i >= 0; i--)
                stream->putback((char)tested.code[i]);
            return (char)in;
        }
        return (char)in;
    }

}  // namespace Rt2::Xml
