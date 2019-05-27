using System;
using static System.Console;    // system namespace 안의 console 클래스의 static 메소드를 바로 쓰겠다.
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.IO;

namespace day32_05._16
{
    class MainApp
    {
        /// <summary>
        ///  thread (BlueFlag)
        /// </summary>
        /*
         * Thread -> Abort() -> CLR
         * */
        //static void BlueFlag()
        //{
        //    for(int i=0; i<10; i++)
        //    {
        //        WriteLine("청기");
        //        Thread.Sleep(10);
        //    }
        //}

        ///  thread (BlueFlagLoop)
        //static void BlueFlagLoop()
        //{
        //    try{
        //        while(true)
        //        {
        //            WriteLine("청기");
        //            Thread.Sleep(10);
        //        }
        //    }
        //    catch(ThreadAbortException e)
        //    {
        //        Console.WriteLine(e);
        //        Thread.ResetAbort();
        //    }
        //    finally
        //    {
        //        Console.WriteLine("리소스 해제");
        //    }
        //    Console.WriteLine("추가 작업");
        //}


        ///  thread (BlueFlagFlag)
        //static Boolean setStop = false;
        //static void BlueFlagFlag()
        //{
        //    while(!setStop)
        //    {
        //        Console.WriteLine("청기");
        //        Thread.Sleep(10);
        //    }
        //    Console.WriteLine("추가 작업");
        //}

        /// thread (BlueFlagInterrupt) Abort와 Interrupt의 차이
        /* Abort는 호출되는 순간 스레드가 종료됨.
         * 
         * flag를 못 쓰는 상황에선 interrupt 사용
         * interrupt되어도 반드시 실행되어야 하는 코드는 마무리되고 종료될 수 있도록
         * 중간에 interrupt되어도 되는 순간에 Thread.Sleep()을 줘서 interrupt되는 순간을 컨트롤할 수 있음.
         * Sleep 상태가 되고, waitsleepjoin 상태가 되면 그 때 interrupt 상태 (sleep 상태를 깨움)로 변경돼서 종료될 수 있도록 함.
         */
        //    static void BlueFlagInterrupt()
        //{
        //    try
        //    {
        //        while(true)
        //        {
        //            Console.WriteLine("청기");
        //            Thread.Sleep(10);
        //        }
        //    }
        //    catch(ThreadInterruptedException e)
        //    {
        //        Console.WriteLine(e);
        //    }
        //    finally
        //    {
        //        Console.WriteLine("리소스 해제");
        //    }
        //    Console.WriteLine("추가 작업");
        //}

        /// Thread (Counter)
        /* lock(thisLock)된 순간에 다른 스레드가 다른 함수로 들어갔어도 대기해야 함.
         * 
         * */
        //    class Counter
        //{
        //    const int LOOP_COUNT = 1000;

        //    readonly object thisLock;
        //    private int count;

        //    public int Count
        //    {
        //        get { return count; }
        //    }

        //    public Counter()
        //    {
        //        thisLock = new object();
        //        count = 0;
        //    }

        //    public void Increase()
        //    {
        //        int loopCount = LOOP_COUNT;
        //        while(loopCount-- > 0)
        //        {
        //            // critical section
        //            lock (thisLock)
        //            {
        //                count++;
        //            }
        //            //count++;
        //            Thread.Sleep(1);
        //        }
        //    }
        //    public void Decrease()
        //    {
        //        int loopCount = LOOP_COUNT;
        //        while (loopCount-- > 0)
        //        {
        //            // critical section
        //            lock (thisLock)
        //            {
        //                count--;
        //            }
        //            //count--;
        //            Thread.Sleep(1);
        //        }
        //    }
        //}

        /// CounterMonitor
        //class CounterMonitor
        //{
        //    const int LOOP_COUNT = 1000;

        //    readonly object thisLock;
        //    private int count;
        //    bool lockedCount = false;

        //    public int Count
        //    {
        //        get { return count; }
        //    }

        //    public CounterMonitor()
        //    {
        //        thisLock = new object();
        //        count = 0;
        //    }

        //    public void Increase()
        //    {
        //        int loopCount = LOOP_COUNT;
        //        while (loopCount-- > 0)
        //        {
        //            // critical section
        //            Monitor.Enter(thisLock);
        //            try
        //            {
        //                count++;
        //            }
        //            finally
        //            {
        //                Monitor.Exit(thisLock);
        //            }
        //            Thread.Sleep(1);
        //        }
        //    }
        //    public void Decrease()
        //    {
        //        int loopCount = LOOP_COUNT;
        //        while (loopCount-- > 0)
        //        {
        //            Monitor.Enter(thisLock);
        //            try
        //            {
        //                count++;
        //            }
        //            finally
        //            {
        //                Monitor.Exit(thisLock);
        //            }
        //            Thread.Sleep(1);
        //        }
        //    }
        //}

        /// CounterMonitor lock (오류)
        //class CounterMonitorLock
        //{
        //    const int LOOP_COUNT = 1000;

        //    readonly object thisLock;
        //    private int count;
        //    bool lockedCount = false;

        //    public int Count
        //    {
        //        get { return count; }
        //    }

        //    public CounterMonitorLock()
        //    {
        //        thisLock = new object();
        //        count = 0;
        //    }

        //    public void Increase()
        //    {
        //        int loopCount = LOOP_COUNT;
        //        while (loopCount-- > 0)
        //        {
        //            lock (thisLock)
        //            {
        //                if (count < 0 || lockedCount == true)
        //                {
        //                    Monitor.Wait(thisLock);
        //                }
        //            }
        //            lockedCount = true;
        //            count++;
        //            lockedCount = false;
        //            Monitor.Pulse(thisLock);
        //        }
        //    }
        //    public void Decrease()
        //    {
        //        int loopCount = LOOP_COUNT;
        //        while (loopCount-- > 0)
        //        {
        //            lock (thisLock)
        //            {
        //                if (count < 0 || lockedCount == true)
        //                {
        //                    Monitor.Wait(thisLock);
        //                }
        //            }
        //            lockedCount = true;
        //            count--;
        //            lockedCount = false;
        //            Monitor.Pulse(thisLock);
        //        }
        //    }
        //}

        /// Prime Number
        //static bool IsPrime(long number)
        //{
        //    if (number < 2)
        //        return false;

        //    if (number % 2 == 0 && number != 2)
        //        return false;
        //    for (long i = 2; i < number; i++)
        //    {
        //        if (number % i == 0)
        //            return false;
        //    }
        //    return true;
        //}

        /// async, await
        /* <async, await>
         * - async: 메소드, 이벤트처리기, 태스크, 람다식
         * - async로 한정하는 메소드는 반드시!!!!!!!!!!!! 반환형식이 Task, Task<TResult> 또는 void여야 함. (문제 하나 나옴)
         * - Task, Task<TResult> 타입 메소드는 메소드 내부에 await 연산자를 만나면 호출자에게 제어권 넘김
         * (await 연산자가 없으면 동기방식으로 진행)
         * */
        async static private void MyMethodAsync(int count)
        {
            Console.WriteLine("C");
            Console.WriteLine("D");

            // 호출한 쪽 스레드와 동시에 돌아감.
            // await니까 여기는 비동기로 돌아가게끔 넘기고 바로 밑으로 툭!
            // UI 스레드가 정지되지 않고 메세지 루프를 계속 돌 수 있도록.
            // 언제 실행될지 알 수 없음. 최소한 일정 정도의 코드는 반드시 실행된 후
            // Task가 실행될 수 있도록?
            // 메인 스레드가 더 이상 진행되기 전에 반드시 실행되어야 하는 부분을 보장받을 수 있음.
            // await 이전은 반드시 실행되니까.
            // 일반 Task로는 보장받을 수 없다.
            await Task.Run(() =>
            {
                for (int i = 1; i <= count; i++)
                {
                    Console.WriteLine($"{i}/{count}...");
                    Thread.Sleep(100);
                }
            });

            // await Task가 끝나야 아래가 실행됨.
            Console.WriteLine("G");
            Console.WriteLine("H");
        }

        static void Caller()
        {
            Console.WriteLine("A");
            Console.WriteLine("B");

            MyMethodAsync(3);

            Console.WriteLine("E");
            Console.WriteLine("F");
        }


        static void Main(string[] args)
        {
            ///  thread (BlueFlag)
            //Thread thread = new Thread(new ThreadStart(BlueFlag));  // ThreadStart: delegate

            //WriteLine("Start thread...");
            //thread.Start(); // ThreadStart delegate를 실행시킴

            //for(int i=0; i<10; i++)
            //{
            //    WriteLine($"백기");
            //    Thread.Sleep(10);
            //}

            //WriteLine("Waiting until thread stop...");
            //thread.Join();  // 위에 생성한 thread가 끝나길 main thread가 기다림

            //WriteLine("Finished");


            ///  thread (BlueFlagLoop)
            //Thread thread = new Thread(new ThreadStart(BlueFlagLoop));  // ThreadStart: delegate

            //WriteLine("Start thread...");
            //thread.Start(); // ThreadStart delegate를 실행시킴

            //Thread.Sleep(100);

            //Console.WriteLine("Aborting thread...");
            //thread.Abort();

            //WriteLine("Waiting until thread stop...");
            //thread.Join();  // 위에 생성한 thread가 끝나길 main thread가 기다림

            //WriteLine("Finished");

            ///  thread (BlueFlagFlag)
            ///  flag를 사용해 thread를 조작하는 경우 제일 추천하는 방법
            //Thread thread = new Thread(new ThreadStart(BlueFlagFlag));  // ThreadStart: delegate

            //WriteLine("Start thread...");
            //thread.Start(); // ThreadStart delegate를 실행시킴

            //Thread.Sleep(100);

            //Console.WriteLine("Stop thread...");
            //setStop = true;

            //WriteLine("Waiting until thread stop...");
            //thread.Join();  // 위에 생성한 thread가 끝나길 main thread가 기다림

            //WriteLine("Finished");

            /// thread (BlueFlagInterrupt)
            //Thread thread = new Thread(new ThreadStart(BlueFlagInterrupt));  // ThreadStart: delegate

            //WriteLine("Start thread...");
            //thread.Start(); // ThreadStart delegate를 실행시킴

            //Thread.Sleep(100);

            //Console.WriteLine("Interrupting thread...");
            //thread.Interrupt();

            //WriteLine("Waiting until thread stop...");
            //thread.Join();  // 위에 생성한 thread가 끝나길 main thread가 기다림

            //WriteLine("Finished");


            /// Thread (Counter)
            //Counter counter = new Counter();

            //Thread incThread = new Thread(new ThreadStart(counter.Increase));
            //Thread decThread = new Thread(new ThreadStart(counter.Decrease));

            //incThread.Start();
            //decThread.Start();

            //incThread.Join();
            //decThread.Join();

            //Console.WriteLine(counter.Count);


            /// Thread (CounterMonitor)
            //CounterMonitor counter = new CounterMonitor();

            //Thread incThread = new Thread(new ThreadStart(counter.Increase));
            //Thread decThread = new Thread(new ThreadStart(counter.Decrease));

            //incThread.Start();
            //decThread.Start();

            //incThread.Join();
            //decThread.Join();

            //Console.WriteLine(counter.Count);


            /// Thread (CounterMonitorLock)  (오류)
            //CounterMonitorLock counter = new CounterMonitorLock();

            //Thread incThread = new Thread(new ThreadStart(counter.Increase));
            //Thread decThread = new Thread(new ThreadStart(counter.Decrease));

            //incThread.Start();
            //decThread.Start();

            //incThread.Join();
            //decThread.Join();

            //Console.WriteLine(counter.Count);

            /// 비동기 copy
            string srcFile = args[0];
            Action<object> FileCopyAction = (object state) =>
            {
                string[] paths = (string[])state;
                File.Copy(paths[0], paths[1]);

                Console.WriteLine("TaskID:{0}, ThreadID: {1}, {2} was copied to {3}",
                    Task.CurrentId, Thread.CurrentThread.ManagedThreadId,
                    paths[0], paths[1]);
            };

            Task t1 = new Task(FileCopyAction, new string[] { srcFile, srcFile + ".copy1" });
            t1.Start(); // 비동기적으로 실행시키고 아래 코드로 넘어감.


            Task t2 = Task.Run(() =>
            {
                FileCopyAction(new string[] { srcFile, srcFile + ".copy2" });
            });


            Task t3 = new Task(FileCopyAction, new string[] { srcFile, srcFile + ".copy3" });
            t3.RunSynchronously();  // 동기방식으로 실행

            t1.Wait();
            t2.Wait();

            /// Task List
            long from = Convert.ToInt64(args[0]);
            long to = Convert.ToInt64(args[1]);
            int taskCount = Convert.ToInt32(args[2]);

            Func<object, List<long>> FindPrimeFunc = (objRange) =>
            {
                long[] range = (long[])objRange;
                List<long> found = new List<long>();

                for (long i = range[0]; i <= range[1]; i++)
                {
                    if (IsPrime(i))
                        found.Add(i);
                }

                return found;
            };
            Task<List<long>>[] tasks = new Task<List<long>>[taskCount];
            long currentFrom = from;
            long currentTo = from + (to - from) / tasks.Length;

            for (int i = 0; i < tasks.Length; i++)
            {
                Console.WriteLine("Task[{0}] :: {1} ~ {2}", i, currentFrom, currentTo);

                tasks[i] = new Task<List<long>>(FindPrimeFunc, new long[] { currentFrom, currentTo });
                currentFrom = currentTo + 1;

                if (i == tasks.Length - 2)
                    currentTo = to;
                else
                    currentTo += ((to - from) / tasks.Length);
            }

            Console.WriteLine("Please press enter to start... ");

            Console.ReadLine();
            Console.WriteLine("Started...");

            DateTime startTime = DateTime.Now;

            foreach (Task<List<long>> task in tasks)
                task.Start();

            List<long> total = new List<long>();

            foreach (Task<List<long>> task in tasks)
            {
                total.AddRange(task.Result.ToArray());
            }
            DateTime endTime = DateTime.Now;

            TimeSpan ellapsed = endTime - startTime;

            Console.WriteLine("Prime number count between {0} and {1} : {2}", from, to, total.Count);
            Console.WriteLine("Ellapsed time : {0}", ellapsed);

            /// Task List Parllel.For
            //long from = Convert.ToInt64(args[0]);
            //long to = Convert.ToInt64(args[1]);

            //Console.WriteLine("Please press enter to start... ");
            //Console.ReadLine();
            //Console.WriteLine("Started...");

            //DateTime startTime = DateTime.Now;
            //List<long> total = new List<long>();

            //// 병렬 루프
            //Parallel.For(from, to + 1, (long i) =>   // from <= x < to + 1
            //{
            //    if (IsPrime(i))
            //        total.Add(i);
            //});

            //DateTime endTime = DateTime.Now;
            //TimeSpan ellapsed = endTime - startTime;

            //Console.WriteLine("Prime number count between {0} and {1} : {2}", from, to, total.Count);
            //Console.WriteLine("Ellapsed time : {0}", ellapsed);

            Caller();
            Console.WriteLine("####################");
            Console.ReadLine();

        }
    }
}
