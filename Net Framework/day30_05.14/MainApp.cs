using System;
using static System.Console;    // system namespace 안의 console 클래스의 static 메소드를 바로 쓰겠다.
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Collections;

/// <summary>
/// 
/// </summary>
namespace day30_05._14
{
    interface ILogger
    {
        void WriteLog(string message);  // 메소드 정의. definition은 없음. 추상 클래스의 abstract method와 유사
    }

    /// Interface
    /* interface
     * interface는 변수 맨 앞에 I를 붙여야 함. 접근 제한자 안 쓰면 default는 internal
     * C#은 다중 상속 지원하지 않음. 잘못 쓰면 모호한 코드가 되기 때문에 비선호. 따라서 interface를 만듬.
     * 클래스는 불가능하지만 interface는 다중 상속 가능. 추상메소드처럼 body가 없는 정의부분만 있기 때문에 상속보다는 구현한다는 표현을 쓴다.
     * 클래스: inheritance, 인터페이스: implement
     * 
     * 추상 클래스, 추상 메소드. (객체를 만들어 호출. 메소드 = 객체 사용법)
     * 사용방법은 정해져 있지만 구현방법은 정해지지 않았을 때 -> 추상 클래스, 추상 메소드 사용
     * 
     * ex)
     *    class Appliance
     *          PowerOn();
     *     TV: Appliance
     *     LaundaryMachine: Appliance
     *     
     *     class UserAppliance
     *          UserAppliance(Appliance appliance)  // 생성자 부분
     *          AppPowerOn()
     *          {
     *              appliance.PowerOn();    // 객체 사용법
     *          }
     *          
     *     --> 가전제품이라는 부모클래스를 상속받는 TV, 세탁기 클래스
     *          부모클래스의 PowerOn이라는 메소드를 상속받은 클래스에서 각각에게 맞게 구현해야하는데 이 때 추상 메소드를 사용한다.
     *          
     * 기본적으로 클래스는 생성자, 소멸자 루틴을 갖고 있다.
     * 클래스는 생성하는 데 오버헤드가 큼. (덩치가 크다)
     * 하지만 인터페이스는 오버헤드가 적다. 추상 메소드만 있는 추상 클래스를 쓸 바에 인터페이스를 선호함.
     * 
     * * 객체지향디자인 패턴 책
     *  1. GoF(Gang of Four)의 객체지향디자인 패턴
     *  2. Head First (자바 코드)
     * */
    //class ConsoleLogger : ILogger   // ILogger를 구현하는 ConsoleLogger 클래스. 반드시 ILogger의 메소드를 구현해야 함.
    //{
    //    public void WriteLog(string message)
    //    {
    //        WriteLine("{0} {1}", DateTime.Now.ToLocalTime(), message);
    //    }
    //}

    //class FileLogger : ILogger
    //{
    //    private StreamWriter writer;

    //    public FileLogger(string path)
    //    {
    //        writer = File.CreateText(path);
    //        writer.AutoFlush = true;    // 자동으로 버퍼 초기화
    //    }

    //    public void WriteLog(string message)
    //    {
    //        writer.WriteLine("{0} {1}", DateTime.Now.ToLocalTime(), message);
    //    }
    //}

    //class ClimateMonitor
    //{
    //    private ILogger logger;

    //    public ClimateMonitor(ILogger logger)
    //    {
    //        this.logger = logger;
    //    }

    //    public void start()
    //    {
    //        while(true)
    //        {
    //            Write("온도 입력: ");
    //            string temparature = ReadLine();
    //            if (temparature == "")
    //                break;
    //            logger.WriteLog("현재 온도 : " + temparature);
    //        }
    //    }
    //}

    //    /* Interface 2 */
    //interface IFormattableLogger : ILogger
    //{
    //    void WriteLog(string format, params object[] args);
    //}

    //class ConsoleLogger : IFormattableLogger
    //{
    //    public void WriteLog(string message)
    //    {
    //        WriteLine("{0} {1}", DateTime.Now.ToLocalTime(), message);
    //    }

    //    public void WriteLog(string format, params Object[] args)
    //    {
    //        string message = String.Format(format, args);
    //        Console.WriteLine("{0} {1}", DateTime.Now.ToLocalTime(), message);
    //    }
    //}

    /// Property
    /* property (get, set) */
    //class BirthdayInfo
    //{
    //    private string name;
    //    private DateTime birthday;

    //    public string Name // Property는 반드시 대문자로 시작
    //    {
    //        get
    //        {
    //            return name;
    //        }
    //        set
    //        {
    //            name = value;
    //        }
    //    }

    //    public DateTime Birthday
    //    {
    //        get
    //        {
    //            return birthday;
    //        }
    //        set
    //        {
    //            birthday = value;
    //        }
    //    }

    //    public int Age
    //    {
    //        get
    //        {
    //            return new DateTime(DateTime.Now.Subtract(birthday).Ticks).Year;
    //        }
    //    }
    //}

    /* 자동 영역 property
     * 어차피 property를 사용할거면 해당 field를 직접 접근하지 않겠다는 얘기.
     * BirthdayInfo property의 Name에 연결되는 필드를 자동으로 만들고 연결시켜준다.
     */
    //class BirthdayInfo
    //{
    //    public string Name
    //    {
    //        get; set;
    //    }
    //    public DateTime Birthday
    //    {
    //        get; set;
    //    }
    //    public int Age
    //    {
    //        get
    //        {
    //            return new DateTime(DateTime.Now.Subtract(Birthday).Ticks).Year;
    //        }
    //    }

    //}

    /* property에 default 값 넣어주기 */
    //class BirthdayInfo
    //{
    //    public string Name
    //    {
    //        get; set;
    //    } = "Anonymous";
    //    public DateTime Birthday
    //    {
    //        get; set;
    //    } = new DateTime(1, 1, 1);
    //    public int Age
    //    {
    //        get
    //        {
    //            return new DateTime(DateTime.Now.Subtract(Birthday).Ticks).Year;
    //        }
    //    }

    //}

    /// <summary>
    ///  Interface에 property 추가
    /// </summary>
    /* 
     * 내용이 없는 interface. 선언만 되어 있어서 쓸 수 없다.
     * 
     * 클래스 안에 이 interface를 재정의하면 내용이 있는거니까 객체로 쓸 수 있음.
     */
    //interface INamedValue
    //{
    //    string Name
    //    {
    //        get; set;
    //    }
    //    string Value
    //    {
    //        get; set;
    //    }
    //}
    //class NamedValue : INamedValue
    //{
    //    public string Name
    //    {
    //        get; set;
    //    }
    //    public string Value
    //    {
    //        get; set;
    //    }
    //}

    /// <summary>
    ///  추상 클래스의 property가 abstract
    /// </summary>
    /// 
    //abstract class Product
    //{
    //    private static int serial = 0;

    //    public string SerialID
    //    {
    //        get { return String.Format("{0:d5}", serial++); }
    //    }
    //    abstract public DateTime ProductDate
    //    {
    //        get; set;
    //    }
    //}

    //class MyProduct : Product
    //{
    //    public override DateTime ProductDate { get; set; }
    //}

        /// MyList
        /// public int this[int index]
    //class MyList
    //{
    //    private int[] array;
    //    public MyList()
    //    {
    //        array = new int[3];
    //    }
    //    public int this[int index]  // main에서 list[i] 형식으로 쓰기 위해 this[int index]로 정의
    //    {
    //        get
    //        {
    //            return array[index];
    //        }
    //        set
    //        {
    //            if(index >= array.Length)
    //            {
    //                Array.Resize<int>(ref array, index + 1);
    //                Console.WriteLine($"Array Resized: {array.Length}");
    //            }
    //            array[index] = value;
    //        }
    //    }
    //    public int Length
    //    {
    //        get { return array.Length; }
    //    }
    //}
    /// Generic type으로 conversion
    class MyList<T>
    {
        private T[] array;
        public MyList()
        {
            array = new T[3];
        }
        public T this[int index]  // main에서 list[i] 형식으로 쓰기 위해 this[int index]로 정의
        {
            get
            {
                return array[index];
            }
            set
            {
                if (index >= array.Length)
                {
                    Array.Resize<T>(ref array, index + 1);
                    Console.WriteLine($"Array Resized: {array.Length}");
                }
                array[index] = value;
            }
        }
        public int Length
        {
            get { return array.Length; }
        }

    }
    class MainApp
    {
        /// <summary>
        ///  Array
        /// </summary>
        /// <param name="score"></param>
        /// <returns></returns>
        //private static bool CheckPassed(int score)
        //{
        //    if (score >= 60)
        //        return true;
        //    else
        //        return false;
        //}
        /// Copy Array
        //static void CopyArray<T>(T[] source, T[] target)
        //{
        //    for (int i = 0; i < source.Length; i++)
        //        target[i] = source[i];
        //}
        static void Main(string[] args)
        {
            /// Interface
            /* interface, 다형성
             * filelogger, consolelogger 둘 다 start이지만
             * filelogger의 start는 파일에 작성, consolelogger의 start는 콘솔창에 작성.
             */
            //WriteLine("FileLogger Start");
            //ClimateMonitor monitor = new ClimateMonitor(new FileLogger("C:/temp/MyLog.txt"));
            //monitor.start();

            //WriteLine("ConsoleLogger Start");
            //ClimateMonitor monitor2 = new ClimateMonitor(new ConsoleLogger());
            //monitor2.start();

            /* Interface 2 */
            //IFormattableLogger logger = new ConsoleLogger();
            //logger.WriteLog("This is the first WriteLog method.");
            //logger.WriteLog("---{0}---", "This is the second Writelog method.");

            /// Property
            /* property */
            //BirthdayInfo birth = new BirthdayInfo();
            //birth.Name = "고승희";                             // set을 변수쓰듯이 사용 가능 // birth.Name (property)
            //birth.Birthday = new DateTime(1993, 5, 14);
            //Console.WriteLine($"Name : {birth.Name}");
            //Console.WriteLine($"Birthday : {birth.Birthday.ToShortDateString()}");
            //Console.WriteLine($"Age : {birth.Age}");

            /// 자동 영역 Property
            // 객체를 생성함과 동시에 값을 넣어줌
            //BirthdayInfo birth = new BirthdayInfo()
            //{
            //    Name = "고승희",
            //    Birthday = new DateTime(1993, 5, 14)
            //};
            //Console.WriteLine($"Name : {birth.Name}");
            //Console.WriteLine($"Birthday : {birth.Birthday.ToShortDateString()}");
            //Console.WriteLine($"Age : {birth.Age}");

            /// default Property
            //BirthdayInfo birth = new BirthdayInfo();
            //Console.WriteLine($"Name : {birth.Name}");
            //Console.WriteLine($"Birthday : {birth.Birthday.ToShortDateString()}");
            //Console.WriteLine($"Age : {birth.Age}");

            //birth.Name = "고승희";                             // set을 변수쓰듯이 사용 가능 // birth.Name (property)
            //birth.Birthday = new DateTime(1993, 5, 14);
            //Console.WriteLine($"Name : {birth.Name}");
            //Console.WriteLine($"Birthday : {birth.Birthday.ToShortDateString()}");
            //Console.WriteLine($"Age : {birth.Age}");


            ///
            //var a = new { Name = "고승희", Age = 27 };
            //Console.WriteLine($"Name: {a.Name}, Age: {a.Age}");

            //var b = new { Subject = "수학", Scores = new int[] { 90, 85, 80, 75 } };
            //Console.Write($"Subject: {b.Subject}, Scores: ");
            //foreach (var score in b.Scores)
            //    Console.Write($"{score} ");

            //Console.WriteLine();

            ///  Interface에 property 추가
            //NamedValue name = new NamedValue() { Name = "이름", Value = "홍길동" };
            //NamedValue height = new NamedValue() { Name = "키", Value = "170cm" };
            //NamedValue weight = new NamedValue() { Name = "체중", Value = "80kg" };
            //Console.WriteLine($"{name.Name} : {name.Value}");
            //Console.WriteLine($"{height.Name} : {height.Value}");
            //Console.WriteLine($"{weight.Name} : {weight.Value}");

            ///// abstract property
            //Product product1 = new MyProduct()
            //{
            //    ProductDate = new DateTime(2018, 09, 09)
            //};
            //WriteLine("Product: {0}, Product Date: {1}", product1.SerialID, product1.ProductDate);
            //Product product2 = new MyProduct()
            //{ ProductDate = new DateTime(2018, 03, 03) };
            //WriteLine("Product: {0}, Product Date: {1}", product2.SerialID, product2.ProductDate);


            /// Collection type 객체
            //string[] array1 = new string[3] { "C++", "C#", "Java" };
            //foreach (string subject in array1)
            //    WriteLine($"{subject}");
            //WriteLine();

            //string[] array2 = new string[] { "C++", "C#", "Java" };
            //foreach (string subject in array2)
            //    WriteLine($"{subject}");
            //WriteLine();

            //string[] array3 = { "C++", "C#", "Java" };
            //foreach (string subject in array3)
            //    WriteLine($"{subject}");

            /// Array
            //int[] scores = new int[] { 90, 75, 80, 94, 50 };
            //foreach (int score in scores)
            //    Console.Write($"{score}");
            //Console.WriteLine();

            //Array.Sort(scores);
            //foreach (int score in scores)
            //    Console.Write($"{score}");
            //Console.WriteLine();

            //Console.WriteLine($"Number of dimensions: {scores.Rank}");

            //WriteLine("Binary Search : 80 is at {0}", Array.BinarySearch<int>(scores, 80));
            //Console.WriteLine($"Linear Search : 94 is at {0} ", Array.IndexOf(scores, 94));

            //WriteLine("Everyone passed ? : {0}", Array.TrueForAll<int>(scores, CheckPassed));

            //Console.WriteLine($"Old Length of scores: {scores.GetLength(0)}");

            //Array.Resize<int>(ref scores, 10);
            //Console.WriteLine($"New length of scores: {scores.Length}");

            //foreach (int score in scores)
            //    Console.Write($"{score} ");
            //Console.WriteLine();

            /// Array [,] 형식
            //int[,] arr = new int[2, 3] { { 1, 2, 3 }, { 4, 5, 6 } };
            //for (int i = 0; i < arr.GetLength(0); i++)
            //{
            //    for (int j = 0; j < arr.GetLength(0); j++)
            //        Console.Write($"[{i}, {j}] : {arr[i, j]}");
            //    Console.WriteLine();
            //}
            //Console.WriteLine();

            //int[,] arr2 = new int[,] { { 1, 2, 3 }, { 4, 5, 6 } };
            //for(int i=0; i<arr2.GetLength(0); i++)
            //{
            //    for(int j=0; j<arr2.GetLength(1); j++)
            //        Console.Write($"[{i}, {j}] : {arr2[i, j]}");
            //    Console.WriteLine();
            //}
            //Console.WriteLine();

            //int[,] arr3 = { { 1, 2, 3 }, { 4, 5, 6 } };
            //for (int i = 0; i < arr3.GetLength(0); i++)
            //{
            //    for (int j = 0; j < arr3.GetLength(1); j++)
            //        Console.Write($"[{i}, {j}] : {arr3[i, j]}");
            //    Console.WriteLine();
            //}
            //Console.WriteLine();



            //int[][] jagged = new int[3][];
            //jagged[0] = new int[5] { 1, 2, 3, 4, 5 };
            //jagged[1] = new int[] { 10,20,30};
            //jagged[2] = new int[] { 100,200};

            //foreach(int[] arr in jagged)
            //{
            //    Console.Write($"Length: {arr.Length}, ");
            //    foreach (int e in arr)
            //        Console.Write($"{e} ");
            //    Console.WriteLine();
            //}


            //int[][] jagged2 = new int[2][]
            //{
            //    new int[] {100,200},
            //    new int[4] {6,7,8,9}
            //};
            //foreach(int[] arr in jagged2)
            //{
            //    Console.Write($"Length: {arr.Length}, ");
            //    foreach (int e in arr)
            //        Console.Write($"{e} ");
            //    Console.WriteLine();
            //}

            /// ArrayList
            //ArrayList list = new ArrayList();
            //for (int i = 0; i < 5; i++)
            //    list.Add(i);

            //foreach (object obj in list)
            //    Console.Write($"{obj} ");
            //Console.WriteLine();

            //list.RemoveAt(2);

            //foreach (object obj in list)
            //    Console.Write($"{obj} ");
            //Console.WriteLine();

            //list.Insert(2, 2);

            //foreach(object obj in list)
            //    Console.Write($"{obj} ");
            //Console.WriteLine();

            //list.Add("abc");
            //list.Add("def");

            //for(int i=0; i<list.Count; i++)
            //    Console.Write($"{list[i]} ");
            //Console.WriteLine();

            /// Queue
            //Queue que = new Queue();
            //que.Enqueue(1);
            //que.Enqueue(2);
            //que.Enqueue(3);
            //que.Enqueue(4);
            //que.Enqueue(5);

            //while (que.Count > 0)
            //    Console.WriteLine(que.Dequeue());

            /// Hashtable
            //Hashtable hashtable = new Hashtable();

            //hashtable["하나"] = "one";
            //hashtable["둘"] = "two";
            //hashtable["셋"] = "three";
            //hashtable["넷"] = "four";
            //hashtable["다섯"] = "five";

            //Console.WriteLine(hashtable["하나"]);
            //Console.WriteLine(hashtable["둘" ]);
            //Console.WriteLine(hashtable["셋" ]);
            //Console.WriteLine(hashtable["넷" ]);
            //Console.WriteLine(hashtable["다섯"]);

            /// Copy Array
            //int[] source = { 1, 2, 3, 4, 5 };
            //int[] target = new int[source.Length];

            //CopyArray<int>(source, target);

            //foreach (int i in target)
            //    Console.WriteLine(i);

            //string[] source2 = { "C++", "C#", "Java", "Python" };
            //string[] target2 = new string[source2.Length];
            //CopyArray<string>(source2, target2);

            //foreach(string i in target2)
            //    Console.WriteLine(i);

            /// MyList
            //MyList list = new MyList();
            //for (int i = 0; i < 5; i++)
            //    list[i] = i;    // MyList에서 public int this[int index]로 정의한 이유

            //for (int i = 0; i < list.Length; i++)
            //    Console.WriteLine(list[i]);
            
            /// Generic MyList
            MyList<string> str_list = new MyList<string>();
            str_list[0] = "abc";
            str_list[1] = "def";
            str_list[2] = "ghi";
            str_list[3] = "jkl";
            str_list[4] = "mno";
            for (int i = 0; i < str_list.Length; i++)
                Console.WriteLine(str_list[i]);

            MyList<int> int_list = new MyList<int>();
            for (int i = 0; i < 5; i++)
                int_list[i] = i;

            for (int i = 0; i < int_list.Length; i++)
                Console.WriteLine(int_list[i]);
        }
    }
}
