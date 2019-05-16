using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using day32_05._16_ClassLibrary;    // namespace 
using DemoLib;

/*
 * DemoLib.dll 빌드 후
 * [Visual Studio 폴더] -> [Developer Command prompt for VS 2019] (관리자 권한 실행)
 * -> cd C:\Users\bit\Source\Repos\BITAcademy\NET Framework\DemoLib\bin\Debug
 * -> gacutil /i DemoLib.dll
 * 
 * C:\Windows\Microsoft.NET\assembly\GAC_MSIL\DemoLib\v4.0_1.0.0.0__daac41f1b5545a0b
 * -> DemoLib.dll 추가됨
 * 
 * C:\Users\bit\Source\Repos\BITAcademy\NET Framework\day32_05.16_ConsoleApp\bin\Debug
 * -> DemoLib.dll 삭제해도 exe 파일이 제대로 실행됨.
 **/
namespace day32_05._16_ConsoleApp
{
    class Program
    {
        static void Main(string[] args)
        {
            //Member member = new Member("홍길동", "대한민국");
            //Console.WriteLine("이름:{0} 주소:{1}", member.Name, member.Addr);

            DemoClass dc = new DemoClass();
            dc.Foo();

            Console.ReadLine();
        }
    }
}
