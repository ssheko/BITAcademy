using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
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

namespace EmployeeList
{
    /// <summary>
    /// MainWindow.xaml에 대한 상호 작용 논리
    /// </summary>
    public partial class MainWindow : Window
    {
        private List<Employee> employees;
        public MainWindow()
        {
            InitializeComponent();
        }

        private void BtnEmployeeID_Click(object sender, RoutedEventArgs e)
        {
            //long id;
            //if (Int64.TryParse(txtEmployeeID.Text, out id))
            //{
            //    try
            //    {
            //        gridEmployeeDetail.DataContext = HrDAC.Instance.GetEmployee(id);
            //    }
            //    catch
            //    {
            //        MessageBox.Show("Error contacting database.");
            //    }
            //}
            //else
            //{
            //    MessageBox.Show("Invalid ID.");
            //}
        }

        private void BtnOK_Click(object sender, RoutedEventArgs e)
        {
            Close();
        }

        private void BtnGetAllEmployees_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                employees = HrDAC.Instance.GetEmployee();
                lstEmployees.ItemsSource = employees;
                //lstEmployees.Items.SortDescriptions.Add(
                //  new System.ComponentModel.SortDescription("Content",
                //       System.ComponentModel.ListSortDirection.Ascending));
            }
            catch
            {
                MessageBox.Show("Error contacting database.");
            }

        }

    }
}
