using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace day32_05._16_ClassLibrary
{
    public class Member // 다른 어셈블리에서 접근 가능
    {
        MemberInfo mi = null;
        
        public string Name // 다른 어셈블리에서 접근 가능
        {
            get
            {
                return mi.Name;
            }
        }
        public string Addr // 다른 어셈블리에서 접근 가능
        {
            get
            {
                return mi.Addr;
            }
        }
        public Member(string name, string addr) // 다른 어셈블리에서 접근 가능
        {
            mi = new MemberInfo(name, addr);
        }
        public override string ToString()   // 다른 어셈블리에서 접근 가능
        {
            return mi.ToString();
        }
    }
}
