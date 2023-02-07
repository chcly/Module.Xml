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
#include "TestDirectory.h"
#include "Utils/FileSystem.h"
#include "Xml/File.h"
#include "gtest/gtest.h"

using namespace Rt2;
using namespace Xml;

GTEST_TEST(Xml, Parse_001)
{
    StringStream ss;
    ss << "<a x='1'>hello world</a>";

    File parser;
    parser.read(ss);

    Node* root = parser.tree();
    EXPECT_NE(nullptr, root);

    Node* a = root->firstChild();
    EXPECT_NE(nullptr, a);
    EXPECT_EQ(a->name(), "a");
    EXPECT_TRUE(a->hasAttributes());
    EXPECT_EQ(a->attribute("x"), "1");
    EXPECT_EQ(a->text(), "hello world");
}

void LogNodeParseStructure(OStream& out, Node* node, int& depth)
{
    for (int i = 0; i < depth; ++i)
        out << '-';
    out << node->name() << std::endl;

    for (size_t i = 0; i < node->size(); ++i)
    {
        Node* ch = node->at(i);

        ++depth;
        LogNodeParseStructure(out, ch, depth);
        --depth;
    }
}

GTEST_TEST(Xml, NodeParseStructure)
{
    StringStream ss;
    ss << "<root><foo>A<b>B</b>C</foo></root>";

    File parser;
    parser.read(ss);

    Node* root = parser.tree();
    EXPECT_NE(nullptr, root);

    OutputStringStream oss;

    int d = 1;
    LogNodeParseStructure(oss, root->getFirstChild("root"), d);

    StringStream expected;
    expected << "-root" << std::endl;
    expected << "--foo" << std::endl;
    expected << "---_text_node" << std::endl;
    expected << "---b" << std::endl;
    expected << "----_text_node" << std::endl;
    expected << "---_text_node" << std::endl;
    EXPECT_EQ(expected.str(), oss.str());
}
