using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace day33_05._18
{
    /// LINQ (select new)
    //public class Profile
    //{
    //    public string Name { get; set; }
    //    public int Height { get; set; }
    //}
    /// LINQ (collection 안의 collection)
    //public class Class
    //{
    //    public string Name { get; set; }
    //    public int[] Score { get; set; }
    //}

        /// LINQ
        public class Person
    {
        public string Sex { get; set; }
        public string Name { get; set; }
    }

    class MainApp
    {
        /// <summary>
        /// LINQ (Language INtegrated Query)
        /// </summary>
        /// <param name="args"></param>
        /* 
         *           범위 변수	        원본 데이터
         * - from [qeury variable] in [data source] 절부터 시작
         * **data source: (IEnumerblae<T> 인터페이스를 상속하는 형식)	(C#에서 제공하는 클래스 모두 사용 가능)
         * 
         * - where [조건]
         * - orderby [정렬기준] [ascending | descending]
         * - select [추출 데이터]
         */
         

        static void Main(string[] args)
        {
            /// LINQ
            //int[] numbers = { 9, 2, 6, 4, 5, 3, 7, 8, 1, 10 };

            //var result = from n in numbers
            //             where n % 2 == 0
            //             orderby n
            //             select n;

            //foreach (int n in result)
            //    Console.WriteLine($"짝수 : {n}");

            /// LINQ (select new)
            //Profile[] arrProfile = {new Profile() { Name="김철수", Height=186}
            //                        , new Profile() { Name="바끄네", Height=158}
            //                        , new Profile() { Name="채순시", Height=172}
            //                        , new Profile() { Name="김기출", Height=178}
            //                        , new Profile() { Name="유병우", Height=171}
            //};
            //var profiles = from profile in arrProfile
            //               where profile.Height < 175
            //               orderby profile.Height
            //               select new   // select에 기존의 항목을 이용하지 않고 직접 새로 넣을 수 있다.
            //               {
            //                   Name = profile.Name,
            //                   InchHeight = profile.Height * 0.393
            //               };

            //foreach (var profile in profiles)
            //    Console.WriteLine($"{profile.Name}, {profile.InchHeight}");

            /// LINQ (collection 안의 collection)
            //Class[] arrClass =
            //{
            //    new Class() {Name="장미반", Score=new int[] {99,80,70,24}}
            //    , new Class() {Name="백합반", Score=new int[] {60,45,87,72}}
            //    , new Class() {Name="개나리반", Score=new int[] {92,30,85,94}}
            //    , new Class() {Name="갈대반", Score=new int[] {90,88,0,17}}
            //};

            //// System.Linq.Enumerable.WhereSelectEnumberableIterator<>
            //var classes = from c in arrClass
            //              from s in c.Score
            //              where s < 60
            //              orderby s
            //              select new { c.Name, Lowest = s };
            //foreach (var c in classes)
            //    Console.WriteLine($"낙제: {c.Name} ({c.Lowest})");

            /// LINQ ()
            Person[] peopleArr =
            {
                new Person() {Sex = "여자", Name="성나정"},
                new Person() {Sex = "남자", Name="쓰레기"},
                new Person() {Sex = "여자", Name="조윤진"},
                new Person() {Sex = "남자", Name="삼천포"}
            };

            var group = from person in peopleArr
                        group person by person.Sex == "남자" into data
                        select new { SexCheck = data.Key, People = data };

            foreach(var element in group)
            {
                if(element.SexCheck)
                {
                    Console.WriteLine("<남자리스트>");
                    foreach (var person in element.People)
                        Console.WriteLine($"이름: {person.Name}");
                }
                else
                {
                    Console.WriteLine("<여자리스트>");
                    foreach (var person in element.People)
                        Console.WriteLine($"이름: {person.Name}");
                }
            }
        }
    }
}
