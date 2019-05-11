// 자주 쓰이는 namespace가 자동으로 import됨. 사용하면 흰색, 아니면 회색으로 색이 바뀜.
using System;
using static System.Console;    // system namespace 안의 console 클래스의 static 메소드를 바로 쓰겠다.
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Globalization;
using System.Collections;

namespace Net_Framework
{
    //class Product
    //{
    //    private int price = 100;

    //    public ref int GetPrice()
    //    {
    //        return ref price;
    //    }

    //    public void PrintPrice()
    //    {
    //        WriteLine($"Price : {price}");
    //    }
    //}
    class MainApp
    {

        /* enum */
        //enum ColorCode { RED=10, BLUE, GREEN, ORANGE=100 };

        /* 참조 변수로 swap */
        //static void Swap(ref int a, ref int b)
        //{
        //    int temp = b;
        //    b = a;
        //    a = temp;
        //}


        static void Divide
            (int a, int b, out int quotient, out int remainder)
        {
            quotient = a / b;
            remainder = a % b;
        }

        static int Func()
        {
            int retval=0;

            return retval;
        }
        static void Main(string[] args)
        {
            
            /* 1 */
            ////Console.WriteLine("Hellow World!");
            //WriteLine("Hellow World!"); // system namespace 안의 console 클래스의 static 메소드 사용

            /* Console WriteLine 보관 */
            //sbyte a = -10;
            //byte b = 40;

            //Console.WriteLine($"a={a}, b={b}"); // 보관

            //short c = -30000;
            //ushort d = 60000;

            //Console.WriteLine($"c={c}, d={d}"); // 보관
            //Console.WriteLine("c={0}, d={1}", c, d); // 보관  // {0} = c, {1} = d

            //int e = -10_000_000;    // 컴파일 시 _ 무시
            //uint f = 300_000_000;

            //Console.WriteLine($"e={e}, f={f}"); // 보관

            //long g = -500_000_000_000;
            //ulong h = 2_000_000_000_000_000_000;

            //Console.WriteLine($"g={g}, h={h}"); // 보관

            /* float, double, decimal */
            //// decimal 
            //float a = 3.1415_9265_3589_7932_3846_2643_3832_79f;
            //double b = 3.1415_9265_3589_7932_3846_2643_3832_79;
            //decimal c = 3.1415_9265_3589_7932_3846_2643_3832_79m;

            //Console.WriteLine(a);
            //Console.WriteLine(b);
            //Console.WriteLine(c);

            /* String */
            //string a = "독도는 우리땅";
            //string b = "대마도도 우리땅";

            //Console.WriteLine(a);
            //Console.WriteLine(b);

            /* object : 어떤 타입이든 다 받음 */
            //object a = 123;
            //object b = 3.14159m;
            //object c = true;
            //object d = "문자열";

            //Console.WriteLine(a);
            //Console.WriteLine(b);
            //Console.WriteLine(c);
            //Console.WriteLine(d);

            /* ToString(), Parse() */
            //int a = 123;
            //string b = a.ToString();
            //Console.WriteLine(b);

            //float c = 3.14f;
            //string d = c.ToString();
            //Console.WriteLine(d);

            //string e = "123456";
            //int f = int.Parse(e);
            //Console.WriteLine(f);

            //string g = "1.2345";
            //float h = float.Parse(g);
            //Console.WriteLine(h);

            /* 상수 */
            //const int MAX_INT = 2147483647;
            //const int MIN_INT = -2147483648;

            //Console.WriteLine(MAX_INT);
            //Console.WriteLine(MIN_INT);

            /* enum */
            //Console.WriteLine((int)ColorCode.RED);
            //Console.WriteLine((int)ColorCode.BLUE);
            //Console.WriteLine(ColorCode.GREEN);
            //Console.WriteLine(ColorCode.ORANGE);

            //ColorCode cCode = ColorCode.RED;
            //Console.WriteLine(cCode == ColorCode.BLUE); // FALSE
            //Console.WriteLine(cCode == ColorCode.RED);  // TRUE


            //Console.WriteLine((int)ColorCode.RED);
            //Console.WriteLine((int)ColorCode.BLUE);
            //Console.WriteLine((int)ColorCode.GREEN);
            //Console.WriteLine((int)ColorCode.ORANGE);

            /* nullable 연산자 */
            //int? a = null;  
            //// 참조타입은 null값을 가질 수 있지만, 기본타입은 가질 수 없다.
            //// 기본타입 + ? (nullable 연산자) => 기본타입이 null값을 가질 수 있게
            //Console.WriteLine(a.HasValue);
            //Console.WriteLine(a != null);

            //a = 3;
            //Console.WriteLine(a.HasValue);
            //Console.WriteLine(a != null);
            //Console.WriteLine(a.Value); // 값을 가져올 땐 a.Value로 가져와야 함.
            //Console.WriteLine(a);

            /* var 타입
             * 선언과 동시에 초기화 필요
             * 로컬 변수로만 사용 가능
             */
            //var a = 20;
            //Console.WriteLine("Type: {0}, Value: {1}", a.GetType(), a);

            //var b = 3.141592;
            //Console.WriteLine("Type: {0}, Value: {1}", b.GetType(), b);

            //var c = "Hello World";
            //Console.WriteLine("Type: {0}, Value: {1}", c.GetType(), c);

            //var d = new int[] { 10, 20, 30 };
            //Console.WriteLine("Type: {0}, Value: ", d.GetType());

            //foreach (var e in d)
            //    Console.Write("{0} ", e);

            //Console.WriteLine();

            /* string method */
            //string str = "This is string search sample";
            //WriteLine(str);
            //WriteLine();

            //WriteLine("Index of 'search' : {0}", str.IndexOf("search"));        // 15
            //WriteLine("Index of 'h' : {0}", str.IndexOf("h"));                  // 1

            //WriteLine("StartsWith 'This' : {0}", str.StartsWith("This"));       // True
            //WriteLine("StartsWith 'string' : {0}", str.StartsWith("string"));   // False

            //WriteLine("EndsWith 'This' : {0}", str.EndsWith("This"));           // False
            //WriteLine("EndsWith 'sample' : {0}", str.EndsWith("sample"));       // False

            //WriteLine("Contains 'search' : {0}", str.Contains("search"));       // True
            //WriteLine("Contains 'school' : {0}", str.Contains("school"));       // False

            //WriteLine("Replace 'sample' with 'example' : {0}", str.Replace("sample", "example"));
            //WriteLine("Replace 'sample' with 'example' : {0}", str.Replace("school", "example"));   // 없는 단어로 replace하면 변화없이 리턴


            //WriteLine("ToLower() : {0}", "Hello World".ToLower());
            //WriteLine("ToUpper() : {0}", "Hello World".ToUpper());

            //WriteLine("Insert() : {0}", "Hello World".Insert(6, "Wonderful "));
            //WriteLine("Remove() : {0}", "Hello Wonderful World".Remove(6, 10)); // 6번째 값부터 10개 삭제

            //WriteLine("Trim() : {0}", "I am Tom".Trim());   // 선행, 후행 공백 삭제
            //WriteLine("TrimStart() : {0}", "Hello World".TrimStart());
            //WriteLine("TrimEnd() : {0}", "Hello World".TrimEnd());

            //string str = "Welcome to the C# world!";

            //WriteLine(str.Substring(15, 2));
            //WriteLine(str.Substring(8));
            //WriteLine();

            //string[] arr =
            //    str.Split(new string[] { " " }, StringSplitOptions.RemoveEmptyEntries);

            //WriteLine("Word count : {0}", arr.Length);

            //foreach (string element in arr)
            //    WriteLine("{0}", element);

            /* 출력 형태 변경 */
            // -: 왼쪽정렬, +: 오른쪽정렬
            // -10: 10칸 잡아서 왼쪽 정렬
            //string fmt = "{0,-10}|{1,-5}|{2,20}";

            //WriteLine(fmt, "Type", "Size", "Explain");
            //WriteLine(fmt, "byte", "1", "byte 타입");
            //WriteLine(fmt, "short", "2", "short 타입");
            //WriteLine(fmt, "int", "4", "int 타입");
            //WriteLine(fmt, "long", "8", "long 타입");

            /* 숫자 출력 형태 */
            //WriteLine("10진수: {0:D}", 123);
            //WriteLine("10진수: {0:D5}", 123); // C의 %5d와 같은 형식

            //WriteLine("16진수: {0:X}", 0xFF1234);
            //WriteLine("16진수: {0:X8}", 0xFF1234);

            //WriteLine("숫자: {0:N}", 123456);
            //WriteLine("숫자: {0:N}", 123456789123456);
            //WriteLine("숫자: {0:N0}",123456);

            //WriteLine("고정소수점: {0:F}", 123.456);
            //WriteLine("고정소수점: {0:F5}",123.456);

            //WriteLine("공학: {0:E}",123.456789);

            /* 날짜 출력 */
            //DateTime dt = DateTime.Now;

            //WriteLine("12시간 형식: {0:yyyy-MM-dd tt hh:mm:ss (ddd)}", dt);
            //WriteLine("24시간 형식: {0:yyyy-MM-dd HH:mm:ss (dddd)}", dt);

            //CultureInfo ciKR = new CultureInfo("ko-KR");
            //WriteLine();
            //WriteLine(dt.ToString("yyyy-MM-dd tt hh:mm:ss (ddd)", ciKR));
            //WriteLine(dt.ToString("yyyy-MM-dd HH:mm:ss (dddd)", ciKR));
            //WriteLine(dt.ToString(ciKR));

            //CultureInfo ciUS = new CultureInfo("en-US");
            //WriteLine();
            //WriteLine(dt.ToString("yyyy-MM-dd tt hh:mm:ss (ddd)", ciUS));
            //WriteLine(dt.ToString("yyyy-MM-dd HH:mm:ss (dddd)", ciUS));
            //WriteLine(dt.ToString(ciUS));

            /* 출력형식 */
            //string name = "홍길동";
            //int age = 25;
            //WriteLine($"{name,-10}, {age:D3}");

            //name = "김유신";
            //age = 30;
            //WriteLine($"{name}, {age,-10:D3}");

            //name = "박문수";
            //age = 15;
            //WriteLine($"{name}, {(age>20? "성인" : "미성년자")}");

            /* ArrayList */
            //ArrayList a = null;
            //a?.Add("C++");  // null이 아니면 ? 뒤를 실행. null일 경우 a를 리턴. (아무것도 하지 않음) 그래서 아래 전부 null을 리턴
            //a?.Add("C#");
            //WriteLine($"Count : {a?.Count}");
            //WriteLine($"{a?[0]}");
            //WriteLine($"{a?[1]}");

            //a = new ArrayList();
            //a?.Add("C++");
            //a?.Add("C#");
            //WriteLine($"Count : {a?.Count}");
            //WriteLine($"{a?[0]}");
            //WriteLine($"{a?[1]}");

            /* null 병합 연산자 */
            //int? num = null;
            //WriteLine($"{num ?? 0}");   // num이 null이 아니면 왼쪽(num), null이면 오른쪽(기본값(0))

            //num = 10;
            //WriteLine($"{num ?? 0}");

            //string str = null;
            //WriteLine($"{str ?? "Default"}");

            //str = "I study C#";
            //WriteLine($"{str ?? "Default"}");

            /* switch string */
            //Write("요일을 입력하세요(월, 화, 수, 목, 금, 토, 일): ");
            //string day = ReadLine();

            //switch (day)
            //{
            //    case "일":
            //        WriteLine("Sunday");
            //        break;
            //    case "월":
            //        WriteLine("Monday");
            //        break;
            //    case "화":
            //        WriteLine("Tuesday");
            //        break;
            //    case "수":
            //        WriteLine("Wednesday");
            //        break;
            //    case "목":
            //        WriteLine("Thursday");
            //        break;
            //    case "금":
            //        WriteLine("Friday");
            //        break;
            //    case "토":
            //        WriteLine("Saturday");
            //        break;
            //    default:
            //        WriteLine("입력하신 글자는 요일이 아닙니다.");
            //        break;

            //}

            /* switch case문 */
            //object obj = null;

            //string str = ReadLine();
            //// .Parse: 타입 변환할 수 없는 값일 경우 exception이 발생해서 프로그램이 종료됨.
            //// .TryParse: 변환된 수를 int_num이 받음. 프로그램이 비정상 종료되는 것을 막을 수 있다.
            //if (int.TryParse(str, out int int_num))
            //    obj = int_num;
            //else if (float.TryParse(str, out float float_num))
            //    obj = float_num;
            //else
            //    obj = str;

            //switch(obj)
            //{
            //    case int i:
            //        WriteLine($"{i}는 int 형식입니다.");
            //        break;
            //    case float f:
            //        WriteLine($"{f}는 float 형식입니다.");
            //        break;
            //    default:
            //        WriteLine($"{obj}는 obj 형식입니다.");
            //        break;
            //}

            /* foreach */
            //int[] arr = new int[] { 0, 1, 2, 3, 4 };

            //foreach (int i in arr)
            //    WriteLine(i);

            /*
             * C#에서 기본적으로 포인터가 제공되지 않는다.
             * Person man1; --> c++ 로컬에 man1 객체 생성
             *              --> C# 로컬 스택 영역에 man1. Person이란 객체를 받을 수 있는 레퍼런스 변수 (C++에서 포인터 변수와 같은 의미)
             * C# 객체는 무조건 Heap에만 생긴다. 즉 무조건 new로만 만들어야 한다.
             * 로컬 스택에 객체 생성할 수 없음.
             * C# 객체로 만들지 않으려면 Person man1 = null; 로 초기화 필요.
             * 
             * int[] arr;
             * --> 로컬 스택에 arr변수 만들고 Heap 영역에 int형 배열 생성.
             *     로컬 스택 arr변수의 주소값이 Heap 영역에 생성된 배열의 이름이 된다. (포인터 개념)
             *     
             *     
             *  static 영역
             *      프로그램 코드, static으로 선언됨. (static으로 선언되면 class 이름으로 직접 접근 가능)
             *      main이 static으로 선언되어 있어서 CLR 접근 가능.
             *      
             *   stack 영역
             *      기본 타입 변수(int, float 등등)
             *      
             *   Heap 영역
             *      객체
             *      
             */

            //int result = Calculator.Plus(2, 5);
            //WriteLine(result);

            //result = Calculator.Minus(10, 4);
            //WriteLine(result);

            /* 참조변수로 swap 
             * C#은 C++의 포인터 개념은 버렸지만, 레퍼런스 개념은 계속 갖고 있음.
             */
            //int x = 3;
            //int y = 5;

            //WriteLine($"x:{x}, y:{y}");

            //Swap(ref x, ref y);

            //WriteLine($"x:{x}, y:{y}");

            /* 참조 매개 변수 */
            //Product carrot = new Product();
            //ref int ref_price = ref carrot.GetPrice();
            //int normal_price = carrot.GetPrice();

            //carrot.PrintPrice();
            //WriteLine($"Ref Price: {ref_price}");
            //WriteLine($"Normal Price: {normal_price}");


            //ref_price = 200;
            //carrot.PrintPrice();
            //WriteLine($"Ref Price: {ref_price}");
            //WriteLine($"Normal Price: {normal_price}");

            /* out */
            int a = 20;
            int b = 3;
            int c;
            int d;

            Divide(a, b, out c, out d); // out int c, out int d 가능

            WriteLine($"a:{a},  b:{b},  a/b:{c},  a%b:{d}");

        }
    }
}
