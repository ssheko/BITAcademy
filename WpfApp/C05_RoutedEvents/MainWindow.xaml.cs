using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Windows.Threading;

namespace C05_RoutedEvents
{
    /// <summary>
    /// MainWindow.xaml에 대한 상호 작용 논리
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
        }
        /** Bubble Label Click */
        //protected int eventCounter = 0;

        //private void SomethingClicked(object sender, RoutedEventArgs e)
        //{
        //    eventCounter++;
        //    string message = "#" + eventCounter.ToString() + ":\r\n" +
        //        " Sender: " + sender.ToString() + "\r\n" +
        //        " Source: " + e.Source + "\r\n" +
        //        " Original Source: " + e.OriginalSource;
        //    lstMessages.Items.Add(message);
        //    e.Handled = (bool)chkHandle.IsChecked;
        //}

        //private void cmdClear_Click(object sender, RoutedEventArgs e)
        //{
        //    eventCounter = 0;
        //    lstMessages.Items.Clear();
        //    //this.Dispatcher.Invoke((ThreadStart)(() => { }), DispatcherPriority.ApplicationIdle);
        //    //Thread.Sleep(1000);

        //}



        /** Key Press Events */
        //private void KeyEvent(object sender, KeyEventArgs e)
        //{
        //    if ((bool)chkIgnoreRepeat.IsChecked && e.IsRepeat) return;

        //    string message = //"At: " + e.Timestamp.ToString() +
        //        "Event: " + e.RoutedEvent + " " +
        //        " Key: " + e.Key;
        //    lstMessages.Items.Add(message);
        //}

        //private void TextInput(object sender, TextCompositionEventArgs e)
        //{
        //    string message = //"At: " + e.Timestamp.ToString() +
        //        "Event: " + e.RoutedEvent + " " +
        //        " Text: " + e.Text;
        //    lstMessages.Items.Add(message);
        //}

        //private void TextChanged(object sender, TextChangedEventArgs e)
        //{
        //    string message =
        //        "Event: " + e.RoutedEvent;
        //    lstMessages.Items.Add(message);
        //}

        //private void cmdClear_Click(object sender, RoutedEventArgs e)
        //{
        //    lstMessages.Items.Clear();
        //}



        /** OnlyNumbers */
        //private void pnl_PreviewTextInput(object sender, TextCompositionEventArgs e)
        //{
        //    short val;
        //    if (!Int16.TryParse(e.Text, out val))
        //    {
        //        e.Handled = true;
        //    }
        //}

        //private void pnl_PreviewKeyDown(object sender, KeyEventArgs e)
        //{
        //    if (e.Key == Key.Space)   // 스페이스바일 경우
        //    {
        //        e.Handled = true;
        //    }
        //}


        /** MousePosition */

        private void cmdCapture_Click(object sender, RoutedEventArgs e)
        {
            this.AddHandler(
                   Mouse.LostMouseCaptureEvent,
                   new RoutedEventHandler(this.LostCapture));
            Mouse.Capture(rect);

            cmdCapture.Content = "[ Mouse is now captured ... ]";
        }

        private void MouseMoved(object sender, MouseEventArgs e)
        {
            Point pt = e.GetPosition(this);
            lblInfo.Text =
                String.Format("You are at ({0},{1}) in window coordinates",
                pt.X, pt.Y);
        }

        private void LostCapture(object sender, RoutedEventArgs e)
        {
            MessageBox.Show("Lost capture");
            cmdCapture.Content = "Capture the Mouse";
        }

    }
}
