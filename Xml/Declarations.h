#pragma once
#include "Utils/ScopePtr.h"

namespace Rt2::Xml
{
    class Node;
    class Attribute;
    class File;

}  // namespace Rt2::Xml

namespace Rt2
{
    using XmlNode = Xml::Node;
    using XmlFile = Xml::File;


    using XmlPtr = ScopePtr<Xml::Node*>;

}  // namespace Rt2
