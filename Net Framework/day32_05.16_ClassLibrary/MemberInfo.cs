using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace day32_05._16_ClassLibrary
{
    class MemberInfo
    {
        internal string Name
        {
            get;
            private set;
        }

        internal string Addr
        {
            get;
            private set;
        }

        internal MemberInfo(string name, string addr)
        {
            Name = name;
            Addr = addr;
        }

        public override string ToString()
        {
            return Name;
        }
    }
}
