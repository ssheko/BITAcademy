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

namespace ConnectDB
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

        //string[] columnName = { "EMPLOYEE_ID", "FIRST_NAME", "LAST_NAME", "EMAIL" ,
        //    "PHONE_NUMBER", "HIRE_DATE", "JOB_ID", "SALARY", "COMMISSION_PCT",
        //    "MANAGER_ID", "DEPARTMENT_ID"};
        private void BtnEmployeeID_Click(object sender, RoutedEventArgs e)
        {
            long id;
            if(Int64.TryParse(txtEmployeeID.Text, out id))
            {
                try
                {
                    gridEmployeeDetail.DataContext = HrDAC.Instance.GetEmployee(id);
                }
                catch
                {
                    MessageBox.Show("Error contacting database.");
                }
            }
            else
            {
                MessageBox.Show("Invalid ID.");
            }
        }

        private void BtnOK_Click(object sender, RoutedEventArgs e)
        {
            Close();
        }
    }
}
