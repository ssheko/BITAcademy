using System;
using static System.Console;    // system namespace 안의 console 클래스의 static 메소드를 바로 쓰겠다.
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace day29_05._13
{
    /* class */
    //class Car
    //{
    //    private string model;
    //    private string color;

    //    public Car()
    //    {
    //        model = "세단";
    //        color = "흰색";
    //    }

    //    public Car(string m, string c)
    //    {
    //        model = m;
    //        color = c;
    //    }

    //    public void ShowStatus()
    //    {
    //        WriteLine($"Model : {model}, Color : {color}");
    //    }

    //    ~Car()
    //    {
    //        WriteLine("소멸자 실행");
    //    }
    //}

    /* Static Field */
    //class StaticField
    //{
    //    public static int count = 0;
    //    public static void ShowCount()
    //    {
    //        WriteLine($"StaticField.count : {count}");
    //    }
    //}

    //class ClassA
    //{
    //    public ClassA()
    //    {
    //        // static field 멤버변수 직접 접근 가능
    //        StaticField.count++;
    //    }
    //}
    //class ClassB
    //{
    //    public ClassB()
    //    {
    //        StaticField.count++;
    //    }
    //}

    /* ShallowDeepCopy */
    //class ShallowDeepCopy
    //{
    //    public int field1;
    //    public int field2;

    //    public ShallowDeepCopy DeepCopy()
    //    {
    //        ShallowDeepCopy newClass = new ShallowDeepCopy();
    //        newClass.field1 = field1;
    //        newClass.field2 = field2;

    //        return newClass;
    //    }
    //}

    /* this, get, set */
    //class Employee
    //{
    //    private string name;
    //    private string position;

    //    public void SetName(string name)
    //    {
    //        this.name = name;
    //    }

    //    public string GetName()
    //    {
    //        return name;
    //    }

    //    public void SetPosition(string position)
    //    {
    //        this.position = position;
    //    }

    //    public string GetPosition()
    //    {
    //        return position;
    //    }
    //}

    /* constructor */
    //class ThisConstructor
    //{
    //    // 초기화하지 않으면 숫자타입은 0, char 타입은 '\0', reference타입은 Null로 초기화시켜줌.
    //    private int a, b, c;

    //    public ThisConstructor()
    //    {
    //        a = 1111;
    //        WriteLine("ThisConstructor()");
    //    }

    //    public ThisConstructor(int b) : this()
    //    {
    //        this.b = b;
    //        WriteLine("ThisConstructor(int)");
    //    }
    //    public ThisConstructor(int b, int c) : this(b)
    //    {
    //        this.c = c;
    //        WriteLine("ThisConstructor(int, int)");
    //    }
    //    public void PrintFields()
    //    {
    //        WriteLine($"a:{a}, b:{b}, c:{c}");
    //    }
    //}

    /* 상속 */
    //class Parent
    //{
    //    protected string name;

    //    public Parent()
    //    {
    //        name = "김철수";
    //        WriteLine($"{this.name}.Parent()");
    //    }
    //    public Parent(string name)
    //    {
    //        this.name = name;
    //        WriteLine($"{this.name}.Parent(string)");
    //    }

    //    ~Parent()
    //    {
    //        WriteLine($"{this.name}.~Parent()");
    //    }
    //    public void ParentMethod()
    //    {
    //        WriteLine($"{this.name}.ParentMethod()");
    //    }

    //}

    //class Child : Parent
    //{
    //    public Child()
    //    {
    //        WriteLine($"{this.name}.Child()");
    //    }

    //    public Child(string name) : base(name)  // 부모 생성자 호출
    //    {
    //        WriteLine($"{this.name}.Child(string)");
    //    }
    //    ~Child()
    //    {
    //        WriteLine($"{this.name}.~Child()");
    //    }

    //    public void ChildMethod()
    //    {
    //        WriteLine($"{this.name}.ChildMethod()");
    //    }
    //}

    /* 다형성 */
    //class Mammal
    //{
    //    public void Nurse()
    //    {
    //        WriteLine("Nursing~~");
    //    }
    //}

    //class Dog : Mammal
    //{
    //    public void Bark()
    //    {
    //        WriteLine("Barking~~");
    //    }
    //}
    //class Human : Mammal
    //{
    //    public void Speak()
    //    {
    //        WriteLine("Speaking~~");
    //    }
    //}

    /* override 
     * -> public override void 형식으로 override를 명시해줘야 한다.
     */
    /* ver.1 override */
    //class Car
    //{
    //    protected string model;
    //    protected string powerTrain;

    //    public Car(string model, string powerTrain)
    //    {
    //        this.model = model;
    //        this.powerTrain = powerTrain;
    //    }

    //    public virtual void drive()
    //    {
    //        WriteLine("달린다~~~");
    //    }
    //}

    //class GasolineCar : Car
    //{
    //    public GasolineCar(string model, string powerTrain)
    //        : base(model, powerTrain)
    //    {

    //    }
    //    public override void drive()
    //    {
    //        //base.drive();
    //        WriteLine($"{model} {powerTrain} 부르릉~~~");
    //    }

    //}

    //class HybridCar : Car
    //{
    //    public HybridCar(string model, string powerTrain)
    //        : base(model, powerTrain)
    //    {

    //    }

    //    public override void drive()
    //    {
    //        //base.drive();
    //        WriteLine($"{model} {powerTrain} 스르륵~~~");
    //    }
    //}

    /* ver.2 부모 클래스 숨기기 */
    //class Car
    //{
    //    protected string model;
    //    protected string powerTrain;

    //    public Car(string model, string powerTrain)
    //    {
    //        this.model = model;
    //        this.powerTrain = powerTrain;
    //    }
    //    public void drive() // virtual 대상이 아닐 경우
    //    {
    //        WriteLine("달린다~~~");
    //    }
    //}

    //class GasolineCar : Car
    //{
    //    public GasolineCar(string model, string powerTrain)
    //        : base(model, powerTrain)
    //    {

    //    }
    //    public new void drive() // 부모의 drive를 상속받을 수 없으므로 new 키워드를 사용해 본인의 drive를 선언
    //    {
    //        //base.drive();
    //        WriteLine($"{model} {powerTrain} 부르릉~~~");
    //    }
    //}

    //class HybridCar : Car
    //{
    //    public HybridCar(string model, string powerTrain)
    //        : base(model, powerTrain)
    //    {

    //    }

    //    public new void drive() // 부모의 drive를 상속받을 수 없으므로 new 키워드를 사용해 본인의 drive를 선언
    //    {
    //        //base.drive();
    //        WriteLine($"{model} {powerTrain} 스르륵~~~");
    //    }
    //}

    /* 클래스 안의 클래스 */
    //class Configuration
    //{
    //    List<ItemValue> listConfig = new List<ItemValue>();

    //    public void SetConfig(string item, string value)
    //    {
    //        ItemValue iv = new ItemValue();
    //        iv.SetValue(this, item, value);
    //    }

    //    public String GetConfig(string item)
    //    {
    //        foreach (ItemValue iv in listConfig)
    //        {
    //            if (iv.GetItem() == item)
    //                return iv.GetValue();
    //        }
    //        return "";
    //    }
    //    /// <summary>
    //    /// 클래스 안의 클래스
    //    /// </summary>
    //    // 클래스 안의 클래스
    //    private class ItemValue
    //    {
    //        private string item;
    //        private string value;

    //        public void SetValue(Configuration config, string item, string value)
    //        {
    //            this.item = item;
    //            this.value = value;

    //            bool found = false;
    //            for (int i = 0; i < config.listConfig.Count; i++)
    //            {
    //                if (config.listConfig[i].item == item)
    //                {
    //                    config.listConfig[i] = this;
    //                    found = true;
    //                    break;
    //                }
    //            }
    //            if (found == false)
    //            {
    //                config.listConfig.Add(this);
    //            }
    //        }

    //        public string GetItem()
    //        {
    //            return item;
    //        }

    //        public string GetValue()
    //        {
    //            return value;
    //        }
    //    }
    //}

    /// <summary>
    /// partial class
    /// </summary>
    //partial class AAA
    //{
    //    public void Method1()
    //    {
    //        WriteLine("Method1()");
    //    }
    //    public void Method2()
    //    {
    //        WriteLine("Method2()");
    //    }
    //}
    //partial class AAA
    //{
    //    public void Method3()
    //    {
    //        WriteLine("Method3()");
    //    }
    //    public void Method4()
    //    {
    //        WriteLine("Method4()");
    //    }
    //}

    /* (this int input) */
    //public static class EnhancedInteger // class의 기본속성은 internal
    //{
    //    public static int Square(this int input)
    //    {
    //        return input * input;
    //    }

    //    public static int Power(this int input, int exponent)
    //    {
    //        int result = input;
    //        for (int i = 1; i < exponent; i++)
    //            result *= input;
    //        return result;
    //    }
    //}

    /// <summary>
    /// 구조체
    /// 구조체는 값형식(클래스는 참조 형식)
    /// 선언만으로도 생성 가능
    /// Deep Copy
    /// 매개변수 없는 생성자 선언 불가능
    /// 상속 불가능
    /// </summary>    
    //struct Point3D
    //{
    //    public int x;
    //    public int y;
    //    public int z;

    //    public Point3D(int x, int y, int z)
    //    {
    //        this.x = x;
    //        this.y = y;
    //        this.z = z;
    //    }

    //    public override string ToString()   // 
    //    {
    //        return string.Format($"{x}, {y}, {z} ");
    //    }
    //}


    /* 추상 클래스 */
    abstract class AbstractBase
    {
        protected void PrivateMethodA()
        {
            Console.WriteLine("AbstractBase.PrivateMethodA()");
        }

        public void PublicMethodA()
        {
            Console.WriteLine("AbstractBase.PublicMethodA()");
        }
        public abstract void AbstractMethodA();
    }

    class Derived : AbstractBase    // 자식 입장에서 부모의 메서드를 상속받을 수 있는 경우는 abstract이거나 virtual로 선언되었을 경우 두 가지밖에 없다.
    {
        public override void AbstractMethodA()
        {
            //throw new NotImplementedException();
            Console.WriteLine("Derived.AbstractMethodA()");
            PrivateMethodA();
        }
    }


    class MainApp
    {
        /* (params int[] args) */
        //static int Sum(params int[] args)
        //{
        //    int sum = 0;
        //    for(int i=0;i<args.Length; i++)
        //    {
        //        if (i > 0)
        //            Write(", ");
        //        Write(args[i]);
        //        sum += args[i];
        //    }
        //    WriteLine();
        //    return sum;
        //}

        /* parameter = "" */
        //static void PrintProfile(string name, string phone = "")
        //{
        //    WriteLine($"Name: {name}, Phone: {phone}");
        //}

        /* 함수 안의 함수 (로컬 함수) */
        //static string ToLowerString(string str)
        //{
        //    var arr = str.ToCharArray();
        //    for(int i=0; i<arr.Length; i++)
        //    {
        //        arr[i] = ToLowerChar(i);
        //    }

        //    char ToLowerChar(int i)
        //    {
        //        // 메소드 내에 속한 지역변수를 자유자재로 사용 가능
        //        if (arr[i] < 65 || arr[i] > 90)
        //            return arr[i];
        //        else
        //            return (char)(arr[i] + 32); // arr[i] + 32 --> int 타입
        //    }

        //    return new string(arr);
        //}        


        static void Main(string[] args)
        {
            /* (params int[] args) */
            //int sum = Sum(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
            //WriteLine($"Sum: {sum}");

            /* parameter = "" */
            //PrintProfile("홍길동");
            //PrintProfile("홍길동", "010-1111-2222");
            //PrintProfile(name: "김유신");
            //PrintProfile(name: "이순신", phone:"010-5555-6666");

            /* 함수 안의 함수 (로컬 함수) */
            //WriteLine(ToLowerString("Hello"));
            //WriteLine(ToLowerString("World"));
            //WriteLine(ToLowerString("C# Programming"));

            /* class
             * C#는 garbage collector가 작동해서 참조를 잃어버린 객체는 CPU의 알고리즘을 통해 객체를 알아서 삭제해줌.
             * --> CPU가 바뀌면 작동이 안 될수도 있음. (원하는 타이밍에 소멸자가 실행이 안 될 수도 있음)
             * 따라서 소멸자 안에 반드시 실행되어야 할 메서드를 사용하지 않는 게 좋음.
             */
            //Car myCar = new Car();
            //Car yourCar = new Car("SUV", "블랙");
            //myCar.ShowStatus();
            //yourCar.ShowStatus();

            /* Static Field
             * static field는 .을 통해 직접 접근 가능
             */
            //StaticField.ShowCount();

            //new ClassA();
            //new ClassA();
            //new ClassB();
            //new ClassB();

            //StaticField.ShowCount();

            /* ShallowDeepCopy */
            //WriteLine("Shallow Copy");
            //// stack에 source가, heap 영역에 ShallowDeepCopy 객체가 생성됨. source가 ShallowDeepCopy 객체를 가리키는 중.
            //ShallowDeepCopy source = new ShallowDeepCopy();
            //source.field1 = 10; // ShallowDeepCopy 객체에 각각 10, 20 값이 추가됨.
            //source.field2 = 20;

            //// C++: 디폴트 대입연산자 호출.
            //// C#: stack에 있는 source의 주소값이 heap 영역에 생성됨.
            ////      stack에 있는 target이 heap 영역의 source가 가리키는 영역(ShallowDeepcopy 객체)을 가리킴.
            //// source의 reference값을 target에 넘겨줌
            //ShallowDeepCopy target = source;
            //target.field2 = 30;
            //WriteLine($"{source.field1} {source.field2}");
            //WriteLine($"{target.field1} {target.field2}");

            //WriteLine();
            //WriteLine("Deep Copy");
            //ShallowDeepCopy deepSource = new ShallowDeepCopy();
            //deepSource.field1 = 10;
            //deepSource.field2 = 20;

            //// heap 영역에 ShallowDeepCopy 객체가 새로 생성. 값은 deepSource가 가리키는 heap 영역에 있는 값이 그대로 복사되어 온다.
            //ShallowDeepCopy deepTarget = deepSource.DeepCopy();
            //deepTarget.field2 = 30;
            //WriteLine($"{deepSource.field1} {deepSource.field2}");
            //WriteLine($"{deepTarget.field1} {deepTarget.field2}");

            /* this, get, set */
            //Employee worker = new Employee();
            //worker.SetName("홍길동");
            //worker.SetPosition("Guard");
            //WriteLine($"{worker.GetName()} {worker.GetPosition()} ");

            /* constructor */
            //ThisConstructor a = new ThisConstructor();
            //a.PrintFields();
            //WriteLine();

            //ThisConstructor b = new ThisConstructor(10);
            //b.PrintFields();
            //WriteLine();

            //ThisConstructor c = new ThisConstructor(10, 20);
            //c.PrintFields();
            //WriteLine();

            /* 접근 제한자 (접근 제한자 생략시 default는 무조건 private)
             * 1. public: 클래스의 내부/외부 모든 곳에서 접근 가능
             * 2. protected: 클래스의 외부에서 접근 불가능, 자식 클래스에서는 접근 가능
             * 3. private: 클래스의 내부에서만 접근 가능 
             * 4. internal: 같은 어셈블리에 있는 코드에서만 public으로 접근 가능
             * 5. protected internal: 같은 어셈블리에 있는 코드에서 protected로 접근 가능
             * */

            /* 상속 */
            //Parent parent = new Parent("홍길동아버지");
            //parent.ParentMethod();
            //WriteLine();

            //Child child = new Child("홍길동");
            //child.ParentMethod();
            //child.ChildMethod();
            //WriteLine();

            /* sealed
             *     : 클래스의 상속을 불가능하게 만듬
             *     
             * sealed class AAA
             * {
             * 
             * }
             * 
             * class BBB : AAA --> 불가능
             */
            //Mammal mammal = new Mammal();
            //mammal.Nurse();
            //WriteLine();

            //mammal = new Dog();
            //mammal.Nurse(); // Dog의 메서드는 사용 불가
            //WriteLine();

            //if(mammal is Dog)
            //{
            //    Dog dog = (Dog)mammal;  // 강제로 Dog로 캐스팅해야 Dog 메서드 사용 가능
            //    dog.Nurse();
            //    dog.Bark();
            //    WriteLine();
            //}

            //mammal = new Human();
            //mammal.Nurse();
            //WriteLine();

            ////Human human = (Human)mammal;
            //Human human = mammal as Human;  // mammal을 Human으로 형변환. 불가능할 경우 human은 null이 된다.
            //if (human != null)
            //{
            //    human.Nurse();
            //    human.Speak();
            //}
            //else
            //    WriteLine("human is not Human");

            /* Override
             * virtual 함수를 선언하지 않아 메소드 오버로딩이 불가능할 경우, new 키워드를 사용해 본인의 메소드를 선언할 수 있지만,
             * Car 타입 객체를 GasolineCar 객체로 받을 수 없음.
             * (부모 base클래스 메소드 숨기기)
             * override가 선언되지 않은 부모 클래스의 메소드를 상속받고 싶을 경우 반드시 new로 정의해야 한다.
             */
            /* ver.1 */
            //Car gasolineCar = new GasolineCar("소나타", "가솔린엔진");
            //gasolineCar.drive();

            //Car hybridCar = new HybridCar("프리우스", "가솔린엔진, 전기모터");
            //hybridCar.drive();

            /* ver.2 */
            //GasolineCar gasolineCar = new GasolineCar("소나타", "가솔린엔진");
            //gasolineCar.drive();

            //HybridCar hybridCar = new HybridCar("프리우스", "가솔린엔진, 전기모터");
            //hybridCar.drive();


            /* 클래스 안의 클래스 */
            //Configuration config = new Configuration();
            //config.SetConfig("Version", "V5.0");
            //config.SetConfig("Size", "655, 324 KB");

            //WriteLine(config.GetConfig("Version"));
            //WriteLine(config.GetConfig("Size"));

            //config.SetConfig("Version", "V5.1");
            //WriteLine(config.GetConfig("Version"));

            /* partial class */
            //AAA obj = new AAA();
            //obj.Method1();
            //obj.Method2();
            //obj.Method3();
            //obj.Method4();

            /* (this int input) */
            //WriteLine($"3^2 : {3.Square()}");
            //WriteLine($"3^4 : {3.Power(4)}");
            //WriteLine($"2^10 : {2.Power(10)}");

            /* 구조체 */
            //Point3D point1;
            //point1.x = 10;
            //point1.y = 20;
            //point1.z = 30;

            //WriteLine(point1.ToString());

            //Point3D point2 = new Point3D(100, 200, 300);
            //Point3D point3 = point2;
            //point3.z = 400;

            //WriteLine(point2.ToString());
            //WriteLine(point3.ToString());

            /* 튜플 
             * 1. Unnamed Tuple
             *      var a = (123, 456);
             *      WriteLine($"{a.Item1, 
             *      
             * 2. Named Tuple
             *      var a = (Name: "홍길동", Age: 20);
             *      WriteLine($"{a.Name}, {a.Age}");
             *      
             * 3. 튜플 분해
             *      var a = (Name: "홍길동", Age: 20);
             *      var (name, age) = a;
             *      WriteLine($"{name}, {age}");
             *      
             * 4. 필드 무시
             *      var a = (Name: "홍길동", Age: 20);
             *      var (name, _) = a;
             *      WriteLine($"{name}, {age}");
             * 
             */

            //var a = ("홍길동", 20);
            //WriteLine($"{a.Item1}, {a.Item2}");

            //var b = (Name: "홍길동", Age: 20);
            //WriteLine($"{b.Name}, {b.Age}");

            //var (name, age) = b;
            //WriteLine($"{name}, {age}");

            //b = a;
            //WriteLine($"{b.Name}, {b.Age}");

            /* 추상 클래스 */
            AbstractBase obj = new Derived();
            obj.AbstractMethodA();
            obj.PublicMethodA();
        }
    }
}
