using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace day31_05._15
{
    /// <summary>
    ///  Exception class (InvalidArgumentException)
    /// </summary>
    //class InvalidArgumentException : Exception
    //{
    //    public InvalidArgumentException() { }
    //    public InvalidArgumentException(string message) : base(message) { }
    //    // property
    //    public object Argument
    //    {
    //        get; set;
    //    }
    //    public string Range
    //    {
    //        get; set;
    //    }
    //}

    /// Exception class (FilterableException)
    //class FilterableException : Exception
    //{
    //    public int ErrorNo
    //    { get; set; }
    //}

    /// delegate (default로 internal). (int a, int b) 매개변수를 받는 메소드를 대신할 수 있는 MyDelegate
    //delegate int MyDelegate(int a, int b);

    //class Calculator
    //{
    //    public int Plus(int a, int b)
    //    {
    //        return a + b;
    //    }
    //    public int Minus(int a, int b)
    //    {
    //        return a - b;
    //    }
    //}

    /// delegate (OnlineShopping)
    //delegate void OnlineShopping(string location);

    /// delegate (Eventhandler)
    //delegate void Notify(string message);
    //class Notifier
    //{
    //    public Notify EventOccured;
    //}
    //class EventListener
    //{
    //    private string name;
    //    public EventListener(string name)
    //    {
    //        this.name = name;
    //    }

    //    public void SomethingHappened(string message)
    //    {
    //        Console.WriteLine($"{name}.SomethingHappened : { message}");
    //    }
    //}
    /// delegate (Calculate)
    //delegate int Calculate(int a, int b);

    /// delegate event
    //delegate void EventHandler(string message);

    //class MyNotifier
    //{
    //    public event EventHandler DoAlarm;
    //    public void Get369(int num)
    //    {
    //        int temp = num % 10;
    //        if(temp != 0 && temp % 3 == 0)
    //        {
    //            DoAlarm(String.Format("{0} : 짝!", num));
    //        }
    //    }
    //}


    /// delegate concatenate
    //delegate string Concatenate(string[] args);


    /// MyList
    /* IEnumerator (총 3가지 메소드)
     *  boolean MoveNext(): 다음 요소로 이동 (성공시 true)
     *  void Reset(): 첫 번째 위치 앞으로 이동
     *  Object Current{get;} : property. 컬렉션의 현재 요소 반환
     * */
    class MyList : IEnumerable, IEnumerator  // IEnumerable을 상속할 경우 클래스 내부에 GetEnumerator 메소드를 만들어야 한다.
    {
        private int[] array;
        private int position = -1;
        public MyList()
        {
            array = new int[3];
        }
        public int this[int index]  // main에서 list[i] 형식으로 쓰기 위해 this[int index]로 정의
        {
            get
            {
                return array[index];
            }
            set
            {
                if (index >= array.Length)
                {
                    Array.Resize<int>(ref array, index + 1);
                    Console.WriteLine($"Array Resized: {array.Length}");
                }
                array[index] = value;
            }
        }
        public int Length
        {
            get { return array.Length; }
        }


        // IEnumerator 멤버
        public object Current
        {
            get
            {
                return array[position];
            }
        }
        // IEnumerator 멤버
        public void Reset()
        {
            position = -1;
        }
        // IEnumerator 멤버
        public bool MoveNext()
        {
            if(position == array.Length -1)
            {
                Reset();
                return false;
            }
            position++;
            return (position < array.Length);
        }

        public IEnumerator GetEnumerator()
        {
            for (int i = 0; i < array.Length; i++)
                yield return array[i];
        }
    }

    /// Enumerator
    //class MyEnumerator
    //{
    //    private int[] numbers = { 1, 2, 3, 4 };

    //    // 한 번 실행해주고 멈춤
    //    public IEnumerator GetEnumerator()
    //    {
    //        yield return numbers[0];
    //        yield return numbers[1];
    //        yield return numbers[2];
    //        yield return numbers[3];
    //    }
    //}
    /// <summary>
    /// 
    /// </summary>
    class MainApp
    {
        /// <summary>
        /// try catch function
        /// </summary>
        /// <param name="arg"></param>
        //static void SimpleFunc(int arg)
        //{
        //    if (arg <= 10)
        //        Console.WriteLine($"arg : {arg}");
        //    else
        //        throw new Exception("인자값이 10보다 큽니다.");
        //}

        /// try catch finally
        //static int Divide(int divisor, int dividend)
        //{
        //    try
        //    {
        //        Console.WriteLine("Divide() 시작");
        //        return divisor / dividend;
        //    }
        //    catch(DivideByZeroException e)
        //    {
        //        Console.WriteLine("Divide() 예외발생");
        //        throw e;
        //    }
        //    finally
        //    {
        //        Console.WriteLine("Divide() 종료");
        //    }
        //}

        /// Exception class (InvalidArgumentException)
        //static uint MergeARGB(uint alpha, uint red, uint green, uint blue)
        //{
        //    uint[] args = new uint[] { alpha, red, green, blue };

        //    foreach (uint arg in args)
        //    {
        //        if (arg > 255)
        //            throw new InvalidArgumentException()
        //            {
        //                Argument = arg,
        //                Range = "0~255"
        //            };
        //    }
        //    return (alpha << 24 & 0xFF000000) | (red << 16 & 0x00FF0000)
        //        | (green << 8 & 0x0000FF00) | (blue & 0x000000FF);
        //}

        /// delegate (Compare, bubble sort)
        /// class 외부에 선언하면 namespace 안에 있는 class 전체가 사용 가능
        ///// class 내부에 선언하면 해당 class에서만 사용 가능
        //delegate int Compare(int a, int b);

        //static int AscendCompare(int a, int b)
        //{
        //    if (a > b)
        //        return 1;
        //    else if (a == b)
        //        return 0;
        //    else
        //        return -1;
        //}

        //static int DescendCompare(int a, int b)
        //{
        //    if (a < b)
        //        return 1;
        //    else if (a == b)
        //        return 0;
        //    else
        //        return -1;
        //}
        //static void BubbleSort(int[] dateSet, Compare comparer)
        //{
        //    int i = 0;
        //    int j = 0;
        //    int temp = 0;
        //    for (i = 0; i < dateSet.Length; i++)
        //    {
        //        for (j = 0; j < dateSet.Length - (i + 1); j++)
        //        {
        //            if (comparer(dateSet[j], dateSet[j + 1]) > 0)
        //            {
        //                temp = dateSet[j + 1];
        //                dateSet[j + 1] = dateSet[j];
        //                dateSet[j] = temp;
        //            }
        //        }
        //    }
        //}

        /// delegate (Compare, bubble sort generic)
        //delegate int Compare<T>(T a, T b);

        ///* 내 코드 */
        ////    static int AscendCompare<T>(T a, T b)
        ////{

        ////    if (Comparer<T>.Default.Compare(a, b) > 0)
        ////        return 1;
        ////    else if (Comparer<T>.Default.Compare(a, b) == 0)
        ////        return 0;
        ////    else
        ////        return -1;
        ////}

        ////static int DescendCompare<T>(T a, T b)
        ////{
        ////    if (Comparer<T>.Default.Compare(a, b) < 0)
        ////        return 1;
        ////    else if (Comparer<T>.Default.Compare(a, b) == 0)
        ////        return 0;
        ////    else
        ////        return -1;
        ////}
        ///* IComparable 인터페이스 상속 */
        //static int AscendCompare<T>(T a, T b) where T : IComparable<T>
        //{
        //    return a.CompareTo(b);
        //}

        //static int DescendCompare<T>(T a, T b) where T : IComparable<T>
        //{
        //    return a.CompareTo(b) * -1;
        //}
        //static void BubbleSort<T>(T[] dateSet, Compare<T> comparer)
        //{
        //    int i = 0;
        //    int j = 0;
        //    T temp;
        //    for (i = 0; i < dateSet.Length; i++)
        //    {
        //        for (j = 0; j < dateSet.Length - (i + 1); j++)
        //        {
        //            if (comparer(dateSet[j], dateSet[j + 1]) > 0)
        //            {
        //                temp = dateSet[j + 1];
        //                dateSet[j + 1] = dateSet[j];
        //                dateSet[j] = temp;
        //            }
        //        }
        //    }
        //}

        /// delegate (OnlineShopping)
        //static void OrderGoods(string location)
        //{
        //    Console.WriteLine($"장바구니내 물건을 {location}으로 가져다 주세요!");
        //}
        //static void SpecialOrder(string location)
        //{
        //    Console.WriteLine($"{location}에 사람이 없으면 문앞에 두시고 문자주세요!");
        //}

            /// delegate event
        //    static public void MyHandler(string message)
        //{
        //    Console.WriteLine(message);
        //}
        static void Main(string[] args)
        {
            /// 형식 매개변수 제약
            /*
             * 1. where T : struct
             *  => T는 값 형식
             *  
             * static void CopyArray<T>(T[] source, T[] target) where T : struct
             * CopyArray<int>(source, target);
             * 
             * 
             * 2. where T : class
             *  => T는 참조 형식
             *  
             * static void CopyArray<T>(T[] source, T[] target) where T : class
             * CopyArray<string>(source, target);
             *              
             *              
             * 3. where T : new()
             *  => T는 매개변수가 없는 생성자가 있어야 함
             *  
             * public static T CreateInstance<T>() where T : new()
             * {
             *      return new T();
             * }
             * 
             * 
             * 4. where T : 베이스 클래스 이름
             *  => T는 해당 베이스 클래스를 상속한 클래스
             *  
             * static void CopyArray<T>(T[] source, T[] target) wherer T : MyList
             * class ChildList : MyList
             * CopyArray<ChildList>(source, target);
             * 
             * 
             * 5. where T : 인터페이스 이름
             *  => T는 해당 인터페이스를 구현해야 함
             *  
             * static void CopyArray<T>(T[] source, T[] target) where T : ILogger
             * class ConsoleLogger : ILogger
             * CopyArray<ConsoleLogger>(source, target);
             * 
             * 
             * 6. where T : U       // U: base class (4번에서는 MyList로 고정된 형태)
             *  => T는 U를 상속한 클래스여야 함 (4번과 유사)
             *  
             * class BaseArray<U>
             * {
             *      public U[] Array
             *      { get;set; }
             *      
             *      public BaseArray(int size)
             *      { Array = new U[size]; }
             *      
             *      public void CopyArray<T> (T[] source) where T : U
             *      { source.CopyTo(Array, 0); }
             *  }
             *  
             *  CopyArray<T, U>
             *  <T,T>
             */

            /// Array Generic
            //List<int> list = new List<int>();
            //for (int i = 0; i < 5; i++)
            //    list.Add(i);

            //foreach (int i in list)
            //    Console.Write($"{i} ");
            //Console.WriteLine();

            //list.RemoveAt(2);

            //foreach(int i in list)
            //    Console.Write($"{i} ");
            //Console.WriteLine();

            //list.Insert(2,2);

            //foreach(int i in list)
            //    Console.Write($"{i} ");
            //Console.WriteLine();


            /// Dictionary
            //Dictionary<string, int> dic = new Dictionary<string, int>();
            //dic["국어"] = 90;
            //dic["영어"] = 85;
            //dic["수학"] = 95;
            //dic["물리"] = 100;
            //dic["화학"] = 95;

            //foreach (KeyValuePair<string, int> item in dic)
            //    Console.WriteLine($"{item.Key} : {item.Value}");


            /// try, catch
            //int[] arr = { 1, 2, 3 };
            //try
            //{
            //    for (int i = 0; i < 5; i++)
            //        Console.WriteLine(arr[i]);
            //}
            //catch (IndexOutOfRangeException e)
            //{
            //    Console.WriteLine($"예외 발생 : {e.Message}");
            //}
            //Console.WriteLine("종료");

            /// try catch function
            //try
            //{
            //    SimpleFunc(5);
            //    SimpleFunc(12);
            //}
            //catch(Exception e)
            //{
            //    Console.WriteLine(e.Message);
            //}

            /// nullable, index
            //try
            //{
            //    int? a = null;
            //    int b = a ?? throw new ArgumentNullException();
            //}
            //catch(ArgumentNullException e)
            //{
            //    Console.WriteLine(e);
            //}

            //try
            //{
            //    int[] array = new[] { 1, 2, 3 };
            //    int index = 4;
            //    int value =
            //        array[index >= 0 && index < 3 ? index : throw new IndexOutOfRangeException()];
            //}
            //catch(IndexOutOfRangeException e)
            //{
            //    Console.WriteLine(e);
            //}

            /// try catch finally
            //try
            //{
            //    Console.Write("제수 입력 : ");
            //    String temp = Console.ReadLine();
            //    int divisor = Convert.ToInt32(temp);

            //    Console.Write("피제수 입력 : ");
            //    temp = Console.ReadLine();
            //    int dividend = int.Parse(temp);
            //    Console.WriteLine("{0}/{1} = {2}", divisor, dividend, Divide(divisor, dividend));
            //}
            //catch(FormatException e)
            //{
            //    Console.WriteLine("에러 : " + e.Message);
            //}
            //catch(DivideByZeroException e)
            //{
            //    Console.WriteLine("에러 : " + e.Message);
            //}
            //finally
            //{
            //    Console.WriteLine("프로그램 종료");
            //}


            ///  Exception class (InvalidArgumentException)
            //try
            //{
            //    Console.WriteLine("0x{0:X8}", MergeARGB(255, 100, 100, 100));
            //    Console.WriteLine("0x{0:X8}", MergeARGB(1, 165, 190, 125));
            //    Console.WriteLine("0x{0:X8}", MergeARGB(0, 255,255,260));
            //}
            //catch(InvalidArgumentException e)
            //{
            //    Console.WriteLine(e.Message);
            //    Console.WriteLine($"Argument: {e.Argument}, Range: {e.Range}");
            //}


            /// Exception class (FilterableException)
            /// when 키워드 
            //Console.Write("Enter number between 0~10: ");
            //string input = Console.ReadLine();
            //try
            //{
            //    int num = int.Parse(input);
            //    if (num < 0 || num > 10)
            //        throw new FilterableException() { ErrorNo = num };
            //    else
            //        Console.WriteLine($"Output : {num}");
            //}
            //catch(FilterableException e) when (e.ErrorNo < 0)
            //{
            //    Console.WriteLine("음수는 허용되지 않습니다.");
            //}
            //catch(FilterableException e) when (e.ErrorNo > 10)
            //{
            //    Console.WriteLine("10보다 큰 수는 허용되지 않습니다.");
            //}

            /// Delegate (MyDelegate)
            /* MyDelegate callback 생성. 
             * Calculator 메소드를 대신해줌.
             * 함수 포인터와 비슷한 느낌
             */
            //Calculator cal = new Calculator();
            //MyDelegate Callback;

            //Callback = new MyDelegate(cal.Plus);
            //Console.WriteLine(Callback(3, 4));

            //Callback = new MyDelegate(cal.Minus);
            //Console.WriteLine(Callback(8, 3));

            /// Delegate (Compare, bubble sort)
            //int[] array = { 3, 7, 4, 2, 9 };

            //Console.WriteLine("Ascending Sort!");
            //BubbleSort(array, new Compare(AscendCompare));
            //for (int i = 0; i < array.Length; i++)
            //    Console.Write($"{array[i]}");
            //Console.WriteLine();

            //Console.WriteLine("Descending Sort!");
            //BubbleSort(array, new Compare(DescendCompare));
            //for (int i = 0; i < array.Length; i++)
            //    Console.Write($"{array[i]} ");
            //Console.WriteLine();

            /// Delegate (Compare, bubble sort (Generic))
            //int[] array = { 3, 7, 4, 2, 9 };

            //Console.WriteLine("Ascending Sort!");
            //BubbleSort<int>(array, new Compare<int>(AscendCompare));
            //for (int i = 0; i < array.Length; i++)
            //    Console.Write($"{array[i]}");
            //Console.WriteLine();

            //string[] array2 = { "abc", "def", "ghi", "jkl", "mno" };
            //Console.WriteLine("Descending Sort!");
            //BubbleSort<string>(array2, new Compare<string>(DescendCompare));
            //for (int i = 0; i < array.Length; i++)
            //    Console.Write($"{array2[i]} ");
            //Console.WriteLine();

            /// delegate (OnlineShopping)
            //OnlineShopping shopper =
            //    new OnlineShopping(OrderGoods) + new OnlineShopping(SpecialOrder);

            //shopper("우리집");

            /// delegate (Eventhandler)
            //Notifier notifier = new Notifier();
            //EventListener listener1 = new EventListener("Listener1");
            //EventListener listener2 = new EventListener("Listener2");
            //EventListener listener3 = new EventListener("Listener3");

            //notifier.EventOccured = listener1.SomethingHappened;
            //notifier.EventOccured += listener2.SomethingHappened;
            //notifier.EventOccured += listener3.SomethingHappened;
            //notifier.EventOccured("You've got mail.");
            //Console.WriteLine();

            //notifier.EventOccured -= listener2.SomethingHappened;
            //notifier.EventOccured("Download completed.");
            //Console.WriteLine();

            //Notify notify1 = new Notify(listener1.SomethingHappened);
            //Notify notify2= new Notify(listener2.SomethingHappened);
            //notifier.EventOccured = (Notify)Delegate.Combine(notify1, notify2);
            //notifier.EventOccured("Fire!");
            //Console.WriteLine();

            //notifier.EventOccured = (Notify)Delegate.Remove(notifier.EventOccured, notify2);
            //notifier.EventOccured("Game Over!!");

            /// delegate (Calculate) 익명 메소드
            //Calculate calc;
            //calc = delegate (int a, int b)
            //{
            //    return a + b;
            //};
            //Console.WriteLine("3 + 4 : {0}", calc(3, 4));

            /// delegate bubble sort
            //int[] array = { 3, 7, 4, 2, 9 };

            //Console.WriteLine("Ascending Sort!");
            //BubbleSort(array, delegate (int a, int b)
            //    {
            //        if (a > b)
            //            return 1;
            //        else if (a == b)
            //            return 0;
            //        else
            //            return -1;
            //    });
            //for (int i = 0; i < array.Length; i++)
            //    Console.Write($"{array[i]} ");
            //Console.WriteLine();

            //Console.WriteLine("Descending Sort!");
            //BubbleSort(array, delegate (int a, int b)
            //    {
            //        if (a < b)
            //            return 1;
            //        else if (a == b)
            //            return 0;
            //        else
            //            return -1;
            //    });
            //for (int i = 0; i < array.Length; i++)
            //    Console.Write($"{array[i]} ");
            //Console.WriteLine();

            /// delegate event
            //MyNotifier notifier = new MyNotifier();
            //notifier.DoAlarm += new EventHandler(MyHandler);    

            //for(int i=1; i<30; i++)
            //{
            //    notifier.Get369(i);
            //}
            // 외부에서 접근/호출 불가. 본인이 선언된 클래스 내에서만 호출 가능.
            //notifier.DoAlarm("이거는 안됨!");

            /// delegate (Calculate) 익명 메소드 rambda 식으로 변경
            //Calculate calc = (a, b) => a + b;
            //Console.WriteLine($"{3} + {4} : {calc(3, 4)}");

            //string[] strArr = {"Microsoft", "C#", "Language" };
            //Concatenate concat = (arr) =>
            //{
            //    string result = "";
            //    foreach (string s in arr)
            //        result += s;
            //    return result;
            //};
            //Console.WriteLine(concat(strArr));

            /// 람다
            //Func<int> func1 = () => 10;
            //Console.WriteLine($"func1() : {func1()}");

            //Func<int, int> func2 = (x) => x*2;
            //Console.WriteLine($"func2(4) : {func2(4)}");

            //Func<double,double,double> func3 = (x,y) => x/y;
            //Console.WriteLine($"func3(23,6) : {func3(23,6)}");

            /// Action은 리턴값이 없을 경우에만 사용 가능.
            //Action act1 = () => Console.WriteLine("Action()");
            //act1();

            //int result = 0;
            //Action<int> act2 = (x) => result = x * x;
            //act2(3);
            //Console.WriteLine($"result : {result}");

            //Action<double, double> act3 = (x, y) =>
            //{
            //    double d = x / y;
            //    Console.WriteLine($"Action<T1, T2>({x}, {y}) : {d}");
            //};
            //act3(10.0, 4.0);

            /// Enumerator
            //var obj = new MyEnumerator();
            //foreach (int i in obj)   // GetEnumerator() 메소드 호출
            //    Console.WriteLine(i);

            /// MyList
            MyList list = new MyList();
            for (int i = 0; i < 5; i++)
                list[i] = i;    // MyList에서 public int this[int index]로 정의한 이유

            for (int i = 0; i < list.Length; i++)
                Console.WriteLine(list[i]);

            foreach (int e in list)
                Console.WriteLine(e);

        }
    }
}

